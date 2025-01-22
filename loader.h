
#ifndef LOADER_H
#define LOADER_H


#include <QObject>
#include "conditioner.h"

#include <QDebug>

#include <QDomDocument>
#include <QFile>
#include <QTextStream>

/*!
 * \brief The Loader class is used to interact with XML format
 *
 * This class is used to write and read AC unit parameters to/from an XML file
 */
class Loader
{
public:
    Loader() = default;
    ~Loader() = default;

    // this one saves params to xml
    /*!
     * \brief saveParamsToXML is used to save parameters to a XML file
     * \return bool, whether the operation was successful
     *
     * the method takes QString, the file to which to write, params of the AC and a flag
     * which marks whether the light theme is used or not
     */
    bool saveParamsToXML(const QString&, Conditioner::ConditionerParams, bool);

    // helper method to create elements
    /*!
     * \brief createElement is used to create an XML element to write to document
     * \return QDomElement, an XML element
     *
     * the method takes the XML document, QString, a tag name, and QString, the text
     */
    QDomElement createElement(QDomDocument&, const QString&, const QString&);

    // convert enums to string
    /*!
     * \brief enumToString is used to convert a variable of enum type (temp. unit) to QString
     * \return QString, a temperature unit
     */
    QString enumToString(const Conditioner::TemperatureUnits);

    /*!
     * \brief enumToString is used to convert a variable of enum type (pressure unit) to QString
     * \return QString, a pressure unit
     */
    QString enumToString(const Conditioner::PressureUnits);

    // backwards thing
    /*!
     * \brief stringToTemperatureUnit is used to convert QString to enum type (temp. unit)
     * \return temperature unit
     */
    Conditioner::TemperatureUnits stringToTemperatureUnit(const QString &);

    /*!
     * \brief stringToPressureUnit is used to convert QString to enum type (pressure unit)
     * \return pressure unit
     */
    Conditioner::PressureUnits stringToPressureUnit(const QString &str);

    // load xml
    /*!
     * \brief loadParamsFromXML is used to load AC unit parameters from a XML file
     * \return std pair, first is parameters, second is a flag whether the light mode is used
     */
    std::pair<Conditioner::ConditionerParams, bool> loadParamsFromXML(const QString&);
};

#endif // LOADER_H
