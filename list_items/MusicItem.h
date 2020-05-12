#ifndef MUSICITEM_H
#define MUSICITEM_H

#include <QWidget>

namespace Ui {
class MusicItem;
}

class MusicItem : public QWidget
{
    Q_OBJECT

public:
    explicit MusicItem(QWidget *parent = nullptr);
    ~MusicItem();

private:
    Ui::MusicItem *ui;
};

#endif // MUSICITEM_H
