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

PageStackWindow {
    id: screenshotAppWindow;

    initialPage: screenshotPage;
    platformStyle: PageStackWindowStyle {
        background: UI.PAGE_EMPTY_BACKGROUND;
    }
    showStatusBar: false;
    showToolBar: false;

    ScreenshotPage {
        id: screenshotPage;
    }

    ToolBarLayout {
        id: commonTools;
        visible: true;

        ToolButtonRow {
            visible: commonTools.visible;
            ToolButton {
                text: qsTr("Save");
                visible: commonTools.visible;
                onClicked: screenshotPage.saveScreenshot();
            }
            ToolButton {
                text:  qsTr("Make New");
                visible: commonTools.visible;
                onClicked: screenshotPage.clearScreenshot();
            }
        }
    }

    Component.onCompleted: {
        theme.inverted = true;
    }

    states: [
        State {
            name: "hidden"
            when: platformWindow.viewMode === WindowState.Thumbnail && !showToolBar && Helper.autohideWindow;
            StateChangeScript {
                script: {
                    Helper.hideAppWindow();
                }
            }
        }
    ]
}
