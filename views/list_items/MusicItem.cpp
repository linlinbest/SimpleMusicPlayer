#include "MusicItem.h"
#include "ui_MusicItem.h"
#include "views/PlaylistWidget.h"

MusicItem::MusicItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicItem)
{
    ui->setupUi(this);
    uiInit();
    row = -1;
}

void MusicItem::uiInit() {
    connect(ui->removeButton, SIGNAL(clicked()),this, SLOT(removeItem()));
}

void MusicItem::setTitle(const QString title) {
    ui->titleButton->setText(title);
}

void MusicItem::setCover(QImage cover) {
    ui->coverLabel->setPixmap(QPixmap::fromImage(cover));
}

void MusicItem::setRow(int index) {
    row = index;
}

int MusicItem::getRow() {
    return row;
}

Ui::MusicItem* MusicItem::getUi() {
    return ui;
}

void MusicItem::setItem(QListWidgetItem *widgetItem) {
    item = widgetItem;
    //connect(item->listWidget(),SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(setItem(QListWidgetItem*)));
}

void MusicItem::setMusicList(MusicList *list) {
    musicList = list;
}

void MusicItem::removeItem() {
    //item->setSelected(true);
    int i= item->listWidget()->row(item);

    //item->listWidget()->takeItem(i);
    //qDebug() << row << i;
    musicList->removeMusic(i);
    item->listWidget()->takeItem(i);
}

QListWidgetItem* MusicItem::getItem() {
    return item;
}

MusicItem::~MusicItem()
{
    delete ui;
}
