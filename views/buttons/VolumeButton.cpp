#include "VolumeButton.h"

#include <QtWidgets>

VolumeButton::VolumeButton(QWidget *parent) :
    QToolButton(parent)
{
    setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    setPopupMode(QToolButton::InstantPopup);

    QWidget *popup = new QWidget(this);

    slider = new QSlider(Qt::Horizontal, popup);
    slider->setRange(0, 100);
    connect(slider, &QAbstractSlider::valueChanged, this, &VolumeButton::volumeChanged);

    label = new QLabel(popup);
    label->setAlignment(Qt::AlignCenter);
    label->setNum(100);
    label->setMinimumWidth(label->sizeHint().width());

    typedef void(QLabel::*IntSlot)(int);
    connect(slider, &QAbstractSlider::valueChanged, label, static_cast<IntSlot>(&QLabel::setNum));

    QBoxLayout *popupLayout = new QHBoxLayout(popup);
    popupLayout->setMargin(2);
    popupLayout->addWidget(slider);
    popupLayout->addWidget(label);

    QWidgetAction *action = new QWidgetAction(this);
    action->setDefaultWidget(popup);

    menu = new QMenu(this);
    menu->addAction(action);
    setMenu(menu);

    stylize();
}

void VolumeButton::increaseVolume()
{
    slider->triggerAction(QSlider::SliderPageStepAdd);
}

void VolumeButton::descreaseVolume()
{
    slider->triggerAction(QSlider::SliderPageStepSub);
}

int VolumeButton::volume() const
{
    return slider->value();
}

void VolumeButton::setVolume(int volume)
{
    slider->setValue(volume);
}

void VolumeButton::stylize()
{
//    QPalette myPalette;
//    QColor myColor(0,0,0);
//    myColor.setAlphaF(0);
//    myPalette.setBrush(backgroundRole(),myColor);
//    menu->setPalette(myPalette);
//    menu->setAutoFillBackground(true);
    QString css("QMenu {background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(189, 182, 84, 116), stop:1 rgba(255, 255, 255, 255)) "
                "}");

    //menu->setAttribute(Qt::WA_TranslucentBackground, true);
    menu->setStyleSheet(css);
}
