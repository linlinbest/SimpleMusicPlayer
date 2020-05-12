#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QListWidget>
#include "models/MusicList.h"

class PlaylistWidget : public QListWidget
{
    Q_OBJECT
public:
    PlaylistWidget(QWidget *parent=nullptr);

    //刷新显示
    void refresh();
    //设置歌曲列表
    void setMusicList(MusicList *music);
    MusicList* getMusicList();
    //设置播放列表
    void setMusicList_playing(MusicList *music);
    //移除歌曲
    void removeMusic();
    //在文件夹中打开
    void showInExplorer();
    //歌曲详情
    void detail();
    //设置/获取图标Icon
    void setIcon(QIcon iicon){ icon=iicon; }
    QIcon getIcon(){ return icon; }

private:
    //当前歌曲列表（存储的是歌曲信息）
    MusicList *musicList;
    //当前展示列表项使用的图标
    QIcon icon=QIcon(":/image/image/image/music.png");
};

#endif // PLAYLISTWIDGET_H
