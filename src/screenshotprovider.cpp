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

#include "screenshotprovider.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

namespace {
    QImage g_lastScreenshotImage;
}

ScreenshotProvider::ScreenshotProvider() :
    QDeclarativeImageProvider(QDeclarativeImageProvider::Image)
{
}

ScreenshotProvider::~ScreenshotProvider()
{
}

QImage ScreenshotProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id);
    Q_UNUSED(requestedSize);

    *size = g_lastScreenshotImage.size();
    return g_lastScreenshotImage;
}

QImage ScreenshotProvider::lastScreenshotImage()
{
    return g_lastScreenshotImage;
}

void ScreenshotProvider::grabScreenshot()
{
    QPixmap screenshot = QPixmap::grabWindow(QApplication::desktop()->winId());
    QTransform transform;
    transform.rotate(90);
    g_lastScreenshotImage = screenshot.toImage().transformed(transform);
}

void ScreenshotProvider::rotateScreenshot()
{
    QTransform transform;
    transform.rotate(-90);
    g_lastScreenshotImage = g_lastScreenshotImage.transformed(transform);
}
