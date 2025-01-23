
#include "valueslider.h"

void ValueSlider::paintEvent(QPaintEvent *event)
{
    // call the base class to handle the standard painting
    QSlider::paintEvent(event);

    QPainter painter(this);

    if (light_mode)
        painter.setPen(light_theme); // set text color
    else
        painter.setPen(dark_theme); // set text color

    // load the desired font
    int id = QFontDatabase::addApplicationFont(":/fonts/UbuntuMono-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family, 16);
    painter.setFont(monospace);

    // Get slider's current value
    int value = this->value();
    QString valueText = QString::number(value);

    // Calculate position for the text
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect handleRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

    // Center the text on the handle
    QRect textRect = handleRect;
    textRect.moveTop(handleRect.top() - 24); // Adjust text position above the handle

    // Draw the text
    painter.drawText(textRect, Qt::AlignCenter, valueText);
}
