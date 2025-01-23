#pragma once

#ifndef IMITATIONDIALOG_H
#define IMITATIONDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

/*!
 * \brief The ImitationDialog class is used to enter variables surrounding the AC
 *
 * The dialog is derived from QDialog and is used to enter the hypothetical
 * values of different parameters the AC might otherwise get from
 * some sort of hardware
 */
class ImitationDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * \brief ImitationDialog starts the data imitation dialog
     * \param temperature the temperature
     * \param humidity the humidity
     * \param pressure the pressure
     * \param parent widget's parent
     */
    ImitationDialog(QString temperature = "24", QString humidity = "50", QString pressure = "758", QWidget *parent = nullptr);

    /*!
     * \brief getTemperature is used to get the entered temp.
     * \return QString, the entered value
     *
     * Temperature is one of the values entered in QLineEdit by used in this dialog
     */
    QString getTemperature();

    /*!
     * \brief getPressure is used to get the entered pressure
     * \return QString, the entered pressure
     *
     * Pressure is one of the values entered in QLineEdit by used in this dialog
     */
    QString getPressure();

    /*!
     * \brief getHumidity is used to get the entered humidity level
     * \return QString, the humidity level
     *
     * Humidity is one of the values entered in QLineEdit by used in this dialog
     */
    QString getHumidity();
private:
    QLineEdit* temperature;
    QLineEdit* pressure;
    QLineEdit* humidity;

    QDialogButtonBox *buttonBox;
private slots:
};

#endif // IMITATIONDIALOG_H
