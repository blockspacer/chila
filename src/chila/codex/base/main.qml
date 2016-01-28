/* Copyright 2005-2015 Roberto Daniel Gimenez Gamarra (chilabot@gmail.com)
 * (C.I.: 1.439.390 - Paraguay)
 */

import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: myWindow
    title: qsTr("Hello World")
    x: 500
    y: 200
    width: 800
    height: 600
    visible: true
    onClosing: winClosing()

    signal winClosing()
    signal tabSwitched(variant tab)

    // Internal ---------------------------------------------------------------------------------------------------------------------
    QtObject
    {
        id: internal
        property variant topMenus: [ menu00, menu01, menu02, menu03, menu04,
                                     menu05, menu06, menu07, menu08, menu09,
                                     menu10, menu11, menu12, menu13, menu14,
                                     menu15, menu16, menu17, menu18, menu19 ]
        property int currMenu: 0
        property variant menuAssoc: ({})
        property variant currTextEdit

        function addActionM(menu, path, index, actionData)
        {
            if (index === path.length)
            {
                if (!actionData.name)
                {
                    menu.addSeparator();
                }
                else
                {
                    var actionStr =
                        'import QtQuick.Controls 1.4\n' +
                        'import QtQuick 2.4\n' +
                        'Action\n' +
                        '{\n' +
                            'text: "' + actionData.text + '"\n' +
                            'shortcut: ' + actionData.shortcut + '\n' +
                            'tooltip: "' + actionData.tooltip + '"\n' +
                        '}';

                    //console.log(actionStr);

                    var action = Qt.createQmlObject(actionStr, myWindow, "");

                    var menuItem = menu.addItem(actionData.name);
                    menuItem.objectName = actionData.name;
                    menuItem.text = actionData.text;
                    menuItem.action = action;

                    return action;
                }
            }
            else
            {
                var pathItem = path[index];

                var childMenu;

                for (var ind in menu.items)
                {
                    var child = menu.items[ind];
                    if (child.objectName === pathItem.name)
                        childMenu = child;
                }

                if (!childMenu)
                {
                    childMenu = menu.addMenu(pathItem.text);
                    childMenu.objectName = pathItem.name;
                }

                return addActionM(childMenu, path, index + 1, actionData);
            }
        }

        function testAddMenus()
        {
            var fileMenuPath = [{name: "file", text: "File"}];
            var fileNewAction = addAction(fileMenuPath, { name: "new", text: "&New", tooltip: "New file", shortcut: "'Ctrl+T'" } );
            addAction(fileMenuPath, { name: "open", text: "&Open", tooltip: "Open file.", shortcut: StandardKey.Open } );
            addAction(fileMenuPath, { });
            addAction(fileMenuPath, { name: "quit", text: "&Quit", tooltip: "Quit.", shortcut: StandardKey.Quit } );

            var editMenuPath = [{name: "edit", text: "Edit"}];
            addAction(editMenuPath, { name: "copy", text: "Copy", tooltip: "Copy text.", shortcut: StandardKey.Copy } );
            addAction(editMenuPath, { name: "paste", text: "Paste", tooltip: "Paste text.", shortcut: StandardKey.Paste } );
            addAction(editMenuPath, { name: "cut", text: "Cut", tooltip: "Cut text.", shortcut: StandardKey.Cut } );

            var editTestPath = editMenuPath;
            editMenuPath.push({name: "test", text: "Test"});

            addAction(editTestPath, { name: "test0", text: "Test0" } );
            addAction(editTestPath, { name: "test1", text: "Test1" } );
            addAction(editTestPath, { name: "test2", text: "Test2" } );

            var editTestPath2 = editMenuPath;
            editTestPath2.push({name: "test3", text: "Test3"});

            addAction(editTestPath2, { name: "test0", text: "Test0" } );
            addAction(editTestPath2, { name: "test1", text: "Test1" } );
            addAction(editTestPath2, { name: "test2", text: "Test2" } );

            fileNewAction.triggered.connect(function(source)
            {
                console.log("test");
            });
        }

        function assert(condition)
        {
            if (!condition)
                throw new Error("Assertion failed");
        }
    }

    // Functions --------------------------------------------------------------------------------------

    function addAction(path, actionData)
    {
        var pathItem = path[0];

        var menu = menuBar.addMenu(pathItem.name, pathItem.text);
        return internal.addActionM(menu, path, 1, actionData);
    }

    function setTriggered(action, fun)
    {
        action.triggered.connect(fun);
    }

    property int nextInd: 0;

    function addTab(name, component)
    {
        var tab = tabView.addTab(name, component);
        tab.active = true;

        return tab;
    }

    function removeTab(tab)
    {
        tabView.removeTab(getTabIndex(tab));
    }

    function getTabIndex(tab)
    {
        for (var index = 0; index < tabView.count; ++index)
        {
            if (tab === tabView.getTab(index))
                return index;
        }
        console.error("Tab not found");
    }

    function selectTab(tab)
    {
        tabView.currentIndex = getTabIndex(tab);
    }

    function showSaveAsDialog()
    {
        saveAsFileDialog.open();
        return saveAsFileDialog;
    }

    function showOpenDialog()
    {
        openFileDialog.open();
        return openFileDialog;
    }

    // Widgets -------------------------------------------------------------------------------------

    menuBar: MenuBar
    {
        id: menuBar

        Menu { id: menu00; visible: false; }
        Menu { id: menu01; visible: false; }
        Menu { id: menu02; visible: false; }
        Menu { id: menu03; visible: false; }
        Menu { id: menu04; visible: false; }
        Menu { id: menu05; visible: false; }
        Menu { id: menu06; visible: false; }
        Menu { id: menu07; visible: false; }
        Menu { id: menu08; visible: false; }
        Menu { id: menu09; visible: false; }
        Menu { id: menu10; visible: false; }
        Menu { id: menu11; visible: false; }
        Menu { id: menu12; visible: false; }
        Menu { id: menu13; visible: false; }
        Menu { id: menu14; visible: false; }
        Menu { id: menu15; visible: false; }
        Menu { id: menu16; visible: false; }
        Menu { id: menu17; visible: false; }
        Menu { id: menu18; visible: false; }
        Menu { id: menu19; visible: false; }

        function addMenu(name, text)
        {
            var menu = internal.menuAssoc[name];

            if (!menu)
            {
                if (internal.currMenu == internal.topMenus.length)
                    console.log("Maximum top menus reached");
                else
                {
                    menu = internal.topMenus[internal.currMenu++];
                    menu.objectName = name;
                    menu.visible = true;
                    menu.title = text;

                    internal.menuAssoc[name] = menu;

                    return menu;
                }
            }

            return menu;
        }

        function getPathFirstRest(path)
        {
            var pos = path.indexOf(".");
            var first = path.substring(0, pos);
            var rest = path.substring(pos + 1);
            return [ first, rest ];
        }
    }

    ColumnLayout
    {
        id: columnLayout1
        height: 182
        anchors.fill: parent

        RowLayout
        {
            id: rowLayout1
            anchors.fill: parent
            ColumnLayout
            {
                Button {
                    id: button1
                    x: 187
                    y: 187
                    text: qsTr("Button")
                }

                Button {
                    id: button2
                    x: 187
                    y: 187
                    text: qsTr("Button")
                }
            }

            TabView
            {
                id: tabView
                Layout.fillWidth: true
                Layout.fillHeight: true

                onCurrentIndexChanged: tabSwitched(getTab(currentIndex))

                style: TabViewStyle
                {
                    frameOverlap: 1
                    tabsMovable: true
                    tab: Rectangle
                    {
                        objectName: "rectangle"
                        border.color:  styleData.selected ? "lightgray" : "lightgray"
                        color:  styleData.selected ? "white" : "lightgray"
                        implicitWidth: Math.max(text.width + 4, 80)
                        implicitHeight: 25
                        radius: 2

                        Text
                        {
                            id: text
                            anchors.centerIn: parent
                            text: styleData.title
                            color: styleData.selected ? "black" : "black"
                        }
                    }

                    frame: Rectangle
                    {
                        color: "white"
                    }
                }
            }
        }

        RowLayout
        {
            Button {
                id: button3
                x: 187
                y: 187
                text: qsTr("Button3")
                onClicked:
                {
                    var component = Qt.createComponent("TextItems.qml");
                    var textItems = component.createObject();
                    textItems.saveDialogQuestion.visible = true;
                }
            }

            Button {
                id: button4
                x: 187
                y: 187
                text: qsTr("Button4")

                onClicked:
                {
                    var component = Qt.createComponent("TextItems.qml");
                    var textItems = component.createObject();
                    var tab = addTab("test", textItems.textArea);
                }
            }
        }
    }

    statusBar: StatusBar {
        Row {
            anchors.fill: parent
            Label { text: "Read Only" }
        }
    }

    FileDialog
    {
        id: openFileDialog
        title: "Open file"
        selectMultiple: true
    }

    FileDialog
    {
        id: saveAsFileDialog
        title: "Save file"
    }

}


