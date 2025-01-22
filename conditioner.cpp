
#include "conditioner.h"

Conditioner::Conditioner() {
    this->params.temperature = 21;
    this->params.t_unit = TemperatureUnits::CELSIUS;
    this->params.p_unit = PressureUnits::MERCURY;

    this->params.outside_temperature = 24;

    this->params.humidity = 50;
    this->params.pressure = 758;
    this->params.working = true;
    this->params.direction = 0;
}

void Conditioner::setTemperature(signed temperature, bool outside) {
    if (outside) this->params.outside_temperature = temperature;
    else this->params.temperature = temperature;
}

void Conditioner::cycleTemperatureUnits() {

    // yes, it could have been done with operator++ overload
    // however i decided
    // -responsibly-
    // to be modest

    switch(this->params.t_unit) {
    case TemperatureUnits::CELSIUS:
        this->params.t_unit = TemperatureUnits::FAHRENHEIT; break;
    case TemperatureUnits::FAHRENHEIT:
        this->params.t_unit = TemperatureUnits::KELVIN; break;
    case TemperatureUnits::KELVIN:
        this->params.t_unit = TemperatureUnits::CELSIUS; break;
    }
}

signed Conditioner::getTemperature(bool outside) {
    auto t = outside == false ? this->params.temperature : this->params.outside_temperature;
    switch (this->params.t_unit) {
    case TemperatureUnits::CELSIUS:
        return t;
    case TemperatureUnits::FAHRENHEIT:
        return static_cast<double>(t) * 1.8 + 32.;
    case TemperatureUnits::KELVIN:
        return static_cast<double>(t) + 273.15;
    }
}

std::string Conditioner::getTemperatureUnits() {
    switch (this->params.t_unit) {
    case TemperatureUnits::CELSIUS:
        return "°C";
    case TemperatureUnits::FAHRENHEIT:
        return "°F";
    case TemperatureUnits::KELVIN:
        return "°K";
    }
}

void Conditioner::cyclePressureUnits() {

    // same old

    switch(this->params.p_unit) {
    case PressureUnits::MERCURY:
        this->params.p_unit = PressureUnits::PASCALS; break;
    case PressureUnits::PASCALS:
        this->params.p_unit = PressureUnits::MERCURY; break;
    }
}

unsigned Conditioner::getPressure() {
    switch (this->params.p_unit) {
    case PressureUnits::MERCURY:
        return this->params.pressure;
    case PressureUnits::PASCALS:
        return static_cast<double>(this->params.pressure) * 133.3;
    }
}

std::string Conditioner::getPressureUnits() {
    switch (this->params.p_unit) {
    case PressureUnits::MERCURY:
        return "ММ РТ. СТ.";
    case PressureUnits::PASCALS:
        return "Па";
    }
}

Conditioner::ConditionerParams Conditioner::getParams() {
    return this->params;
}

void Conditioner::setParams(Conditioner::ConditionerParams params) {
    this->params = params;
}
