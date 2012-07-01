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

#include "helper.h"

#include "screenshotprovider.h"

#include <QDesktopServices>
#include <QDir>
#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QDesktopWidget>
#include <QSettings>

Helper::Helper(QObject *parent) :
    QObject(parent),
    appWindow(0),
    settings(new QSettings("ionascu", "screenshotmee", this))
{
    settings->setIniCodec("UTF-8");
}

Helper::~Helper()
{
}

QDateTime Helper::currentDateTime()
{
    return QDateTime::currentDateTime();
}

void Helper::grabScreenshot()
{
    ScreenshotProvider::grabScreenshot();
}

void Helper::saveScreenshot(const QString &fileName)
{
    QString path = picturesLocation() + QDir::separator() + fileName;
    qDebug() << "Dumping image to" << path;
    ScreenshotProvider::lastScreenshotImage().save(path);
}

void Helper::rotateScreenshot()
{
    if (ScreenshotProvider::lastScreenshotImage().isNull())
        return;

    ScreenshotProvider::rotateScreenshot();
}

void Helper::registerWindow(QWidget *window)
{
    appWindow = window;
}

void Helper::raiseAppWindow()
{
    if (appWindow) {
        appWindow->showFullScreen();
        appWindow->raise();
    }
}

void Helper::hideAppWindow()
{
    if (appWindow) {
        appWindow->hide();
    }
}

QString Helper::picturesLocation()
{
    QVariant value = settings->value("PicturesPath");
    if (!value.isValid())
        return QDesktopServices::storageLocation(QDesktopServices::PicturesLocation);
    else
        return value.toString();
}

void Helper::setPicturesLocation(const QString &path)
{
    settings->setValue("PicturesPath", path);
    emit autohideWindowChanged();
}

bool Helper::autohideWindow()
{
    QVariant value = settings->value("AutohideWindow");
    if (value.isValid())
        return value.toBool();
    return false;
}

void Helper::setAutohideWindow(bool value)
{
    settings->setValue("AutohideWindow", value);
    emit autohideWindowChanged();
}
