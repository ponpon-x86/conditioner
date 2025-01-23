
#include "misc.h"

Misc::Misc(QWidget *parent)
    : QWidget{parent}
{
    // load the desired font
    int id = QFontDatabase::addApplicationFont(":/fonts/UbuntuMono-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family);

    // this one will be needed for graphs
    timer = new QTimer(this);
    time_elapsed = 0;
    timer->start(100); // update every second

    // create all the labels & buttons
    mode_button = new QPushButton(tr("M"));
    humidity_button = new QPushButton(tr("ВЛАЖНОСТЬ // 50%"));
    power_button = new QPushButton(tr("ВЫКЛЮЧИТЬ КОНДИЦИОНЕР"));

    temperature_scene = new QGraphicsScene();
    temperature_view = new QGraphicsView(temperature_scene);
    temperature_view->setRenderHint(QPainter::Antialiasing);
    temperature_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable scrollbars
    temperature_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    humidity_scene = new QGraphicsScene();
    humidity_view = new QGraphicsView(humidity_scene);
    humidity_view->setRenderHint(QPainter::Antialiasing);
    humidity_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable scrollbars
    humidity_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    pressure_scene = new QGraphicsScene();
    pressure_view = new QGraphicsView(pressure_scene);
    pressure_view->setRenderHint(QPainter::Antialiasing);
    pressure_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable scrollbars
    pressure_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    direction_label = new QLabel(tr("НАПРАВЛЕНИЕ ПОДАЧИ ВОЗДУХА:"));
    direction_slider = new ValueSlider(Qt::Horizontal);
    settings_button = new QPushButton(tr("S"));
    pressure_button = new QPushButton(tr("ДАВЛЕНИЕ // 758 ММ РТ. СТ."));

    direction_slider->setRange(-75, 75);
    direction_slider->setValue(0);

    // apply font to labels & buttons
    mode_button->setFont(monospace);
    settings_button->setFont(monospace);
    humidity_button->setFont(monospace);
    power_button->setFont(monospace);
    direction_label->setFont(monospace);
    pressure_button->setFont(monospace);

    temperature_label = new QLabel(tr("ТЕМПЕРАТУРА"));
    humidity_label = new QLabel(tr("ВЛАЖНОСТЬ"));
    pressure_label = new QLabel(tr("ДАВЛЕНИЕ"));

    temperature_label->setFont(monospace);
    humidity_label->setFont(monospace);
    pressure_label->setFont(monospace);

    // set size for mode button
    mode_button->setFixedWidth(50);
    mode_button->setFixedHeight(50);

    // same for settings button
    settings_button->setFixedWidth(50);
    settings_button->setFixedHeight(50);

    // set height for humidity button
    humidity_button->setFixedHeight(50);

    // set height for pressure button
    pressure_button->setFixedHeight(50);

    // set height for labels
    temperature_label->setFixedHeight(40);
    humidity_label->setFixedHeight(40);
    pressure_label->setFixedHeight(40);
    direction_label->setFixedHeight(40);

    // set height for direction label
    power_button->setFixedHeight(100);

    // now to set the styles...
    mode_button->setStyleSheet(styles::utility_button_light);
    humidity_button->setStyleSheet(styles::humidity_button_light);
    power_button->setStyleSheet(styles::power_button_light);

    temperature_view->setStyleSheet(styles::scene_light);
    humidity_view->setStyleSheet(styles::scene_light);
    pressure_view->setStyleSheet(styles::scene_light);

    settings_button->setStyleSheet(styles::utility_button_light);
    pressure_button->setStyleSheet(styles::pressure_button_light);

    direction_label->setStyleSheet(styles::general_label_light);
    humidity_label->setStyleSheet(styles::general_label_light);
    temperature_label->setStyleSheet(styles::general_label_light);
    pressure_label->setStyleSheet(styles::general_label_light);

    direction_slider->setStyleSheet(styles::direction_slider_light);

    direction_label->setAlignment(Qt::AlignCenter);
    humidity_label->setAlignment(Qt::AlignCenter);
    temperature_label->setAlignment(Qt::AlignCenter);
    pressure_label->setAlignment(Qt::AlignCenter);

    // connect buttons to signals
    connect(mode_button, &QPushButton::clicked, this, &Misc::modeSwitch);
    connect(settings_button, &QPushButton::clicked, this, &Misc::settingsCalled);
    connect(power_button, &QPushButton::clicked, this, &Misc::powerSwitch);
    connect(pressure_button, &QPushButton::clicked, this, &Misc::changePressureUnits);
    // connect slider
    connect(direction_slider, &QSlider::valueChanged, this, &Misc::directionSliderValueChanged);
    // the idea is the misc module on main window will request a regular update
    // which can be handled by main window, since main window holds Conditioner data.
    connect(timer, &QTimer::timeout, this, &Misc::graphDataRequest);

    // now, create the layout and put everything created in intended order
    main_layout = new QGridLayout(this);
    head_layout = new QHBoxLayout();
    foot_layout = new QHBoxLayout();

    head_layout->addWidget(mode_button);
    head_layout->addWidget(humidity_button);

    //main_layout->addWidget(mode_button, 0, 0, 1, 1);
    //main_layout->addWidget(humidity_button, 0, 1, 1, 2);
    main_layout->addLayout(head_layout, 0, 0, 1, 2);
    // 1, 2 as last arguments mean span 1 row, 2 cols
    main_layout->addWidget(power_button, 1, 0, 1, 2);
    main_layout->addWidget(temperature_label, 2, 0, 1, 2);
    main_layout->addWidget(temperature_view, 3, 0, 1, 2);
    main_layout->addWidget(humidity_label, 4, 0, 1, 1);
    main_layout->addWidget(humidity_view, 5, 0, 1, 1);
    main_layout->addWidget(pressure_label, 4, 1, 1, 1);
    main_layout->addWidget(pressure_view, 5, 1, 1, 1);
    main_layout->addWidget(direction_label, 6, 0, 1, 2);
    main_layout->addWidget(direction_slider, 7, 0, 1, 2);

    foot_layout->addWidget(settings_button);
    foot_layout->addWidget(pressure_button);
    main_layout->addLayout(foot_layout, 8, 0, 1, 2);

    // ...then set the margins to 0 for intended look
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
}

void Misc::updatePressure(QString string) {
    pressure_button->setText(string);
}

void Misc::updatePower(QString string, bool working) {
    power_button->setText(string);

    // AC doesn't work!?!?
    // hide everything from the user in the name of god!!
    if (!working) {
        pressure_button->setEnabled(false);
        humidity_button->setEnabled(false);
        direction_slider->setEnabled(false);
        updateGraph(0,0,0,0,0,0);
    } else {
        pressure_button->setEnabled(true);
        humidity_button->setEnabled(true);
        direction_slider->setEnabled(true);
    }
}

void Misc::updateAirFlowDirection(int value) {
    direction_slider->setValue(value);
}

void Misc::switchStyles(bool light) {
    direction_slider->setMode(light);
    if (light) {
        mode_button->setStyleSheet(styles::utility_button_light);
        humidity_button->setStyleSheet(styles::humidity_button_light);
        power_button->setStyleSheet(styles::power_button_light);
        temperature_view->setStyleSheet(styles::scene_light);
        pressure_button->setStyleSheet(styles::pressure_button_light);
        direction_label->setStyleSheet(styles::general_label_light);
        direction_slider->setStyleSheet(styles::direction_slider_light);
        temperature_label->setStyleSheet(styles::general_label_light);
        humidity_label->setStyleSheet(styles::general_label_light);
        pressure_label->setStyleSheet(styles::general_label_light);
        settings_button->setStyleSheet(styles::utility_button_light);
    } else {
        mode_button->setStyleSheet(styles::utility_button_dark);
        humidity_button->setStyleSheet(styles::humidity_button_dark);
        power_button->setStyleSheet(styles::power_button_dark);
        temperature_view->setStyleSheet(styles::scene_dark);
        pressure_button->setStyleSheet(styles::pressure_button_dark);
        direction_label->setStyleSheet(styles::general_label_dark);
        direction_slider->setStyleSheet(styles::direction_slider_dark);
        temperature_label->setStyleSheet(styles::general_label_dark);
        humidity_label->setStyleSheet(styles::general_label_dark);
        pressure_label->setStyleSheet(styles::general_label_dark);
        settings_button->setStyleSheet(styles::utility_button_dark);
    }
}

void Misc::updateGraph(int target_t, int outside_t, int pressure, int humidity, bool light_mode, bool working) {
    // AC doesn't work?? quick, hide everything!!
    if (!working) {
        t_target_points.clear();
        t_outside_points.clear();
        h_points.clear();
        p_points.clear();

        temperature_scene->clear();
        humidity_scene->clear();
        pressure_scene->clear();

        humidity_label->setText("ВЛАЖНОСТЬ");
        pressure_label->setText("ДАВЛЕНИЕ");

        time_elapsed = 0;
        return;
    }

    // update time and add new data point
    time_elapsed += 1.0; // assuming 1 unit of time per update
    t_target_points.append(QPointF(time_elapsed, target_t));
    t_outside_points.append(QPointF(time_elapsed, outside_t));
    h_points.append(QPointF(time_elapsed, - (this->average_humidity - humidity)));
    p_points.append(QPointF(time_elapsed, - (this->average_pressure - pressure)));

    humidity_label->setText("ВЛАЖНОСТЬ // " + QString::number(humidity) + "%");
    pressure_label->setText("ДАВЛЕНИЕ // " + QString::number(pressure) + " ММ РТ.СТ.");

    // remove old points to keep the graph within bounds
    if (t_target_points.size() > 50) { // limit graph to last 50 points
        t_target_points.remove(0);
    }
    if (t_outside_points.size() > 50) {
        t_outside_points.remove(0);
    }
    if (h_points.size() > 50) {
        h_points.remove(0);
    }
    if (p_points.size() > 50) {
        p_points.remove(0);
    }

    // clear the scene and redraw the graph
    temperature_scene->clear();
    humidity_scene->clear();
    pressure_scene->clear();

    // singular, unsettling fragments of documentation suggested that QGraphicsScene
    // itself was a gateway to some ancient and unnameable complexity

    // with countless hours of trial and error, i bent every effort towards understanding
    // this archaic tool, exhausting what remained of my sanity as i wrestled
    // with obscure references and baffling examples.

    // at last, buried deep within the tangled hieroglyphs of Qt’s documentation,
    // i unearthed something resembling a solution — a disjointed mess of code that
    // somehow, against all reason, began to function. every line I wrote seemed to
    // unsettle the very framework, as though I were trespassing in a realm of arcane UI
    // constructs. in the end, i alone sat perplexed, wailing through those blackened arcades of antiquity,
    // marveling the infinite profanity and the absurdity of it

    // draw axes (optional)

    // alright so
    // in order for the scene's temperature_view to look OKish
    // there are -margins- in its style
    // however
    // they seem to break scene's width and height.
    // so now we are forced to consider those. tough luck.
    qreal center_y = (temperature_view->height()) / 2;  // fixed Y for the X-axis (center line)
    temperature_scene->addLine(0, center_y, (temperature_view->width()), center_y, QPen(Qt::gray));  // x-axis
    for (int i = -40; i <= 40; i += 20)
        temperature_scene->addLine(0, center_y + i, (temperature_view->width()), center_y + i, QPen(Qt::gray));  // additional x-axis
    temperature_scene->addLine(50, 0, 50, temperature_view->height(), QPen(Qt::gray));   // y-axis

    pressure_scene->addLine(0, center_y, (pressure_view->width()), center_y, QPen(Qt::gray));  // x-axis
    for (int i = -40; i <= 40; i += 20)
        pressure_scene->addLine(0, center_y + i, (pressure_view->width()), center_y + i, QPen(Qt::gray));  // additional x-axis
    pressure_scene->addLine(50, 0, 50, pressure_view->height(), QPen(Qt::gray));   // y-axis

    humidity_scene->addLine(0, center_y, (humidity_view->width()), center_y, QPen(Qt::gray));  // x-axis
    for (int i = -40; i <= 40; i += 20)
        humidity_scene->addLine(0, center_y + i, (humidity_view->width()), center_y + i, QPen(Qt::gray));  // additional x-axis
    humidity_scene->addLine(50, 0, 50, humidity_view->height(), QPen(Qt::gray));   // y-axis

    // attempting to normalize the x-coordinates
    qreal start_time = t_target_points.first().x();

    // draw the graph
    for (int i = 1; i < t_target_points.size(); ++i) {
        QPointF tp1 = t_target_points[i - 1];
        QPointF tp2 = t_target_points[i];

        QPointF op1 = t_outside_points[i - 1];
        QPointF op2 = t_outside_points[i];

        QPointF hp1 = h_points[i - 1];
        QPointF hp2 = h_points[i];

        QPointF pp1 = p_points[i - 1];
        QPointF pp2 = p_points[i];

        // scale
        double t_scale = (static_cast<double>(temperature_view->width()) - static_cast<double>(styles::scene_double_margin)) / 50.;
        double h_scale = (static_cast<double>(humidity_view->width()) - static_cast<double>(styles::scene_double_margin)) / 50.;
        double p_scale = (static_cast<double>(pressure_view->width()) - static_cast<double>(styles::scene_double_margin)) / 50.;

        // map points to scene coordinates (flip y-axis for temperature)
        qreal x1 = (tp1.x() - start_time) * t_scale;       // scale x-axis
        qreal y1 = center_y - tp1.y();    // flip and offset y-axis
        qreal x2 = (tp2.x() - start_time) * t_scale;
        qreal y2 = center_y - tp2.y();

        Qt::GlobalColor pen;
        if (working)
            pen = light_mode ? Qt::blue : Qt::green;
        else pen = Qt::gray;

        temperature_scene->addLine(x1, y1, x2, y2, QPen(pen, 2));

        x1 = (op1.x() - start_time) * t_scale;        // scale x-axis
        y1 = center_y - op1.y();    // flip and offset y-axis
        x2 = (op2.x() - start_time) * t_scale;
        y2 = center_y - op2.y();

        temperature_scene->addLine(x1, y1, x2, y2, QPen(Qt::red, 2));

        x1 = (hp1.x() - start_time) * h_scale;        // scale x-axis
        y1 = center_y - hp1.y();    // flip and offset y-axis
        x2 = (hp2.x() - start_time) * h_scale;
        y2 = center_y - hp2.y();

        humidity_scene->addLine(x1, y1, x2, y2, QPen(Qt::red, 2));

        x1 = (pp1.x() - start_time) * p_scale;        // scale x-axis
        y1 = center_y - pp1.y();    // flip and offset y-axis
        x2 = (pp2.x() - start_time) * p_scale;
        y2 = center_y - pp2.y();

        pressure_scene->addLine(x1, y1, x2, y2, QPen(Qt::red, 2));
    }
}

void Misc::updateHumidity(QString value) {
    humidity_button->setText(value);
}
