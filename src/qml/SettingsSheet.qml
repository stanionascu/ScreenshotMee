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

import QtQuick 1.1
import com.nokia.meego 1.0;

Sheet {
    acceptButtonText: qsTr("Save");
    rejectButtonText: qsTr("Cancel");

    content: Flickable {
        id: flickable;
        anchors.fill: parent;
        anchors.topMargin: 24;
        anchors.leftMargin: 24;
        anchors.rightMargin: 24;
        contentHeight: settingsGroup.height;
        contentWidth: width;

        Item {
            id: settingsGroup;
            anchors.top: parent.top;
            anchors.left: parent.left;
            anchors.right: parent.right;
            height: picturesPathField.y + picturesPathField.height;

            CheckBox {
                id: autoHideCheckbox;
                anchors.top: parent.top;
                anchors.left: parent.left;
                text: qsTr("Automatically hide window");
                checked: Helper.autohideWindow;
            }

            Label {
                id: storagePathLabel;
                anchors.top: autoHideCheckbox.bottom;
                anchors.topMargin: 12;
                anchors.left: parent.left;
                anchors.right: parent.right;
               text: qsTr("Storage path:");
            }

            TextField {
                id: picturesPathField;
                anchors.top: storagePathLabel.bottom;
                anchors.topMargin: 12;
                anchors.left: parent.left;
                anchors.right: parent.right;
                text: Helper.picturesLocation;
            }
        }
    }

    onAccepted: {
        Helper.picturesLocation = picturesPathField.text;
        Helper.autohideWindow = autoHideCheckbox.checked;
    }
}
