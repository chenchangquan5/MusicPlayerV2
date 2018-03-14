#ifndef PLAYERLOGIC_H
#define PLAYERLOGIC_H

#include <QObject>
#include <QMediaPlayer>
#include <QMenu>

#include "mainwidget.h"
#include "lyricfiles.h"
#include "settingsdialog.h"
#include "songfiles.h"
#include "miniwidget.h"
#include "timingsettings.h"
#include "login.h"
#include "register.h"
#include "downloadsongs.h"


class PlayerLogic : public QObject
{
    Q_OBJECT

public slots:
    void slotChangePath(QString songPath, QString lyricPath);

    void slotControlPlay(void);
    void slotControlNext(void);
    void slotControlPrev(void);
    void slotControlPlayMode(int index);
    void slotControlSongNameListChangePlay(int index);
    void slotControlPosition(int position);
    void slotControlVolume(int volume);
    void slotControlSetting(void);
    void slotNormalToMini(void);
    void slotMiniToNormal(void);
    void slotCustomContexMenuRequested(int pos_x, int pos_y);
    void slotCloseWidget(void);
    void slotShowTimingSettings(void);
    void slotTimingSettingsToTimingStop(void);
    void slotTimingSettingsToTimingPlay(void);
    void slotShowLogin(void);
    void slotShowRegister(void);
    void slotShowDownloadSongs(void);
    void slotLoginSuccess(void);
    void slotLogout(void);

public:
    explicit PlayerLogic(QObject *parent = 0);
    ~PlayerLogic();

    void showMainWidget(void);

signals:
    void signalLoginSuccessToMainWidget(void);
    void signalLogoutToMainWidget(void);

private slots:
    void slotCurrentIndexChanged(int position);
    void slotDurationChanged(qint64 duration);
    void slotPositionChanged(qint64 position);

private:

    //设置界面
    SettingsDialog *m_settingsDialog;
    void initSettingsDialog(void);

    int m_playIndex;
    int m_playMode;
    QMediaPlayer *m_player;
    void initPlayer(void);

    LyricFiles *m_lyricFiles;
    void getCurrentSongLyric(void);

    qint64 m_currentPlayerTime;
    qint64 m_totalPlayerTime;
    QString m_songName;
    QString m_playPosition;
    SongFiles *m_songFiles;
    QMediaPlaylist *m_playList;
    void initPlayList(void);

    //初始化迷你界面
    MiniWidget *m_miniWidget;
    void initMiniWidget(void);

    //初始化主界面
    MainWidget *m_mainWidget;
    void initMainWidget(void);

    //菜单界面
    QMenu *m_menu;

    //初始化定时设置界面
    TimingSettings *m_timingSettings;
    void initTimingSettings(void);

    //初始化登录界面
    Login *m_login;
    void initLogin(void);

    //初始化注册界面
    Register *m_register;
    void initRegister(void);

    //初始化下载界面
    DownloadSongs *m_downloadSongs;
    void initDownloadSongs(void);
};

#endif // PLAYERLOGIC_H
