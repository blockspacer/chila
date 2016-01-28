import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item
{
    id: item1
    width: 640
    height: 480

    property alias button2: button2
    property alias button1: button1

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
                Layout.fillWidth: true
                Layout.fillHeight: true

                Tab {
                    title: "Red"
                    Rectangle { color: "red" }
                }
                Tab {
                    title: "Blue"
                    Rectangle { color: "blue" }
                }
                Tab {
                    title: "Green"
                    Rectangle { color: "green" }
                }
            }
        }


        RowLayout
        {
            Button {
                id: button3
                x: 187
                y: 187
                text: qsTr("Button")
            }

            Button {
                id: button4
                x: 187
                y: 187
                text: qsTr("Button")
            }
        }


    }

}
