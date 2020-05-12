#include "minimusicplayer.h"
#include "ui_minimusicplayer.h"

MiniMusicPlayer::MiniMusicPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiniMusicPlayer)
{
    ui->setupUi(this);
}

MiniMusicPlayer::~MiniMusicPlayer()
{
    delete ui;
}
