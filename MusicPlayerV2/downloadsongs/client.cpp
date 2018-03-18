#include "client.h"
#include "ui_client.h"

#include <QMessageBox>
#include <QStringList>
#include <QTextStream>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    ui->progressBar->setValue(0);

    m_tcpBlockSize = 0;
    m_tcpSocket = new QTcpSocket(this);

    connect(m_tcpSocket, SIGNAL(readyRead()),
            this, SLOT(readyToRead()));
}

Client::~Client()
{
    delete ui;
}

void Client::readyToRead(void)
{
    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_5_8);

    if(m_tcpBlockSize == 0)
    {
        if(m_tcpSocket->bytesAvailable()<sizeof(quint16))
            return;

        in >> m_tcpBlockSize;
    }

    if(m_tcpSocket->bytesAvailable() < m_tcpBlockSize)
        return;

    QByteArray message;
    in >> message;

    m_tcpBlockSize = 0;

    //匹配msg中含有"@$@$@"的连续字符
    QString msg = message;
    if(msg.contains("@$@$@",Qt::CaseSensitive))
    {
        msg.remove("@$@$@");

        emit signalSendSongNameToWidget(msg);
    }else
    {
        if(m_isStart)
        {
            m_isStart = false;
            analysisHeadDataPack(message);
        }else
        {
            analysisFileDataPack(message);
        }
    }
}

void Client::analysisHeadDataPack(const QByteArray &message)
{
    QString msg(message);
    QStringList list = msg.split("##");
    qDebug() << list;
    //接收包头
    m_recvSize = 0;
    m_fileName = list.at(0);
    m_fileSize = QString(list.at(1)).toUInt();

    QString str = QString("接收的文件:[%1:%2kB]").arg(m_fileName).arg(m_fileSize/1024);
    setWindowTitle(str);

    ui->progressBar->setMaximum(m_fileSize);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);

    m_file.setFileName(m_fileName);
    if(false == m_file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this,"Error","文件创建并打开失败!");
    }

    sendMsgToHost("FileHead recv");
}

void Client::analysisFileDataPack(const QByteArray &message)
{
    this->show();

    //接收处理文件
    qint64 len = m_file.write(message);
    m_recvSize += len;
//    qDebug() << "m_recvSize: " << m_recvSize;

    ui->progressBar->setValue(m_recvSize);

    qDebug() << "m_rec" << m_recvSize;
    qDebug() << "m_file" << m_fileSize;

    if(m_recvSize == m_fileSize) //接收完毕
    {
        m_file.close();
        //提示信息
        QMessageBox::information(this,"完成","文件接收完成");
        //回射信息
        sendMsgToHost("file write done");
        m_tcpSocket->disconnectFromHost();
        m_tcpSocket->close();

        this->close();
    }
}

void Client::slotSendMsg(void)
{
    m_tcpSocket->connectToHost("localhost", 5555);
    sendMsgToHost("receive songs list");
}

void Client::slotSendSongsNamePosition(int index)
{
    QString num = "%^%*%" + QString::number(index);

    sendMsgToHost(num.toLatin1());
}

void Client::slotSendDisconnect(void)
{
    m_tcpSocket->disconnectFromHost();
    m_tcpSocket->close();
}

void Client::sendMsgToHost(const QByteArray &message)
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);

    out << (quint16)0;
    out << message;
    out.device()->seek(0);
    out << (quint16)(buffer.size() - sizeof(quint16));

    m_tcpSocket->write(buffer);
}
