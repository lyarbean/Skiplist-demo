import QtQuick 2.3
import QtQuick.Window 2.2
import SkipListModel 1.0
Window {
    visible: true
    Component.onCompleted: {
        showMaximized();
    }

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
                            color: ["red", "orange", "yellow", "green", "blue", "indigo", "purple"][index]
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
            id:  the_skip_list
            width: parent.width - 64
            height: 300
            model: the_model
            focus: true
            orientation: Qt.Horizontal
            cacheBuffer: 10
            add: Transition {
                 NumberAnimation { properties: "x,y"; from: 100; duration: 1000 }
             }
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
        }

        Rectangle {
            color: "lightsteelblue"
            width: 128
            height: 32
            radius: 16
            TextInput{
                id : input_text
                anchors.centerIn: parent
                anchors.fill: parent
                Keys.onReturnPressed: {
                    the_model.addItem(text)
                    text = ""
                    the_skip_list.forceLayout()
                }
            }

        }
    }
}
//        Keys.onUpPressed:  {
//            the_skip_list.scale = the_skip_list.scale * 1.25
//        }
//        Keys.onDownPressed: {
//            the_skip_list.scale = the_skip_list.scale * 0.8
//        }




