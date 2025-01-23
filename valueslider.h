
#ifndef VALUESLIDER_H
#define VALUESLIDER_H

#include <QSlider>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionSlider>
#include <QString>
#include <QFontDatabase>

class ValueSlider : public QSlider
{
    Q_OBJECT
public:
    explicit ValueSlider(Qt::Orientation orientation, QWidget *parent = nullptr)
        : QSlider(orientation, parent) {
    }

    /*!
     * \brief setMode sets the mode used by slider
     * \param light_mode is a flag indicating whether light mode should be used
     */
    void setMode(bool light_mode) {
        this->light_mode = light_mode;
    }
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QColor light_theme = QColor("#483F99");
    QColor dark_theme = QColor("#F8F8F2");
    bool light_mode = true;
};

#endif // VALUESLIDER_H
