
#include "temperature.h"

Temperature::Temperature(QWidget *parent)
    : QWidget{parent}
{
    // load the desired font
    int id = QFontDatabase::addApplicationFont(":/fonts/UbuntuMono-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family);

    // create all the labels & buttons
    plus_button = new QPushButton(tr("+"));
    target_temperature_button = new QPushButton(tr("21°С"));
    real_temperature_label = new QLabel(tr("СНАРУЖИ 24°С"));
    minus_button = new QPushButton(tr("-"));

    // apply font to labels
    plus_button->setFont(monospace);
    target_temperature_button->setFont(monospace);
    real_temperature_label->setFont(monospace);
    minus_button->setFont(monospace);

    // set sizes for + button
    plus_button->setMaximumWidth(275);
    plus_button->setMaximumHeight(50);

    // these are empty widgets, their purpose is to fill the space
    // in vertical layout of the Temperature widget so that
    // the temperature numbers would be centered
    upper_filler = new QWidget();
    lower_filler = new QWidget();

    // set sizes for temp. number
    target_temperature_button->setMaximumWidth(275);
    target_temperature_button->setMaximumHeight(90);

    // set sizes for another temp. number
    real_temperature_label->setMaximumWidth(275);
    real_temperature_label->setMaximumHeight(20);

    // set sizes for - button
    minus_button->setMaximumWidth(275);
    minus_button->setMaximumHeight(50);

    // i want the buttons to be of plain white color
    // with blue-ish text on them, so
    plus_button->setStyleSheet(styles::plus_button_light);
    //plus_button->setAlignment(Qt::AlignCenter);

    // the following would look a bit crooked and slightly not-so-intended
    // but since the time is of the essence, it should suffice
    target_temperature_button->setStyleSheet(styles::target_temperature_button_light);

    real_temperature_label->setStyleSheet(styles::real_temperature_label_light);
    real_temperature_label->setAlignment(Qt::AlignCenter);

    // again, i want the buttons to be of plain white color
    // with blue-ish text on them, so
    minus_button->setStyleSheet(styles::minus_button_light);
    //minus_button->setAlignment(Qt::AlignCenter);

    // since layout is not a qwidget, it is impossible to change its background color;
    // and i want the background of Temperature module to be blue-ish
    // so i'll just put a widget of solid color and of maximum possible height there
    // to serve as a background
    widget = new QWidget(this);
    widget->setGeometry(0, 0, 275, 768);
    widget->setStyleSheet(styles::temperature_background_widget_light);
    widget->show();

    // connect the buttons to signals
    connect(plus_button, &QPushButton::clicked, this, &Temperature::increaseTemperature);
    connect(minus_button, &QPushButton::clicked, this, &Temperature::decreaseTemperature);
    connect(target_temperature_button, &QPushButton::clicked, this, &Temperature::changeTemperatureUnits);

    // now, create the layout and put everything created in intended order
    main_layout = new QVBoxLayout(this);
    main_layout->addWidget(plus_button);

    main_layout->addWidget(upper_filler);

    main_layout->addWidget(target_temperature_button);
    main_layout->addWidget(real_temperature_label);

    main_layout->addWidget(lower_filler);

    main_layout->addWidget(minus_button);

    // ...then set the margins to 0 for intended look
    main_layout->setContentsMargins(0, 0, 0, 0);
}

void Temperature::updateTemperature(QString string, bool outside) {
    if (outside)
        real_temperature_label->setText(tr("СНАРУЖИ ") + string);
    else
        target_temperature_button->setText(string);
}

void Temperature::switchStyles(bool light) {
    if (light) {
        plus_button->setStyleSheet(styles::plus_button_light);
        target_temperature_button->setStyleSheet(styles::target_temperature_button_light);
        real_temperature_label->setStyleSheet(styles::real_temperature_label_light);
        minus_button->setStyleSheet(styles::minus_button_light);
        widget->setStyleSheet(styles::temperature_background_widget_light);
    } else {
        plus_button->setStyleSheet(styles::plus_button_dark);
        target_temperature_button->setStyleSheet(styles::target_temperature_button_dark);
        real_temperature_label->setStyleSheet(styles::real_temperature_label_dark);
        minus_button->setStyleSheet(styles::minus_button_dark);
        widget->setStyleSheet(styles::temperature_background_widget_dark);
    }
}

void Temperature::updatePower(bool working) {
    // AC doesn't work!?!?
    // burn the fields
    if (!working) {
        plus_button->setEnabled(false);
        minus_button->setEnabled(false);
        target_temperature_button->setEnabled(false);
        real_temperature_label->setText("");
    } else {
        plus_button->setEnabled(true);
        minus_button->setEnabled(true);
        target_temperature_button->setEnabled(true);
    }
}
