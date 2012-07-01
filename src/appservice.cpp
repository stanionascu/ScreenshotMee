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

#include "appservice.h"
#include "helper.h"

AppService::AppService(QObject *parent) :
    QDBusAbstractAdaptor(parent),
    helper(0)
{
    setAutoRelaySignals(true);
}

AppService::~AppService()
{
}

void AppService::setHelper(Helper *h)
{
    helper = h;
}

void AppService::raiseWindow()
{
    helper->raiseAppWindow();
}
