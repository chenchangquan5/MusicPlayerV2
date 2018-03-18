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


};

#endif // DOWNLOADSONGS_H
