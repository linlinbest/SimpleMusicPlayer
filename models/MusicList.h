#ifndef MUSICLIST_H
#define MUSICLIST_H
#include<vector>
using namespace std;

#include"Music.h"
#include <QMediaPlaylist>
#include <QListWidget>

//#include "views/PlaylistWidget.h"

/**
 * @author 唐金麟
 */

class PlaylistWidget;
//歌曲列表
class MusicList
{
    //歌单名
    QString name;
    //所存储的歌曲
    QVector<Music> music;
    //控制是否需要与数据库交互（比如：当前播放列表的歌单删除歌曲时不需要更新数据库，只是临时的）
    //TODO: property here?
    bool sql_flag=true;

    friend class MainWidget;
public:
    MusicList();
    MusicList(const QList<QUrl>& urls,QString iname="");

    int size() {return music.size();}
    //设定歌单名
    void setName(const QString& iname){name=iname;}
    QString getName(){ return name; }
    //设定数据库标志
    void setSQL(bool on){ sql_flag=on; }
    //从url添加歌曲
    void addMusic(const QList<QUrl>& urls);
    //添加一首歌曲
    void addMusic(const Music& iMusic);
    //获取指定位置的歌曲
    Music getMusic(int pos);
    //将本歌单加入播放列表
    void addToPlayList(QMediaPlaylist *playlist);
    //歌单可视化
    void addToListWidget(PlaylistWidget *listWidget);
    //移除指定的歌曲
    void removeMusic(int pos);
    //在文件夹中打开
    void showInExplorer(int pos);
    //显示指定歌曲详细信息
    void detail(int pos);
    //数据库中移除全部本歌单的歌曲
    void remove_SQL_all();
    //将歌单中的歌曲全部写入数据库
    void insert_SQL_all();
    //从数据中恢复本歌单
    void read_fromSQL();
    //将本列表中的歌曲排序
    void sort_by(COMPARE key=DEFAULT);
    //整理歌单：将歌单中的重复歌曲去掉
    void neaten();
    //清空本歌单
    void clear();
};

#endif // MUSICLIST_H
