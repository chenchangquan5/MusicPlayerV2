#include "downloadsongs.h"
#include "ui_downloadsongs.h"

#include <QStringList>
#include <QMenu>
#include <QCursor>
#include <QDebug>

DownloadSongs::DownloadSongs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadSongs)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->lw_songNL->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lw_songNL->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

DownloadSongs::~DownloadSongs()
{
    delete ui;
}

void DownloadSongs::slotSendSongNameToWidget(const QString songName)
{
    QStringList songNameList = songName.split(",");
    ui->lw_songNL->clear();
    ui->lw_songNL->addItems(songNameList);
}

void DownloadSongs::on_lw_songNL_customContextMenuRequested(const QPoint &pos)
{
    QMenu *m_menu = new QMenu(this);

    m_menu->addAction("下载", this, SLOT(slotDownloadSongs()));
    m_menu->exec(QCursor::pos());
}

void DownloadSongs::slotDownloadSongs()
{
    qDebug() << "pos";
}

void DownloadSongs::on_lw_songNL_doubleClicked(const QModelIndex &index)
{
    emit signalSendSongsNamePosition(index.row());
}

void DownloadSongs::on_pb_close_clicked()
{
    emit signalSendDisconnect();
    this->close();
}

void DownloadSongs::mousePressEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        m_widgetMove = ev->globalPos() - this->frameGeometry().topLeft();
        ev->accept();
    }
}

void DownloadSongs::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        this->move(ev->globalPos() - m_widgetMove);
        ev->accept();
    }
}


