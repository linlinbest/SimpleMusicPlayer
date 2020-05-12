#include "MiniMusicPlayer.h"
#include "ui_MiniMusicPlayer.h"
#include "MainWindow.h"

#include <QPainter>

MiniMusicPlayer::MiniMusicPlayer(MainWindow *mainPlayerWindow) :
    QWidget(),
    ui(new Ui::MiniMusicPlayer)
{
    mainWindow = mainPlayerWindow;

    ui->setupUi(this);



    playInit();
    uiInit();
}

void MiniMusicPlayer::uiInit() {
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowOpacity(0.7);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    connect(ui->closeButton, &QAbstractButton::clicked, this, &QWidget::deleteLater);

    //player = static_cast<MainWindow*>(mainWindow)->getPlayer();
    connect(ui->closeButton, &QAbstractButton::clicked, mainWindow, &MainWindow::show);
    connect(ui->playButton, &QAbstractButton::clicked, mainWindow, &MainWindow::togglePlayback);
    connect(mainWindow, &MainWindow::playbackToggled, this, &MiniMusicPlayer::updateState);
    connect(ui->prevButton, &QAbstractButton::clicked, player->playlist(), &QMediaPlaylist::previous);
    connect(ui->nextButton, &QAbstractButton::clicked, player->playlist(), &QMediaPlaylist::next);
}

void MiniMusicPlayer::playInit() {
    player = mainWindow->getPlayer();
    updateState();


}


/**
 * @brief update the state of the mini music player
 */
void MiniMusicPlayer::updateState() {
    if (player->state() == QMediaPlayer::PlayingState) {
        ui->playButton->setToolTip(tr("Pause"));
        ui->playButton->setIcon(QIcon(":/button_icons/pause.svg"));
    }
    else {
        ui->playButton->setToolTip(tr("Play"));
        ui->playButton->setIcon(QIcon(":/button_icons/play.svg"));
    }
}


void MiniMusicPlayer::paintEvent(QPaintEvent *) {
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.translate(width() / 2, height() / 2);

//    int frameNo = 3;
//    bool floatBased = true;

//    for (int diameter = 0; diameter < 256; diameter += 9) {
//        int delta = abs((frameNo % 128) - diameter / 2);
//        int alpha = 255 - (delta * delta) / 4 - diameter;

//        if (alpha > 0) {
//            painter.setPen(QPen(QColor(0, diameter / 2, 127, alpha), 3));

//            if (floatBased) {
//                painter.drawEllipse(QRectF(-diameter / 2.0, -diameter / 2.0,
//                                           diameter, diameter));
//            } else {
//                painter.drawEllipse(QRect(-diameter / 2, -diameter / 2,
//                                          diameter, diameter));
//            }
//        }
//    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);



    QLinearGradient linearGradient(this->width()/2, this->height(), this->width()/2, 0);
    linearGradient.setColorAt(0.2, QColor("#ffff7f"));
    linearGradient.setColorAt(0.6, Qt::yellow);
    linearGradient.setColorAt(1.0, QColor(255, 170, 0));
    //painter.setBrush( Qt::cyan );
    painter.setPen( QPen(linearGradient, 2) );
    painter.setBrush(QBrush(linearGradient));
    QRect rect(0,0,280,240);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;
    painter.drawPie(rect,startAngle,spanAngle);
}

MiniMusicPlayer::~MiniMusicPlayer()
{
    delete ui;
}
