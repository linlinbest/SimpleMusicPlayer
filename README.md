# SimpleMusicPLayer

## Project Structure

- main.cpp
- models
  - Music.h/cpp
  - MusicList.h/cpp
- utils
  - Common.h/cpp
- views
  - list_items
    - MusicItem.h/cpp
  - buttons
    - VolumeButton.h/cpp
  - MainWindow.h/cpp
  - MiniMusicPlayer.h/cpp
  - LyricWidget.h/cpp
  - PlaylistWidget.h/cpp
- images
  - images.qrc
    - backgrounds
    - button_icons
- SimpleMusicPlayer.pro

## Classes

- Music  
This class holds the basic information of music.  

- MusicList  
The MusicList Class contains a vector of Music and supports reading lists of music from the database.  
*Noted*: Qt's QMediaPlaylist Class does not support accessing embedded information like titles and authors in music files. In order to that, you have to use QObject::metaData after setting the media in a QMediaPlayer instance. Therefore, it is neccessary have this class to access music information with less cost.

- Common  
This class provides static functions that will be used in multiple classes

- MainWindow : QMainWindow  
The main widget of the music player. It contains all basic operations on music player and embeds a simple database to store music information.

- MiniPlayer : QWidget  
A concise version of the music player that will show up at the bottom corner when MainWindow is minimized.

- LyricWidget : QWidget  
Support reading .lrc files and converting them into dynamic lyrics.

- MusicItem : QWidget  
A custom widget to be set in QListitemWidget.

- PlaylistWidget : QListWidget  
This class is used to display the content of MusicList in the form of MusicItem. You can also edit the Musiclist through buttons inside MusicItem.
