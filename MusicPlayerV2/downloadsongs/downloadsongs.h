#ifndef DOWNLOADSONGS_H
#define DOWNLOADSONGS_H

#include <QWidget>

namespace Ui {
class DownloadSongs;
}

class DownloadSongs : public QWidget
{
    Q_OBJECT

signals:
    void signalSendMsg(void);

public slots:
    void slotSendSongNameToWidget(const QString songName);
    void slotDownloadSongs();

public:
    explicit DownloadSongs(QWidget *parent = 0);
    ~DownloadSongs();

private slots:
    void on_lw_songNL_customContextMenuRequested(const QPoint &pos);

    void on_lw_songNL_doubleClicked(const QModelIndex &index);

private:
    Ui::DownloadSongs *ui;

};

#endif // DOWNLOADSONGS_H
