
#include "info.h"

Info::Info(QWidget *parent)
    : QWidget{parent}
{
    int id = QFontDatabase::addApplicationFont(":/fonts/VictorMono-VariableFont_wght.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family);

    QLabel *temperature_label = new QLabel(tr("Температура: "));
    QLabel *humidity_label = new QLabel(tr("Влажность: "));
    QLabel *pressure_label = new QLabel(tr("Давление: "));

    temperature_label->setFont(monospace);
    humidity_label->setFont(monospace);
    pressure_label->setFont(monospace);

    temperature_label->setStyleSheet("font-size: 36px;");
    humidity_label->setStyleSheet("font-size: 36px;");
    pressure_label->setStyleSheet("font-size: 36px;");

    QLabel *temperature_value_label = new QLabel(tr("amogus"));
    QLabel *humidity_value_label = new QLabel();
    QLabel *pressure_value_label = new QLabel();

    temperature_value_label->setFont(monospace);
    humidity_value_label->setFont(monospace);
    pressure_value_label->setFont(monospace);

    temperature_value_label->setStyleSheet("font-size: 36px;");
    humidity_value_label->setStyleSheet("font-size: 36px;");
    pressure_value_label->setStyleSheet("font-size: 36px;");

    QHBoxLayout *layer1 = new QHBoxLayout;
    layer1->addWidget(temperature_label);
    layer1->addWidget(temperature_value_label);

    QHBoxLayout *layer2 = new QHBoxLayout;
    layer2->addWidget(humidity_label);
    layer2->addWidget(humidity_value_label);

    QHBoxLayout *layer3 = new QHBoxLayout;
    layer3->addWidget(pressure_label);
    layer3->addWidget(pressure_value_label);

    QFormLayout *main_layout = new QFormLayout;
    main_layout->addRow(layer1);
    main_layout->addRow(layer2);
    main_layout->addRow(layer3);
    setLayout(main_layout);
}

