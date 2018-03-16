#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

signals:
    void signalSendSongNameToWidget(const QString songName);

public slots:
    void slotSendMsg(void);

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

    void sendMsgToHost(const QByteArray &message);
    void analysisHeadDataPack(const QByteArray &message);
    void analysisFileDataPack(const QByteArray &message);

private slots:
    void readyToRead(void);


private:
    Ui::Client *ui;

    bool m_isStart;
    QFile m_file;             //文件对象
    QString m_fileName;       //文件名字
    qint64 m_fileSize;        //文件大小
    qint64 m_recvSize;        //已经发送大小

    quint16 m_tcpBlockSize;
    QTcpSocket *m_tcpSocket;
};

#endif // CLIENT_H
