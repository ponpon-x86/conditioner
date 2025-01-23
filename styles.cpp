#include "styles.h"

namespace styles {
    // light theme for temp module
    QString plus_button_light = ("QPushButton { background-color: #DCDBDB; color: #483F99; font-size: 50px; border: 0px; }"
                             "QPushButton:pressed { background-color: #FFFFFF; color: #483F99; font-size: 50px; border: 0px; } "
                             "QPushButton:disabled { background-color: #DCDBDB; color: #DCDBDB; font-size: 50px; border: 0px; } ");
    QString target_temperature_button_light = ("QPushButton { background-color: #483F99; color: #FFFFFF; font-size: 50px; border: 0px; }"
                                                "QPushButton:pressed { background-color: #FFFFFF; color: #483F99; font-size: 50px; border: 0px; } "
                                               "QPushButton:disabled { background-color: #483F99; color: #483F99; font-size: 50px; border: 0px; } ");
    QString real_temperature_label_light = ("font-size: 20px; color: #FFFFFF;");
    QString minus_button_light = ("QPushButton { background-color: #DCDBDB; color: #483F99; font-size: 50px; border: 0px; }"
                                  "QPushButton:pressed { background-color: #FFFFFF; color: #483F99; font-size: 50px; border: 0px; } "
                                  "QPushButton:disabled { background-color: #DCDBDB; color: #DCDBDB; font-size: 50px; border: 0px; } ");
    QString temperature_background_widget_light = ("background-color: #483F99;");
    // dark theme for temp module
    QString plus_button_dark = ("QPushButton { background-color: #282923; color: #F92472; font-size: 50px; border: 0px; }"
                                 "QPushButton:pressed { background-color: #111111; color: #F92472; font-size: 50px; border: 0px; } "
                                "QPushButton:disabled { background-color: #282923; color: #282923; font-size: 50px; border: 0px; } ");
    QString target_temperature_button_dark = ("QPushButton { background-color: #3C3D38; color: #F8F8F2; font-size: 50px; border: 0px; }"
                                               "QPushButton:pressed { background-color: #111111; color: #F92472; font-size: 50px; border: 0px; } "
                                              "QPushButton:disabled { background-color: #3C3D38; color: #3C3D38; font-size: 50px; border: 0px; } ");
    QString real_temperature_label_dark = ("font-size: 20px; color: #F8F8F2;");
    QString minus_button_dark = ("QPushButton { background-color: #282923; color: #F92472; font-size: 50px; border: 0px; }"
                                  "QPushButton:pressed { background-color: #111111; color: #F92472; font-size: 50px; border: 0px; } "
                                 "QPushButton:disabled { background-color: #282923; color: #282923; font-size: 50px; border: 0px; } ");
    QString temperature_background_widget_dark = ("background-color: #3C3D38;");


    // light theme for misc module
    QString utility_button_light = ("QPushButton { background-color: #FFF; color: #483F99; font-size: 50px; border: 0px; }"
                                 "QPushButton:pressed { background-color: #DCDBDB; color: #483F99; font-size: 50px; border: 0px; } ");
    QString humidity_button_light = ("QPushButton { background-color: #483F99; color: #FFFFFF; font-size: 30px; border: 0px; }"
                                     "QPushButton:disabled { background-color: #483F99; color: #483F99; font-size: 30px; border: 0px; }");
    QString power_button_light = ("QPushButton { background-color: #483F99; color: #FFFFFF; font-size: 30px; border: 0px; margin-top: 20px; margin-left: 20px; margin-right: 20px; }"
                                  "QPushButton:pressed { background-color: #FFFFFF; color: #483F99; font-size: 30px; border: 0px; margin-top: 20px; margin-left: 20px; margin-right: 20px; }");
    QString scene_light = ("background-color: transparent; margin-left:20px; margin-right:20px;");
    QString general_label_light = ("color: #483F99; font-size: 24px; margin:6px;");

    QString direction_slider_light = ("QSlider {"
                                      "    padding: 20px;"
                                      "}"
                                      " "
                                      "QSlider::groove:horizontal {"
                                      "    border: 1px solid #483F99;"
                                      "    height: 30px;"
                                      "}"
                                      " "
                                      "QSlider::handle:horizontal {"
                                      "    background: #ccc;"
                                      "    width: 30px;"
                                      "    margin: -1px -1px;"
                                      "    border: 5px solid #fff;"
                                      "}"
                                      "QSlider::handle:horizontal:disabled {"
                                      "    background: #ccc;"
                                      "    width: 30px;"
                                      "    margin: -1px -1px;"
                                      "    border: 5px solid #ccc;"
                                      "}"
                                      "QSlider::handle:horizontal:hover {"
                                      "    background: #fff;"
                                      "    border-color: #fff;"
                                      "}"
                                      " "
                                      "QSlider::add-page:horizontal {"
                                      "    background: #483F99;"
                                      "}"
                                      " "
                                      "QSlider::sub-page:horizontal {"
                                      "    background: #483F99;"
                                      "}");

    QString pressure_button_light = ("QPushButton { background-color: #483F99; color: #FFFFFF; font-size: 30px; border: 0px; }"
                                     "QPushButton:pressed { background-color: #FFFFFF; color: #483F99; font-size: 30px; border: 0px; } "
                                     "QPushButton:disabled { background-color: #483F99; color: #483F99; font-size: 30px; border: 0px; }");
    QString misc_background_widget_light = ("background-color: #DCDBDB;");
    // dark theme for misc module
    QString utility_button_dark = ("QPushButton { background-color: #222; color: #EE2D73; font-size: 50px; border: 0px; }"
                                 "QPushButton:pressed { background-color: #282923; color: #EE2D73; font-size: 50px; border: 0px; } ");
    QString humidity_button_dark = ("QPushButton { background-color: #3C3D38; color: #F8F8F2; font-size: 30px; border: 0px; } "
                                    "QPushButton:disabled { background-color: #3C3D38; color: #3C3D38; font-size: 30px; border: 0px; } ");
    QString power_button_dark = ("QPushButton { background-color: #3C3D38; color: #F8F8F2; font-size: 30px; border: 0px; margin-top: 20px; margin-left: 20px; margin-right: 20px; }"
                                  "QPushButton:pressed { background-color: #111111; color: #EE2D73; font-size: 30px; border: 0px; margin-top: 20px; margin-left: 20px; margin-right: 20px; }");
    QString scene_dark = ("background-color: transparent; margin-left:20px; margin-right:20px;");
    QString general_label_dark = ("color: #F8F8F2; font-size: 24px; margin:6px;");

    QString direction_slider_dark = ("QSlider {"
                                      "    padding: 20px;"
                                      "}"
                                      " "
                                      "QSlider::groove:horizontal {"
                                      "    border: 1px solid #F8F8F2;"
                                      "    height: 30px;"
                                      "}"
                                      " "
                                      "QSlider::handle:horizontal {"
                                      "    background: #282923;"
                                      "    width: 30px;"
                                      "    margin: -1px -1px;"
                                      "    border: 5px solid #111111;"
                                      "}"
                                     "QSlider::handle:horizontal:disabled {"
                                     "    background: #282923;"
                                     "    width: 30px;"
                                     "    margin: -1px -1px;"
                                     "    border: 5px solid #282923;"
                                     "}"
                                      "QSlider::handle:horizontal:hover {"
                                      "    background: #111111;"
                                      "    border-color: #EE2D73;"
                                      "}"
                                      " "
                                      "QSlider::add-page:horizontal {"
                                      "    background: #3C3D38;"
                                      "}"
                                      " "
                                      "QSlider::sub-page:horizontal {"
                                      "    background: #3C3D38;"
                                      "}");

    QString pressure_button_dark = ("QPushButton { background-color: #3C3D38; color: #F8F8F2; font-size: 30px; border: 0px; }"
                                     "QPushButton:pressed { background-color: #111111; color: #EE2D73; font-size: 30px; border: 0px; } "
                                    "QPushButton:disabled { background-color: #3C3D38; color: #3C3D38; font-size: 30px; border: 0px; } ");
    QString misc_background_widget_dark = ("background-color: #282923;");

    int scene_double_margin = 40;
}
