#ifndef LYRICWIDGET_H
#define LYRICWIDGET_H

#include <QWidget>
#include <QLabel>

class LyricLine
{
public:
    qint64 time;
    QString text;

    LyricLine(qint64 time, QString text):time(time), text(text){}
};

bool operator <(const LyricLine& A, const LyricLine& B);


class LyricWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LyricWidget(QWidget *parent = nullptr);
    ~LyricWidget();

    QString getLyricText(int index);
    void clear();

signals:

public slots:
    void updateLyrics(qint64 position);
    bool processLyricFile(QString filePath);


private:
    QList<LyricLine> lines;
    QList<QLabel*> displayedLrcs;

    void uiInit();
};

#endif // LYRICWIDGET_H
