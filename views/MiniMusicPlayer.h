#ifndef MINIMUSICPLAYER_H
#define MINIMUSICPLAYER_H

#include "MainWindow.h"

#include <QWidget>
#include <QMediaPlayer>

namespace Ui {
class MiniMusicPlayer;
}

class MiniMusicPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit MiniMusicPlayer(MainWindow *mainPlayerWindow);
    ~MiniMusicPlayer();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::MiniMusicPlayer *ui;
    MainWindow *mainWindow;
    QMediaPlayer *player;

    void playInit();
    void uiInit();

private slots:
    void updateState();
};

#endif // MINIMUSICPLAYER_H
