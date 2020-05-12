#ifndef MUSICITEM_H
#define MUSICITEM_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QListWidgetItem>

#include "models/MusicList.h"

namespace Ui {
class MusicItem;
}

class MusicItem : public QWidget
{
    Q_OBJECT

public:
    explicit MusicItem(QWidget *parent = nullptr);
    ~MusicItem();

    Ui::MusicItem* getUi();
    int getRow();
    QListWidgetItem* getItem();

    void setTitle(const QString title);
    void setCover(QImage cover);
    //MusicItem(QMediaPlaylist *musicList);

    //MusicItem(QMediaPlayer *player);
    //TODO:this class waits to be implemented


public slots:
    void setRow(int index);
    void setItem(QListWidgetItem *widgetItem);
    void setMusicList(MusicList *list);
    void removeItem();

private:
    Ui::MusicItem *ui;
    int row;
    QListWidgetItem* item;
    MusicList* musicList;

    void uiInit();
};

#endif // MUSICITEM_H
