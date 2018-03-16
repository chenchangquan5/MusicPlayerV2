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
    qDebug() << index.row();
}
