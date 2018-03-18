#ifndef DOWNLOADSONGS_H
#define DOWNLOADSONGS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

namespace Ui {
class DownloadSongs;
}

class DownloadSongs : public QWidget
{
    Q_OBJECT

signals:
    void signalSendMsg(void);
    void signalSendSongsNamePosition(int index);
    void signalSendDisconnect(void);

public slots:
    void slotSendSongNameToWidget(const QString songName);
    void slotDownloadSongs(void);

public:
    explicit DownloadSongs(QWidget *parent = 0);
    ~DownloadSongs();

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private slots:
    void on_lw_songNL_doubleClicked(const QModelIndex &index);
    void on_lw_songNL_customContextMenuRequested(const QPoint &pos);
    void on_pb_close_clicked();

private:
    Ui::DownloadSongs *ui;

    QPoint m_widgetMove;
};

#endif // DOWNLOADSONGS_H
