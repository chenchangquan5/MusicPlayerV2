#ifndef DOWNLOADSONGS_H
#define DOWNLOADSONGS_H

#include <QWidget>

namespace Ui {
class DownloadSongs;
}

class DownloadSongs : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadSongs(QWidget *parent = 0);
    ~DownloadSongs();

private:
    Ui::DownloadSongs *ui;
};

#endif // DOWNLOADSONGS_H
