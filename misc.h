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

#include "styles.h"


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
     */
    void updatePower(QString);

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
     * \brief updateGraph is used to invoke arcane arts and redraw temperature graph
     * \param light_mode is a flag which indicates whether light theme is used currently
     * \param working is a flag which indicates whether AC is working
     */
    void updateGraph(int, int, bool light_mode = true, bool working = true);
private:
    QPushButton *mode_button;
    QPushButton *humidity_button;
    QPushButton *power_button;
    // will use qgraphicscene instead of qcustomplot
    // as i love being subjected to physical and psychological torture
    QGraphicsScene *graphics_scene;
    QGraphicsView* view;
    QLabel *direction_label;
    QSlider *direction_slider;
    QPushButton *pressure_button;

    QGridLayout *main_layout;

    QTimer* timer;
    qreal time_elapsed;
    QVector<QPointF> target_points; // stores graph data
    QVector<QPointF> outside_points; // stores graph data
signals:
    void modeSwitch();
    void powerSwitch();
    void changePressureUnits();
    void directionSliderValueChanged(int value);

    void graphDataRequest();
};

#endif // MISC_H
