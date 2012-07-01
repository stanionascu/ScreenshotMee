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

#ifndef APPSERVICE_H
#define APPSERVICE_H

#include <QDBusAbstractAdaptor>

class Helper;

class AppService : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.ionascu.screenshotmee")
public:
    AppService(QObject *parent = 0);
    virtual ~AppService();

    void setHelper(Helper *h);

public Q_SLOTS:
    Q_NOREPLY void raiseWindow();

private:
    Helper *helper;
};

#endif // APPSERVICE_H
