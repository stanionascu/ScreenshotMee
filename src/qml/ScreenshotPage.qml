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

import QtQuick 1.1;
import com.nokia.meego 1.0;
import "../js/UI.js" as UI;
import QtMobility.sensors 1.1;

Page {
    id: screenshotPage;
    tools: commonTools;

    visible: screenshotAppWindow.visible;

    Label {
        visible: screenshot.source == "";
        id: statusLabel;
        anchors.fill: parent;
        text: qsTr("Cover device screen briefly to screenshot.\n");
        color: UI.FONT_SECONDARY_COLOR;
        font.pixelSize: UI.FONT_XLARGE;
        verticalAlignment: Qt.AlignVCenter;
        horizontalAlignment: Qt.AlignHCenter;
    }

    Image {
        id: screenshot;
        anchors.fill: parent;
        visible: false;
        fillMode: Image.PreserveAspectFit;
        Label {
            anchors.fill: parent;
            text: qsTr("Screenshot");
            color: UI.FONT_SECONDARY_COLOR;
            font.pixelSize: UI.FONT_XLARGE;
            verticalAlignment: Qt.AlignVCenter;
            horizontalAlignment: Qt.AlignHCenter;
        }
    }

    ToolIcon {
        id: settingsButton;
        platformIconId: "toolbar-settings";
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.rightMargin: 20;
        anchors.topMargin: 20;

        onClicked: {
            if (settingsSheet.status !== DialogStatus.Open)
                settingsSheet.open();
        }
    }

    ToolIcon {
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        platformIconId: "icon-m-image-edit-rotate-left";
        onClicked: screenshotPage.rotateScreenshot();

        visible: screenshot.visible;
    }

    ProximitySensor {
        id: proximitySensor;
        active: false;
        onReadingChanged: {
            if (reading.close && active) {
                screenshotTimer.start();
            } else {
                screenshotTimer.stop();
            }
        }
    }

    Timer {
        id: screenshotTimer;
        interval: 1000;
        repeat: false;
        running: false;
        triggeredOnStart: false;
        onTriggered: {
            makeScreenshot();
        }
    }

    SettingsSheet {
        id: settingsSheet;
    }

    Component.onCompleted: {
        screenshotTimer.stop();
        proximitySensor.active = true;
    }

    function makeScreenshot() {
        console.log("Screenshoting...");
        Helper.grabScreenshot();
        screenshot.visible = true;
        screenshotAppWindow.showToolBar = true;
        screenshot.source = "image://screenshot/" + Math.random();
        proximitySensor.active = false;
        Helper.raiseAppWindow();
    }

    function clearScreenshot() {
        screenshot.visible = false;
        screenshotAppWindow.showToolBar = false;
        screenshot.source = "";
        proximitySensor.active = true;
        Helper.hideAppWindow();
    }

    function saveScreenshot() {
        var fileName = Qt.formatDateTime(Helper.currentDateTime(), "yyyy-MM-dd_hh-mm-ss") + ".png";
        Helper.saveScreenshot(fileName);
        informationDialog.message = qsTr("Saved as") + " " + fileName;
        informationDialog.open();
    }

    function rotateScreenshot() {
        Helper.rotateScreenshot();
        screenshot.source = "image://screenshot/" + Math.random();
    }

    QueryDialog {
        id: informationDialog;
        titleText: qsTr("Screenshot saved");
        acceptButtonText: qsTr("OK");
    }
 }
