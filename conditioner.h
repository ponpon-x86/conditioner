#pragma once

#ifndef CONDITIONER_H
#define CONDITIONER_H

#include <string>

/*!
 * \brief The Conditioner class holds parameter for supposed conditioner
 *
 * The Conditioner class describes the air conditioner unit and holds additional parameters
 * that can be altered.
 */
class Conditioner
{
public:
    /*!
     * \brief Conditioner constructor sets default parameters
     */
    Conditioner();
    ~Conditioner() = default;

    /*!
     * \brief The TemperatureUnits enum provides temperature units options
     */
    enum class TemperatureUnits {
        CELSIUS,
        FAHRENHEIT,
        KELVIN
    };

    /*!
     * \brief The PressureUnits enum provides pressure units options
     */
    enum class PressureUnits {
        MERCURY,
        PASCALS
    };

    /*!
     * \brief The ConditionerParams struct holds parameters of AC unit
     *
     * The ConditionerParams struct holds all possible parameters of air conditioner unit
     * and its surroundings.
     */
    struct ConditionerParams {
        signed temperature;
        TemperatureUnits t_unit;
        PressureUnits p_unit;

        signed outside_temperature;

        unsigned humidity;
        unsigned pressure;
        bool working;
        unsigned direction;
    };

    /*!
     * \brief cycleTemperatureUnits switches between available temperature units
     */
    void cycleTemperatureUnits();

    /*!
     * \brief getTemperatureUnits is used to get currently selected temp. unit
     * \return string, temp. unit name
     */
    std::string getTemperatureUnits();

    /*!
     * \brief getTemperature is used to get current temperature
     * \param outside is a flag which marks if return value should be target temp. or an outside temp.
     * \return signed int, temperature
     */
    signed getTemperature(bool outside = false);

    /*!
     * \brief setTemperature sets temperature value
     * \param temperature the temperature
     * \param outside a flag which markes whether the outside temp. or target AC temp is being set
     */
    void setTemperature(signed temperature, bool outside);

    /*!
     * \brief increaseTemperature increments AC's temperature by 1
     */
    void increaseTemperature() { if (this->params.temperature < 50) this->params.temperature++; };

    /*!
     * \brief decreaseTemperature decrements AC's temperature by 1
     */
    void decreaseTemperature() { if (this->params.temperature > -50) this->params.temperature--; };



    /*!
     * \brief getHumidity is used to get humidity level
     * \return unsigned int, current humidity level
     */
    unsigned getHumidity() { return this->params.humidity; };

    /*!
     * \brief setHumidity is used to set humidity level
     * \param humidity, humidity level
     */
    void setHumidity(unsigned humidity) { this->params.humidity = humidity; };



    /*!
     * \brief cyclePressureUnits is used to cycle between available pressure units
     */
    void cyclePressureUnits();

    /*!
     * \brief getPressureUnits is used to get currently selected pressure units
     * \return string, pressure unit name
     */
    std::string getPressureUnits();

    /*!
     * \brief getPressure is used to get current pressure
     * \return unsigned int, current pressure
     */
    unsigned getPressure();

    /*!
     * \brief setPressure is used to set pressure
     * \param pressure, the pressure value
     */
    void setPressure(unsigned pressure) { this->params.pressure = pressure; };



    /*!
     * \brief isWorking is used to get info whether AC is working
     * \return bool, flag that indicates whether AC is working
     */
    bool isWorking() { return this->params.working; };

    /*!
     * \brief setWorking is used to set a working flag
     * \param working flag to be set
     */
    void setWorking(bool working) { this->params.working = working; };



    /*!
     * \brief getDirection is used to get the direction of AC's air flow
     * \return unsinged int, the abstract direction
     */
    unsigned getDirection() { return this->params.direction; };

    /*!
     * \brief setDirection is used to set the direction of AC's air flow
     * \param direction, the direction
     */
    void setDirection(unsigned direction) { this->params.direction = direction; };



    /*!
     * \brief getParams is used to get all AC params
     * \return ConditionerParams, the param struct
     */
    ConditionerParams getParams();

    /*!
     * \brief setParams is used to set AC params
     */
    void setParams(ConditionerParams);
private:
    ConditionerParams params;
};

#endif // CONDITIONER_H
