
#include "loader.h"

bool Loader::saveParamsToXML(const QString& filename, Conditioner::ConditionerParams params, bool light_mode) {
    QDomDocument doc;
    QDomElement root = doc.createElement("Conditioner");
    doc.appendChild(root);

    // Add fields as XML elements
    root.appendChild(createElement(doc, "Temperature", QString::number(params.temperature)));
    root.appendChild(createElement(doc, "TemperatureUnit", enumToString(params.t_unit)));
    root.appendChild(createElement(doc, "PressureUnit", enumToString(params.p_unit)));
    // these parameters are not changable, so we don't actually need to save these
    // root.appendChild(createElement(doc, "OutsideTemperature", QString::number(params.outside_temperature)));
    // root.appendChild(createElement(doc, "Humidity", QString::number(params.humidity)));
    // root.appendChild(createElement(doc, "Pressure", QString::number(params.pressure)));
    root.appendChild(createElement(doc, "Working", params.working ? "true" : "false"));
    root.appendChild(createElement(doc, "Direction", QString::number(params.direction)));
    root.appendChild(createElement(doc, "LightMode", QString::number(static_cast<int>(light_mode))));

    // Save XML to file
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error writing to file " << filename << ".";
        return false;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();

    return true;
}

QDomElement Loader::createElement(QDomDocument &doc, const QString &tag_name, const QString &text) {
    QDomElement element = doc.createElement(tag_name);
    QDomText text_node = doc.createTextNode(text);
    element.appendChild(text_node);
    return element;
}

// Convert enums to string
QString Loader::enumToString(const Conditioner::TemperatureUnits unit) {
    switch (unit) {
        case Conditioner::TemperatureUnits::CELSIUS: return "Celsius";
        case Conditioner::TemperatureUnits::FAHRENHEIT: return "Fahrenheit";
        case Conditioner::TemperatureUnits::KELVIN: return "Kelvin";
        default: return "Unknown"; // just in case.
    }
}

QString Loader::enumToString(const Conditioner::PressureUnits unit) {
    switch (unit) {
        case Conditioner::PressureUnits::MERCURY: return "Mercury";
        case Conditioner::PressureUnits::PASCALS: return "Pascals";
        default: return "Unknown"; // just in case.
    }
}

Conditioner::TemperatureUnits Loader::stringToTemperatureUnit(const QString &str) {
    if (str == "Celsius") {
        return Conditioner::TemperatureUnits::CELSIUS;
    } else if (str == "Fahrenheit") {
        return Conditioner::TemperatureUnits::FAHRENHEIT;
    } else if (str == "Kelvin") {
        return Conditioner::TemperatureUnits::KELVIN;
    }
    qDebug() << "Unknown TemperatureUnit: " << str << "; returning Celsius since it's the most common.";
    return Conditioner::TemperatureUnits::CELSIUS; // Default
}

// Convert string to PressureUnits
Conditioner::PressureUnits Loader::stringToPressureUnit(const QString &str) {
    if (str == "Mercury") {
        return Conditioner::PressureUnits::MERCURY;
    } else if (str == "Pascals") {
        return Conditioner::PressureUnits::PASCALS;
    }
    qDebug() << "Unknown PressureUnit: " << str << "; returning in mercury millimiters since they're the most common.";
    return Conditioner::PressureUnits::MERCURY; // Default
}

std::pair<Conditioner::ConditionerParams, bool> Loader::loadParamsFromXML(const QString &fileName) {
    // in case there would be an error, there's some default parameters
    Conditioner::ConditionerParams params;
    params.temperature = 21;
    params.t_unit = Conditioner::TemperatureUnits::CELSIUS;
    params.p_unit = Conditioner::PressureUnits::MERCURY;
    params.working = true;
    params.direction = 0;
    // there are default values for changable parameters around the air conditioner
    // these were not saved, but are present and hence assigned here
    params.outside_temperature = 24;
    params.humidity = 50;
    params.pressure = 758;

    bool light_mode = true;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading: " << fileName << "; returning default parameters.";
        return { params, light_mode };
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "Failed to parse the XML file; returning default parameters.";
        file.close();
        return { params, light_mode };
    }
    file.close();

    QDomElement root = doc.documentElement();
    if (root.tagName() != "Conditioner") {
        qDebug() << "Unexpected root element (expected Conditioner): " << root.tagName() << "; returning default parameters.";
        return { params, light_mode };
    }

    // Parse each child element
    QDomElement element = root.firstChildElement();
    while (!element.isNull()) {
        QString tag = element.tagName();
        QString value = element.text();

        if (tag == "Temperature") {
            params.temperature = value.toInt();
        } else if (tag == "TemperatureUnit") {
            params.t_unit = stringToTemperatureUnit(value);
        } else if (tag == "PressureUnit") {
            params.p_unit = stringToPressureUnit(value);
        } else if (tag == "Working") {
            params.working = (value == "true");
        } else if (tag == "Direction") {
            params.direction = value.toUInt();
        } else if (tag == "LightMode") {
            light_mode = value.toUInt();
        } else {
            qDebug() << "(Note) Unknown element: " << tag;
        }

        element = element.nextSiblingElement();
    }

    return { params, light_mode } ;
}
