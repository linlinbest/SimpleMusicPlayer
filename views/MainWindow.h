#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSqlDatabase>

#include "models/MusicList.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void playbackToggled();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMediaPlayer* getPlayer();
    MusicList* getCurrMusicList();
    void setCurrMusicList(MusicList *musicList);

    //QString formatTime(qint64 timeMilliSeconds);

public slots:
    void quitMusicPlayer();
    void addFile();
    void togglePlayback();
    void switchMode();
    void playAll();
    void removeAll();


private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QSqlDatabase database;
    MusicList *currMusicList;

    void uiInit();
    void playerInit();
    void sqlInit();

protected:
    bool isWindowMoveable = false;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void updateState();
    void updateInfo();
    void updateCurrPlaylist();
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void setPosition(int position);
    void openMiniMusicPlayer();
};
#endif // MAINWINDOW_H
