#pragma once

#ifndef MISC_H
#define MISC_H


#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFontDatabase>
#include <QFormLayout>
#include <QPushButton>
#include <QSlider>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QTimer>
#include <QRegularExpression>

#include "styles.h"
#include "valueslider.h"

class Misc : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Misc is the only constructor for the widget
     * \param parent is the parent of the widget
     */
    explicit Misc(QWidget *parent = nullptr);

    /*!
     * \brief updatePressure is used to update displayed pressure with passed QString parameter
     */
    void updatePressure(QString);

    /*!
     * \brief updatePower is used to update displayed AC power status with passed QString parameter
     * \param working is a flag indicating whether the AC is working
     */
    void updatePower(QString, bool working);

    /*!
     * \brief updateAirFlowDirection is used to update displayed AC air flow direction with passed int parameter
     */
    void updateAirFlowDirection(int value);

    /*!
     * \brief updateHumidity is used to update displayed humidity with passed QString parameter
     */
    void updateHumidity(QString);



    /*!
     * \brief switchStyles is used to switch current UI theme
     * \param light is a flag which indicates whether light theme should be used
     */
    void switchStyles(bool light);


    /*!
     * \brief updateGraph is used to invoke arcane arts and redraw temperature, pressure and humidity graph
     * \param light_mode is a flag which indicates whether light theme is used currently
     * \param working is a flag which indicates whether AC is working
     */
    void updateGraph(int, int, int, int, bool light_mode = true, bool working = true);
private:
    QPushButton *mode_button;
    QPushButton *humidity_button;
    QPushButton *power_button;
    // will use qgraphicscene instead of qcustomplot
    // as i love being subjected to physical and psychological torture

    // also, new plan.
    // i have no idea what the specs require from me, so i'll just make
    // three different graphs and pray to jesus, allah and buddha that this is it
    QLabel *temperature_label;
    QGraphicsScene *temperature_scene;
    QGraphicsView* temperature_view;
    QLabel *humidity_label;
    QGraphicsScene *humidity_scene;
    QGraphicsView* humidity_view;
    QLabel *pressure_label;
    QGraphicsScene *pressure_scene;
    QGraphicsView* pressure_view;

    QLabel *direction_label;
    ValueSlider *direction_slider;

    QPushButton *settings_button;
    QPushButton *pressure_button;

    QHBoxLayout *head_layout;
    QHBoxLayout *foot_layout;
    QGridLayout *main_layout;

    QTimer* timer;
    qreal time_elapsed;
    QVector<QPointF> t_target_points; // stores graph data
    QVector<QPointF> t_outside_points; // stores graph data
    QVector<QPointF> p_points; // stores graph data
    QVector<QPointF> h_points; // stores graph data

    const int average_humidity = 85;
    const int average_pressure = 758;
signals:
    void modeSwitch();
    void settingsCalled();
    void powerSwitch();
    void changePressureUnits();
    void directionSliderValueChanged(int value);

    void graphDataRequest();
};

#endif // MISC_H
