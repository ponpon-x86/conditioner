
#include "imitationdialog.h"

ImitationDialog::ImitationDialog(QWidget *parent)
    : QDialog(parent)
{
    auto t_label = new QLabel(tr("Температура:"));
    temperature = new QLineEdit();
    auto p_label = new QLabel(tr("Давление:"));
    pressure = new QLineEdit();
    auto h_label = new QLabel(tr("Влажность:"));
    humidity = new QLineEdit();

    // default temp
    temperature->setText(QString::number(24));
    pressure->setText(QString::number(758));
    humidity->setText(QString::number(50));

    auto layout = new QVBoxLayout();
    layout->addWidget(t_label);
    layout->addWidget(temperature);
    layout->addWidget(p_label);
    layout->addWidget(pressure);
    layout->addWidget(h_label);
    layout->addWidget(humidity);

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
