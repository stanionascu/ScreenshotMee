/*************************************************************************
 * This file is part of Screenshot Mee! for Nokia N9.
 * Copyright (C) 2012 Stanislav Ionascu <stanislav.ionascu@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QDateTime>

class QSettings;

class Helper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString picturesLocation READ picturesLocation WRITE setPicturesLocation NOTIFY picturesLocationChanged)
    Q_PROPERTY(bool autohideWindow READ autohideWindow WRITE setAutohideWindow NOTIFY autohideWindowChanged)
public:
    Helper(QObject *parent = 0);
    virtual ~Helper();

    Q_INVOKABLE QDateTime currentDateTime();
    Q_INVOKABLE void raiseAppWindow();
    Q_INVOKABLE void hideAppWindow();
    Q_INVOKABLE void rotateScreenshot();
    Q_INVOKABLE void grabScreenshot();

    void registerWindow(QWidget *window);

    QString picturesLocation();
    void setPicturesLocation(const QString &path);

    bool autohideWindow();
    void setAutohideWindow(bool value);

Q_SIGNALS:
    void picturesLocationChanged();
    void autohideWindowChanged();

public Q_SLOTS:
    void saveScreenshot(const QString &fileName);

private:
    QWidget *appWindow;
    QSettings *settings;
};

#endif // HELPER_H
