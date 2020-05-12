#ifndef MINIMUSICPLAYER_H
#define MINIMUSICPLAYER_H

#include <QWidget>

namespace Ui {
class MiniMusicPlayer;
}

class MiniMusicPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MiniMusicPlayer(QWidget *parent = nullptr);
    ~MiniMusicPlayer();

private:
    Ui::MiniMusicPlayer *ui;
};

#endif // MINIMUSICPLAYER_H
