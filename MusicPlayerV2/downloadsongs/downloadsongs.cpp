#include "downloadsongs.h"
#include "ui_downloadsongs.h"


DownloadSongs::DownloadSongs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadSongs)
{
    ui->setupUi(this);


}

DownloadSongs::~DownloadSongs()
{
    delete ui;

