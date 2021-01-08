import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15

import AbritesApp 1.0
import PolygonObjects 1.0

Window {
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height
    property int obsVisibleObjects: 0
    width: AbritesApp.roomSize.width + sidebar.width
    height: AbritesApp.roomSize.height
    visible: true
    title: qsTr("Damian's Abrites App")

    Rectangle {
        id: room
        width: AbritesApp.roomSize.width
        height: AbritesApp.roomSize.height
        color: "lightsteelblue"

        Rectangle {
            id: observer
            antialiasing: true
            x: AbritesApp.observerLocation.x
            y: AbritesApp.observerLocation.y
            width: 14
            height: 14
            color: "blue"
            transform: Rotation{
                id: rotationObs
                angle: -rotationOpt.value
                origin.x: 7; origin.y: 7;
            }
        }
        Rectangle {
            antialiasing: true
            anchors.top: observer.top
            anchors.horizontalCenter: observer.horizontalCenter
            color: "white"
            width: observer.width
            height: 3
            transform: Rotation{
                angle: -rotationOpt.value
                origin.x: 7; origin.y: 7;
            }
        }
        Rectangle {
            id: visibleArea
            color: "yellow"
            width: AbritesApp.visibleArea.width
            height: AbritesApp.visibleArea.height
            opacity: 0.3
            x: AbritesApp.visibleArea.x
            y: AbritesApp.visibleArea.y
        }

        PolygonObjects {
            width: room.width
            height: room.height
            Component.onCompleted: obsVisibleObjects = AbritesApp.getVisibleObjects(rotationOpt.value);
        }
    }

    Rectangle {
        id: sidebar
        anchors.right: parent.right
        width: 200
        height: parent.height
        color: "grey"
        Column {
            leftPadding: 10
            topPadding: 10
            Label {
                text: "Room Size: " + AbritesApp.roomSize.width + "x" + AbritesApp.roomSize.height
            }
            Label {
                text: "Observer Pos: " + AbritesApp.observerLocation.x + "x" + AbritesApp.observerLocation.y
            }
            Label {
                text: "Observer Rotation:"
            }

            ToolSeparator {orientation: Qt.Horizontal}
            SpinBox {
                id: rotationOpt
                editable: true
                from: 0
                to: 360
                onValueChanged: obsVisibleObjects = AbritesApp.getVisibleObjects(rotationOpt.value);
            }
            ToolSeparator {orientation: Qt.Horizontal}
            Label {
                text: "Observer can see: " + obsVisibleObjects + " objects"
            }
        }
    }
}
