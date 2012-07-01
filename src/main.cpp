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

#include <QtGui/QApplication>
#include <QtDeclarative>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusPendingCall>
#include <applauncherd/MDeclarativeCache>

#include "screenshotprovider.h"
#include "helper.h"
#include "appservice.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication *app = MDeclarativeCache::qApplication(argc, argv);

    AppService *service = NULL;
    QDBusConnection dbus(QDBusConnection::sessionBus());
    if (!dbus.registerService("com.ionascu.screenshotmee")) {
        QDBusInterface interface("com.ionascu.screenshotmee", "/Application");
        interface.asyncCall("raiseWindow");
        qWarning() << "The application is already running... Raising window and quitting...";
        return 0;
    } else {
        service = new AppService(app);
        dbus.registerObject("/Application", app);
        qDebug() << "Registered at:" << "com.ionascu.screenshotmee";
    }

    QDeclarativeView *view = MDeclarativeCache::qDeclarativeView();

    Helper *helper = new Helper;
    helper->registerWindow(view);
    service->setHelper(helper);

    view->engine()->addImageProvider("screenshot", new ScreenshotProvider);
    view->engine()->rootContext()->setContextProperty("Helper", helper);
    view->setSource(QUrl("qrc:/qml/main.qml"));
    view->showFullScreen();

    int result = app->exec();
    delete helper;

    return result;
}
