
#include "imitationdialog.h"

ImitationDialog::ImitationDialog(QString temperature, QString humidity, QString pressure, QWidget *parent)
    : QDialog(parent)
{
    auto t_label = new QLabel(tr("Температура:"));
    this->temperature = new QLineEdit();
    auto p_label = new QLabel(tr("Давление:"));
    this->pressure = new QLineEdit();
    auto h_label = new QLabel(tr("Влажность:"));
    this->humidity = new QLineEdit();

    // default temp
    this->temperature->setText(temperature);
    this->pressure->setText(pressure);
    this->humidity->setText(humidity);

    auto layout = new QVBoxLayout();
    layout->addWidget(t_label);
    layout->addWidget(this->temperature);
    layout->addWidget(p_label);
    layout->addWidget(this->pressure);
    layout->addWidget(h_label);
    layout->addWidget(this->humidity);

    resize(300, 150);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    layout->addWidget(buttonBox);
    setLayout(layout);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    setWindowTitle(tr("Imitation Dialog"));
}

QString ImitationDialog::getTemperature() {
    return temperature->text();
}

QString ImitationDialog::getHumidity() {
    return humidity->text();
}

QString ImitationDialog::getPressure() {
    return pressure->text();
}
