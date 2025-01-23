#pragma once

#ifndef TEMPERATURE_H
#define TEMPERATURE_H


#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFontDatabase>
#include <QFormLayout>
#include <QPushButton>

#include "styles.h"

class Temperature : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Temperature is the only constuctor of the widget
     * \param parent is the parent of the widget
     */
    explicit Temperature(QWidget *parent = nullptr);

    /*!
     * \brief updateTemperature is used to update the displayed temperature
     * \param outside is a flag which indicates which temperature is being updated (outside temp. by default)
     */
    void updateTemperature(QString, bool outside = false);

    /*!
     * \brief switchStyles is used to switch UI theme
     * \param light is a flag which indicates whether light theme should be used
     */
    void switchStyles(bool light = true);

    /*!
     * \brief updatePower updates the temperature module in accord with AC's working state
     * \param working is a flag indicating whether the AC is working or not
     */
    void updatePower(bool working);
private:
    QPushButton *plus_button;
    QPushButton *target_temperature_button;
    QLabel *real_temperature_label;
    QPushButton *minus_button;

    QWidget *upper_filler;
    QWidget *lower_filler;

    QWidget *widget;
    QVBoxLayout *main_layout;
signals:
    void increaseTemperature();
    void decreaseTemperature();
    void changeTemperatureUnits();
};

#endif // TEMPERATURE_H
