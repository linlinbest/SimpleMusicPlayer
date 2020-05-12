#include "ui_MusicItem.h"
#include "PlaylistWidget.h"
#include "views/list_items/MusicItem.h"

PlaylistWidget::PlaylistWidget(QWidget *parent)
    :QListWidget (parent)
{
    //this->setSelectionMode(QAbstractItemView::MultiSelection);
}

void PlaylistWidget::refresh()
{
    clear();
    //TODO:add custom listWidget
    //musicList->addToListWidget(this);

    for (int i=0; i<musicList->size(); i++){
        const Music music = musicList->getMusic(i);

        QListWidgetItem *item = new QListWidgetItem;
        //item->setIcon(listWidget->getIcon());
        //item->setText(music.getInfo());

        MusicItem *musicItem = new MusicItem();
        item->setSizeHint(QSize(0, musicItem->size().height()));
        musicItem->setTitle(music.getInfo());
        musicItem->setCover(music.getCover());

        musicItem->setRow(i);
        musicItem->setItem(item);
        musicItem->setMusicList(musicList);

        this->addItem(item);
        this->setItemWidget(item,musicItem);

        //connect(musicItem->getUi()->removeButton, SIGNAL(clicked()),);

        //connect(this,SIGNAL(itemPressed(QListWidgetItem*)), musicItem, SLOT(setItem(QListWidgetItem*)));
        //connect(this,SIGNAL(itemPressed(QListWidgetItem*)), musicItem, SLOT(setRow(int)));
        //item->listWidget()->removeItemWidget(item)

        //qDebug() << listWidget->width();
    }
}

void PlaylistWidget::setMusicList(MusicList *music)
{
    musicList=music;
    refresh();
}

MusicList* PlaylistWidget::getMusicList() {
    return musicList;
}

void PlaylistWidget::setMusicList_playing(MusicList *music)
{
    musicList=music;
    musicList->setSQL(false);
    refresh();
}

void PlaylistWidget::removeMusic()
{
    int pos=currentRow();
    //移除
    musicList->removeMusic(pos);
    //实测这里如果直接使用removeMedia会导致当前播放的歌曲乱跳...（所以这里只能从更上层调用的地方来移除正在播放的歌曲）
    //playlist->removeMedia(pos);

    //从ListWidget中移除
    QListWidgetItem *tempItem=takeItem(pos);
    removeItemWidget(tempItem);
    delete tempItem;
}

void PlaylistWidget::showInExplorer()
{
    int pos=currentRow();
    musicList->showInExplorer(pos);
}

void PlaylistWidget::detail()
{
    int pos=currentRow();
    musicList->detail(pos);
}
