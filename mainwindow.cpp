
#include "mainwindow.h"

#include <QTabWidget>
#include "temperature.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto loaded = loader.loadParamsFromXML("params.xml");
    conditioner.setParams(loaded.first);
    light_mode = loaded.second;

    this->resize(800, 600);

    this->setMinimumWidth(800);
    this->setMinimumHeight(600);

    this->setMaximumWidth(1024);
    this->setMaximumHeight(768);

    bkg = new QWidget(this);
    bkg->setGeometry(0, 0, 1024, 768);
    // bkg->show();

    // set layout in QWidget
    window = new QWidget();

    // set QWidget as the central layout of the main window
    setCentralWidget(window);

    misc = new Misc(this);
    temperature = new Temperature(this);
    temperature->setFixedWidth(275);

    updateStyles();

    // connect signals to slots
    connect(temperature, &Temperature::increaseTemperature, this, &MainWindow::handleIncreaseTemperature);
    connect(temperature, &Temperature::decreaseTemperature, this, &MainWindow::handleDecreaseTemperature);
    connect(temperature, &Temperature::changeTemperatureUnits, this, &MainWindow::handleTemperatureUnitsChange);
    connect(misc, &Misc::modeSwitch, this, &MainWindow::handleModeSwitch);
    connect(misc, &Misc::settingsCalled, this, &MainWindow::handleSettingsCall);
    connect(misc, &Misc::powerSwitch, this, &MainWindow::handlePowerSwitch);
    connect(misc, &Misc::changePressureUnits, this, &MainWindow::handlePressureUnitsChange);
    connect(misc, &Misc::directionSliderValueChanged, this, &MainWindow::handleDirectionSliderValueChanged);
    connect(misc, &Misc::graphDataRequest, this, &MainWindow::handleGraphDataRequest);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0); // remove margins
    layout->setSpacing(0); // no spacing between widgets

    // add widgets to the layout
    layout->addWidget(misc);            // stretchable widget
    layout->addWidget(temperature);     // fixed-width widget

    // set the stretch factor
    layout->setStretch(0, 1); // this one will stretch
    layout->setStretch(1, 0); // this one will not stretch

    window->setLayout(layout);

    updateTemperature();
    updatePressure();
    updatePower();
    updateAirFlowDirection();
}

MainWindow::~MainWindow()
{
    loader.saveParamsToXML("params.xml", conditioner.getParams(), light_mode);
}

QString MainWindow::formTemperatureString(bool outside) {
    QString value;
    value = QString::number(conditioner.getTemperature(outside));
    value += QString::fromUtf8(conditioner.getTemperatureUnits().c_str());
    return value;
}

QString MainWindow::formPressureString() {
    QString value = "ДАВЛЕНИЕ // ";
    value += QString::number(conditioner.getPressure());
    value += " ";
    value += QString::fromUtf8(conditioner.getPressureUnits().c_str());
    return value;
}

void MainWindow::updateTemperature() {
    auto working = conditioner.isWorking();
    if (!working) return;
    temperature->updateTemperature(this->formTemperatureString());
    temperature->updateTemperature(this->formTemperatureString(true), true);
}

void MainWindow::updateHumidity() {
    QString value = "ВЛАЖНОСТЬ // ";
    value += QString::number(conditioner.getHumidity());
    value += "%";
    misc->updateHumidity(value);
}

void MainWindow::handleIncreaseTemperature() {
    qDebug() << "Temperature increased.";
    conditioner.increaseTemperature();
    updateTemperature();
}

void MainWindow::handleDecreaseTemperature() {
    qDebug() << "Temperature decreased.";
    conditioner.decreaseTemperature();
    updateTemperature();
}

void MainWindow::handleTemperatureUnitsChange() {
    qDebug() << "Cycling t units.";
    conditioner.cycleTemperatureUnits();
    updateTemperature();
}

void MainWindow::handlePowerSwitch() {
    qDebug() << "Switching power.";
    conditioner.setWorking( !conditioner.isWorking() );
    updatePower();
    // at first the idea was to update graph immideately
    // however this triggeres an addition of a point to graph
    // which can be of course bypassed,
    // however the task lacks specification in that regard
    // so the idea is dropped for now.

    // updateGraph();
}

void MainWindow::handlePressureUnitsChange() {
    qDebug() << "Cycling p units.";
    conditioner.cyclePressureUnits();
    updatePressure();
}

void MainWindow::handleModeSwitch() {
    qDebug() << "Cycling modes.";
    light_mode = !light_mode;
    updateStyles();
    // updateGraph();
}

void MainWindow::updateStyles() {
    temperature->switchStyles(light_mode);
    misc->switchStyles(light_mode);
    QString bkg_style = light_mode ? "background-color: #DCDBDB;" : "background-color: #282923;";
    bkg->setStyleSheet(bkg_style);
}

void MainWindow::updatePower() {
    QString value = conditioner.isWorking() ? "ВЫКЛЮЧИТЬ " : "ВКЛЮЧИТЬ ";
    value += "КОНДИЦИОНЕР";
    misc->updatePower(value, conditioner.isWorking());
    temperature->updatePower(conditioner.isWorking());
    if (conditioner.isWorking()) updateTemperature();
}

void MainWindow::updatePressure() {
    misc->updatePressure(this->formPressureString());
}

void MainWindow::handleDirectionSliderValueChanged(int value) {
    conditioner.setDirection(value);
    qDebug() << "Air flow direction changed.";
}

void MainWindow::updateAirFlowDirection() {
    misc->updateAirFlowDirection( conditioner.getDirection() );
}

void MainWindow::updateGraph() {
    auto data = conditioner.getParams();
    misc->updateGraph( data.temperature , data.outside_temperature , data.pressure, data.humidity, light_mode , data.working );
}

void MainWindow::handleGraphDataRequest() {
    updateGraph();
    qDebug() << "Updating graph.";
}

void MainWindow::handleSettingsCall() {
    auto params = conditioner.getParams();
    ImitationDialog dialog(QString::number(params.outside_temperature),
                           QString::number(params.humidity),
                           QString::number(params.pressure), this);
    if (dialog.exec() == QDialog::Accepted) {
        // the dialog was accepted
        conditioner.setHumidity(dialog.getHumidity().toUInt());
        conditioner.setPressure(dialog.getPressure().toUInt());
        conditioner.setTemperature(dialog.getTemperature().toInt(), true);

        updatePressure();
        updateTemperature();
        updateHumidity();
    } else {
        // the dialog was rejected
    }
}
