#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

#include <QDebug>

#include "imitationdialog.h"
#include "conditioner.h"
#include "temperature.h"
#include "misc.h"
#include "loader.h"

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    Conditioner conditioner;
    Misc* misc;
    Temperature* temperature;
    Loader loader;

    QWidget *window;
    QWidget *bkg;

    bool light_mode = true;

    QString formTemperatureString(bool outside = false);
    QString formPressureString();

    void updateTemperature();
    void updatePressure();
    void updateHumidity();
    void updatePower();
    void updateAirFlowDirection();
    void updateGraph();

    void updateStyles();
private slots:
    void handleIncreaseTemperature();
    void handleDecreaseTemperature();
    void handleTemperatureUnitsChange();

    void handleModeSwitch();
    void handlePowerSwitch();
    void handlePressureUnitsChange();
    void handleDirectionSliderValueChanged(int value);

    void handleGraphDataRequest();
};

#endif // MAINWINDOW_H
