
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
    timer->start(1000); // update every second

    // create all the labels & buttons
    mode_button = new QPushButton(tr("M"));
    humidity_button = new QPushButton(tr("ВЛАЖНОСТЬ // 50%"));
    power_button = new QPushButton(tr("ВЫКЛЮЧИТЬ КОНДИЦИОНЕР"));

    graphics_scene = new QGraphicsScene();
    view = new QGraphicsView(graphics_scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable scrollbars
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    direction_label = new QLabel(tr("НАПРАВЛЕНИЕ ПОДАЧИ ВОЗДУХА:"));
    direction_slider = new QSlider(Qt::Horizontal);
    pressure_button = new QPushButton(tr("ДАВЛЕНИЕ // 758 ММ РТ. СТ."));

    direction_slider->setRange(0, 100);
    direction_slider->setValue(50);

    // apply font to labels & buttons
    mode_button->setFont(monospace);
    humidity_button->setFont(monospace);
    power_button->setFont(monospace);
    direction_label->setFont(monospace);
    pressure_button->setFont(monospace);

    // set size for mode button
    mode_button->setFixedWidth(50);
    mode_button->setFixedHeight(50);

    // set height for humidity button
    humidity_button->setFixedHeight(50);

    // set height for pressure button
    pressure_button->setFixedHeight(50);

    // set height for direction label
    direction_label->setFixedHeight(24);

    // set height for direction label
    power_button->setFixedHeight(100);

    // now to set the styles...
    mode_button->setStyleSheet(styles::mode_button_light);
    humidity_button->setStyleSheet(styles::humidity_button_light);
    power_button->setStyleSheet(styles::power_button_light);
    view->setStyleSheet(styles::scene_light);
    pressure_button->setStyleSheet(styles::pressure_button_light);
    direction_label->setStyleSheet(styles::direction_label_light);
    direction_slider->setStyleSheet(styles::direction_slider_light);

    direction_label->setAlignment(Qt::AlignCenter);

    // connect buttons to signals
    connect(mode_button, &QPushButton::clicked, this, &Misc::modeSwitch);
    connect(power_button, &QPushButton::clicked, this, &Misc::powerSwitch);
    connect(pressure_button, &QPushButton::clicked, this, &Misc::changePressureUnits);
    // connect slider
    connect(direction_slider, &QSlider::valueChanged, this, &Misc::directionSliderValueChanged);
    // the idea is the misc module on main window will request a regular update
    // which can be handled by main window, since main window holds Conditioner data.
    connect(timer, &QTimer::timeout, this, &Misc::graphDataRequest);

    // now, create the layout and put everything created in intended order
    main_layout = new QGridLayout(this);

    main_layout->addWidget(mode_button, 0, 0);
    main_layout->addWidget(humidity_button, 0, 1);
    // 1, 2 as last arguments mean span 1 row, 2 cols
    main_layout->addWidget(power_button, 1, 0, 1, 2);
    main_layout->addWidget(view, 2, 0, 1, 2);
    main_layout->addWidget(direction_label, 3, 0, 1, 2);
    main_layout->addWidget(direction_slider, 4, 0, 1, 2);
    main_layout->addWidget(pressure_button, 5, 0, 1, 2);

    // ...then set the margins to 0 for intended look
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
}

void Misc::updatePressure(QString string) {
    pressure_button->setText(string);
}

void Misc::updatePower(QString string) {
    power_button->setText(string);
}

void Misc::updateAirFlowDirection(int value) {
    direction_slider->setValue(value);
}

void Misc::switchStyles(bool light) {
    if (light) {
        mode_button->setStyleSheet(styles::mode_button_light);
        humidity_button->setStyleSheet(styles::humidity_button_light);
        power_button->setStyleSheet(styles::power_button_light);
        view->setStyleSheet(styles::scene_light);
        pressure_button->setStyleSheet(styles::pressure_button_light);
        direction_label->setStyleSheet(styles::direction_label_light);
        direction_slider->setStyleSheet(styles::direction_slider_light);
    } else {
        mode_button->setStyleSheet(styles::mode_button_dark);
        humidity_button->setStyleSheet(styles::humidity_button_dark);
        power_button->setStyleSheet(styles::power_button_dark);
        view->setStyleSheet(styles::scene_dark);
        pressure_button->setStyleSheet(styles::pressure_button_dark);
        direction_label->setStyleSheet(styles::direction_label_dark);
        direction_slider->setStyleSheet(styles::direction_slider_dark);
    }
}

void Misc::updateGraph(int target_t, int outside_t, bool light_mode, bool working) {
    // update time and add new data point
    time_elapsed += 1.0; // assuming 1 unit of time per update
    target_points.append(QPointF(time_elapsed, target_t));
    outside_points.append(QPointF(time_elapsed, outside_t));

    // remove old points to keep the graph within bounds
    if (target_points.size() > 50) { // limit graph to last 50 points
        target_points.remove(0);
    }
    if (outside_points.size() > 50) {
        outside_points.remove(0);
    }

    // clear the scene and redraw the graph
    graphics_scene->clear();

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
    // in order for the scene's view to look OKish
    // there are -margins- in its style
    // however
    // they seem to break scene's width and height.
    // so now we are forced to consider those. tough luck.
    qreal center_y = (view->height() - styles::scene_double_margin) / 2;  // fixed Y for the X-axis (center line)
    graphics_scene->addLine(0, center_y, (view->width() - styles::scene_double_margin), center_y, QPen(Qt::gray));  // x-axis
    for (int i = -60; i <= 60; i += 20)
        graphics_scene->addLine(0, center_y + i, (view->width() - styles::scene_double_margin), center_y + i, QPen(Qt::gray));  // additional x-axis
    graphics_scene->addLine(50, 0, 50, view->height(), QPen(Qt::gray));   // y-axis

    // attempting to normalize the x-coordinates
    qreal start_time = target_points.first().x();

    // draw the graph
    for (int i = 1; i < target_points.size(); ++i) {
        QPointF tp1 = target_points[i - 1];
        QPointF tp2 = target_points[i];

        QPointF op1 = outside_points[i - 1];
        QPointF op2 = outside_points[i];

        // scale
        double scale = (static_cast<double>(view->width()) - static_cast<double>(styles::scene_double_margin)) / 50.;

        // map points to scene coordinates (flip y-axis for temperature)
        qreal x1 = (tp1.x() - start_time) * scale;       // scale x-axis
        qreal y1 = center_y - tp1.y();    // flip and offset y-axis
        qreal x2 = (tp2.x() - start_time) * scale;
        qreal y2 = center_y - tp2.y();

        Qt::GlobalColor pen;
        if (working)
            pen = light_mode ? Qt::blue : Qt::green;
        else pen = Qt::gray;

        graphics_scene->addLine(x1, y1, x2, y2, QPen(pen, 2));

        x1 = (op1.x() - start_time) * scale;        // scale x-axis
        y1 = center_y - op1.y();    // flip and offset y-axis
        x2 = (op2.x() - start_time) * scale;
        y2 = center_y - op2.y();

        graphics_scene->addLine(x1, y1, x2, y2, QPen(Qt::red, 2));
    }
}

void Misc::updateHumidity(QString value) {
    humidity_button->setText(value);
}
