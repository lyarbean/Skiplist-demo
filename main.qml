import QtQuick 2.3
import QtQuick.Window 2.2
import SkipListModel 1.0

Window {
    visible: true
    width: 360
    height: 360
    SkipListModel {
        id: the_model
    }

    Component {
        id: forwardDelegate
        Column {
            property int offset: 0
            property alias model: repeater.model
            spacing: 8
            Repeater {
                id: repeater
                delegate: Row {
                    spacing: 24
                    Rectangle {
                        height: 24
                        radius: 5
                        color: ["red", "orange", "yellow", "green", "blue", "indigo", "purple"][index]
                        width: 28
                        Rectangle {
                            x: parent.x + 24
                            y: parent.y + 12
                            height: 2
                            color: "gray"
                            width: modelData < 0 ? 0 : (modelData - offset) * 32
                        }
                        Text {
                            anchors.centerIn: parent
                            font.pointSize: 12
                            text: modelData < 0 ? "x" : modelData
                            color: index > 2 ? "white" : "black"
                            font.bold: true
                        }
                    }
                }
            }
        }
    }
    Column {
        anchors.fill: parent
        anchors.leftMargin: 32
        spacing: 64
        ListView {
            id: the_skip_list
            width: parent.width - 64
            height: 300
            model: the_model
            //anchors.centerIn: parent
            orientation: Qt.Horizontal
            cacheBuffer: 10
            delegate: Column {
                spacing: 8
                Text {
                    id: offsetRect
                    width: 32
                    color: "#333333"
                    text: model.offset
                    font.bold: true
                }
                Text {
                    id: eleRect
                    width: 32
                    color: "#444444"
                    text: model.element
                }
                Loader {
                    id: forward_loader
                    sourceComponent: forwardDelegate
                    onStatusChanged: {
                        item.model = model.forward
                        item.offset = model.offset
                    }
                }
            }
            focus: true
        }
        Rectangle {
            color: "lightsteelblue"
            width: 128
            height: 64
            radius: 16
            Text {
                text: "Add"
                color: "black"
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    the_model.addItem(Math.round(Math.random() * 1e5) % 1e4)
                    console.log("Count " + the_model.rowCount())
                    the_skip_list.model = null
                    the_skip_list.model = the_model
                }
            }
        }
    }
}
