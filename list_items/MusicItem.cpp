#include "MusicItem.h"
#include "ui_MusicItem.h"

MusicItem::MusicItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicItem)
{
    ui->setupUi(this);
}

MusicItem::~MusicItem()
{
    delete ui;
}
