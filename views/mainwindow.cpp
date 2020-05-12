#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MiniMusicPlayer.h"

#include "views/list_items/MusicItem.h"
#include "utils/Common.h"
#include "models/MusicList.h"

#include <QtWidgets>
#include <QFileDialog>
#include <QMediaPlaylist>
#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sqlInit();

    playerInit();
    uiInit();

}

void MainWindow::addFile() {
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setWindowTitle(tr("Add local files"));
//    QStringList list;list<<"application/octet-stream";
//    fileDialog.setMimeTypeFilters(list);
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted){
       QList<QUrl> urls=fileDialog.selectedUrls();
       currMusicList->addMusic(urls);
       currMusicList->insert_SQL_all();
       updateCurrPlaylist();
    }
}

/**
 * @brief play all the music in the current musiclist
 */
void MainWindow::playAll() {
    playlist->clear();
    currMusicList->addToPlayList(playlist);
    player->stop();
    togglePlayback();
    //player->play();

}

void MainWindow::quitMusicPlayer() {
    //database.close();
    QCoreApplication::quit();
}

void MainWindow::sqlInit() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("SimpleMusicPlayer.db");
        database.setUserName("local");
        database.setPassword("123456");
        if (!database.open()) {
            QMessageBox::critical(this,tr("Database Error"),database.lastError().databaseText());
            exit(-1);
        }
    }
    //create tables if they don't exist
//    QSqlQuery tmp;
//    tmp.exec(QString("DROP TABLE MusicLists"));
//    QSqlQuery tmp1;
//    tmp1.exec(QString("DROP TABLE MusicInfo"));

    QSqlQuery query;
    QString create_sql = "CREATE TABLE IF NOT EXISTS MusicInfo (name VARCHAR(30), url VARCHAR(200), "
                         "author VARCHAR(50), title VARCHAR(50), duration BIGINT, albumTitle VARCHAR(50), "
                         "audioBitRate INT, PRIMARY KEY(name, url))";
    //query.prepare(create_sql);
    query.exec(create_sql);


    QSqlQuery query2;
    QString create_sql2 = "CREATE TABLE IF NOT EXISTS MusicLists (name VARCHAR(30) PRIMARY KEY)";
    //query2.prepare(create_sql2);
    query2.exec(create_sql);
}

void MainWindow::uiInit() {
    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->volumeButton->stylize();
    ui->volumeButton->setToolTip(tr("Adjust volume"));
    ui->volumeButton->setVolume(player->volume());

    ui->currPlaylistWidget->setMusicList(this->getCurrMusicList());
    ui->currLyricsWidget->setAutoFillBackground(true);
    //ui->currLyricsWidget->setBackgroundRole(QPalette::Background);

    //connect signals and slots of buttons inside the main window
    connect(ui->positionSlider, &QAbstractSlider::valueChanged, this, &MainWindow::setPosition);
    connect(ui->prevButton, &QAbstractButton::clicked, playlist, &QMediaPlaylist::previous);
    connect(ui->nextButton, &QAbstractButton::clicked, playlist, &QMediaPlaylist::next);
    connect(ui->playButton, &QAbstractButton::clicked, this, &MainWindow::togglePlayback);
    connect(this, &MainWindow::playbackToggled, this, &MainWindow::updateState);
    connect(ui->modeButton, &QAbstractButton::clicked, this, &MainWindow::switchMode);
    connect(ui->volumeButton, &VolumeButton::volumeChanged, player, &QMediaPlayer::setVolume);

    connect(ui->minimizeButton, &QAbstractButton::clicked, this, &MainWindow::hide);
    connect(ui->minimizeButton, &QAbstractButton::clicked, this, &MainWindow::openMiniMusicPlayer);
    connect(ui->closeButton, &QAbstractButton::clicked, this, &MainWindow::quitMusicPlayer);

    connect(ui->openFileButton, &QAbstractButton::clicked, this, &MainWindow::addFile);
    connect(ui->removeAllButton, &QAbstractButton::clicked, this, &MainWindow::removeAll);
    connect(ui->playAllButton, &QAbstractButton::clicked, this, &MainWindow::playAll);

    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updatePosition);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::updateDuration);
    connect(player, &QMediaPlayer::metaDataAvailableChanged, this, &MainWindow::updateInfo);
    connect(player, &QMediaPlayer::audioAvailableChanged, this, &MainWindow::updateState);

    //connect(player, &QMediaPlayer::metaDataAvailableChanged, this, &MainWindow::update);

    connect(player, &QMediaPlayer::positionChanged, ui->currLyricsWidget, &LyricWidget::updateLyrics);


}

void MainWindow::playerInit() {
    //player initialization
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);

    currMusicList = new MusicList();// TODO: remember to delete
    currMusicList->setName("");
    currMusicList->read_fromSQL();
    currMusicList->addToPlayList(playlist);

}

void MainWindow::openMiniMusicPlayer() {
    MiniMusicPlayer* miniPlayer = new MiniMusicPlayer(this);
    miniPlayer->move(1000,550);
    //miniPlayer->setAttribute(Qt::WA_DeleteOnClose);
    miniPlayer->show();
}

/**
 * @brief update the information of the current music
 */
void MainWindow::updateInfo() {
    if (!player->isMetaDataAvailable()) {
        QImage noMusic = QImage(":/button_icons/no_music.png");
        ui->coverLabel->setPixmap(QPixmap::fromImage(noMusic));
        ui->currLyricsWidget->clear();
        return;
    }

    QImage picImage= player->metaData(QStringLiteral("ThumbnailImage")).value<QImage>();
    if(picImage.isNull()) picImage=QImage(":/button_icons/no_music.png");

    QString titleAuthor = player->metaData(QStringLiteral("Title")).toString()
            + " - " +  player->metaData(QStringLiteral("Author")).toString();
    ui->titleLabel->setText(titleAuthor);

    QUrl musicUrl = player->playlist()->currentMedia().canonicalUrl();
    Music tmpMusic = Music(musicUrl);
    QString lrcFilePath = tmpMusic.getLyricFile();


    ui->currLyricsWidget->processLyricFile(lrcFilePath);
    ui->coverLabel->setPixmap(QPixmap::fromImage(picImage));

}

void MainWindow::updateCurrPlaylist() {
    //ui->currPlaylistWidget->clear();
    //currMusicList->addToListWidget(ui->currPlaylistWidget);
    ui->currPlaylistWidget->refresh();
}

/**
 * @brief switch the playback mode of the playlist
 */
void MainWindow::switchMode() {
    if (playlist->playbackMode() == QMediaPlaylist::Loop) {
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        ui->modeButton->setIcon(QIcon(":/button_icons/loop_on_one.svg"));
    }
    else if (playlist->playbackMode() == QMediaPlaylist::CurrentItemInLoop) {
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        ui->modeButton->setIcon(QIcon(":/button_icons/random.svg"));
    }
    else if (playlist->playbackMode() == QMediaPlaylist::Random) {
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        ui->modeButton->setIcon(QIcon(":/button_icons/loop.svg"));
    }
}

/**
 * @brief Toggle the state of the player
 */
void MainWindow::togglePlayback() {
    if (player->state() == QMediaPlayer::PlayingState) player->pause();
    else player->play();
    emit playbackToggled();
}

/**
 * @brief update the state of the main window
 */
void MainWindow::updateState() {
    if (player->state() == QMediaPlayer::PlayingState) {
        ui->playButton->setToolTip(tr("Pause"));
        ui->playButton->setIcon(QIcon(":/button_icons/pause.svg"));
    }
    else {
        ui->playButton->setToolTip(tr("Play"));
        ui->playButton->setIcon(QIcon(":/button_icons/play.svg"));
    }
}


/**
 * @brief updates the position of the progress slider
 */
void MainWindow::updatePosition(qint64 position) {
    ui->positionSlider->setValue(static_cast<int>(position));
    //qDebug() << position;

    ui->positionLabel->setText(Common::formatTime(position)+"/"+Common::formatTime(player->duration()));
    //if(playlist->currentIndex()>=0)ui->lyricWidget->show(position);
}

/**
 * @brief updates the duration of the progress slider
 */
void MainWindow::updateDuration(qint64 duration) {
    ui->positionSlider->setRange(0, static_cast<int>(duration));
    ui->positionSlider->setEnabled(static_cast<int>(duration) > 0);
    ui->positionSlider->setPageStep(static_cast<int>(duration) / 10);
}

void MainWindow::setPosition(int position) {
    // avoid seeking when the slider value change is triggered from updatePosition()
    if (qAbs(player->position() - position) > 1000) {
        //qDebug() << "HAHAH";
        player->setPosition(position);
    }
}

/**
 * @brief get the pointer to the current media player
 */
QMediaPlayer* MainWindow::getPlayer() {
    return player;
}

MusicList* MainWindow::getCurrMusicList() {
    return currMusicList;
}
void MainWindow::setCurrMusicList(MusicList *musicList) {
    currMusicList = musicList;
    playlist->clear();
    currMusicList->addToPlayList(playlist);
}

void MainWindow::removeAll() {
    currMusicList->clear();
    updateCurrPlaylist();
}


void MainWindow::mousePressEvent(QMouseEvent* e) {
    if(e->button() ==  Qt::LeftButton) {
        isWindowMoveable = true;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* e) {
    if(isWindowMoveable) {
        move(e->globalPos());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* e) {
    if(e->button() ==  Qt::LeftButton) {
        isWindowMoveable = false;
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

