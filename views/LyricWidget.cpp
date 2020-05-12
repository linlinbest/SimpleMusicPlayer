#include "LyricWidget.h"

#include <QFile>
#include <QLayout>
#include <QDebug>

bool operator <(const LyricLine& A, const LyricLine& B){
    return A.time < B.time;
}

LyricWidget::LyricWidget(QWidget *parent) : QWidget(parent)
{
    uiInit();
}

LyricWidget::~LyricWidget()
{
    //delete middleLine;
}

void LyricWidget::uiInit() {
    //if (parent()!=nullptr);
    QVBoxLayout *lyricsLayout = new QVBoxLayout;

//    middleLine = new QLabel(this);
//    //middleLine->setGeometry(370,110,301,271);
//    //this->setGeometry(370,110,301,271);
//    //this->resize(301,271);
//    //this->setFixedSize(301,271);
//    //this->setSizePolicy()
//    middleLine->resize(400,20);
//    middleLine->setText(tr("No lyrcis available"));
//    middleLine->setAlignment(Qt::AlignCenter);

    int totalLines = 9;
    for (int i=0; i<totalLines; i++) {
        QLabel *lineText = new QLabel(this);
        if (i==(totalLines-1)/2) lineText->setText(tr("No lyrics available"));
        else lineText->setText("");
        lineText->setAlignment(Qt::AlignCenter);
//        lineText->setFont(QFont("PT Mono"));
//        qDebug() << lineText->fontInfo().toString();
        lyricsLayout->addWidget(lineText);
        displayedLrcs.push_back(lineText);
    }
    this->setLayout(lyricsLayout);
}

void LyricWidget::updateLyrics(qint64 position) {
    int currLine = -1;
    int middleIndex = (displayedLrcs.size()-1)/2;
    if (lines.isEmpty()) {
        for (int i=0; i<displayedLrcs.size(); i++) {
            if (i==middleIndex) displayedLrcs[i]->setText(tr("No lyrics available"));
            else displayedLrcs[i]->setText("");
        }
        return;
    }

    for(int i=0; i+1<lines.size(); i++){
        if(lines[i].time<position && position<=lines[i+1].time){
            currLine = i;
            break;
        }
    }
    if (position>lines.back().time) currLine = lines.size()-1;

    for (int i=0; i<displayedLrcs.size(); i++) {
        displayedLrcs[i]->setText(getLyricText(i+currLine-middleIndex));
    }

}

QString LyricWidget::getLyricText(int index) {
    if(index<0 || index>=lines.size()){
        return "";
    }else{
        return lines[index].text;
    }
}


bool LyricWidget::processLyricFile(QString filePath)
{
    QFile lyricFile(filePath);
    if (!lyricFile.exists()) return false;
    lyricFile.open(QFile::ReadOnly);
    QString content(QString::fromLocal8Bit(lyricFile.readAll()));
    lyricFile.close();

    lines.clear();

    const QRegExp rx("\\[(\\d+):(\\d+(\\.\\d+)?)\\]"); //用来查找时间标签的正则表达式

    // 步骤1
    int pos = rx.indexIn(content);
    if (pos == -1) {
        return false;
    }
    else {
        int lastPos;
        QList<int> timeLabels;
        do {
            // 步骤2
            timeLabels << (rx.cap(1).toInt() * 60 + rx.cap(2).toDouble()) * 1000;
            lastPos = pos + rx.matchedLength();
            pos = rx.indexIn(content, lastPos);
            if (pos == -1) {
                QString text = content.mid(lastPos).trimmed();
                foreach (const int& time, timeLabels)
                    lines.push_back(LyricLine(time, text));
                break;
            }
            // 步骤3
            QString text = content.mid(lastPos, pos - lastPos);
            if (!text.isEmpty()) {
                foreach (const int& time, timeLabels)
                    lines.push_back(LyricLine(time, text.trimmed()));
                timeLabels.clear();
            }
        }
        while (true);
        // 步骤4
        std::stable_sort(lines.begin(), lines.end());
    }
    if (lines.size()) {
        return true;
    }
    return false;
}

void LyricWidget::clear() {
    lines.clear();
    int middleIndex = (displayedLrcs.size()-1)/2;
    displayedLrcs[middleIndex]->setText(tr("No Lyrics Available"));
    //middleLine->setText(tr("No Lyrics Available."));
}


