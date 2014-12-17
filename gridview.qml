import QtQuick 2.3
import QtQuick.Window 2.2
//import SkipListModel 1.0
import SkipListItemModel 1.0
Window {
    // delay to show
    visible: false
    Component.onCompleted: {

        show();
    }
    minimumHeight: 480
    minimumWidth: 480
    // SkipListModel {
    SkipListItemModel {
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
            cacheBuffer: 1
            add: Transition {
                NumberAnimation { properties: "x,y"; from: 100; duration: 1000 }
            }
            delegate: Column {
                spacing: 8
                Text {
                    width: 64
                    color: "#333333"
                    text: index + ":" + (element ? element : "")
                    font.bold: true
                }
                Rectangle {
                    width: 64
                    height: forward * 32
                    color: ["red", "orange", "yellow", "green", "blue", "indigo", "purple"][forward % 7]
                }
                Rectangle {
                    width: 64
                    height: (the_model.height() - forward) * 32
                    ListView {
                        anchors.fill: parent
                        model : the_model.height() - forward
                        delegate :
                            Rectangle {
                            height: 32
                            Rectangle {
                                width: 64
                                anchors.leftMargin: 0
                                anchors.topMargin: 30
                                color : "gray"
                                height: 4
                            }
                        }
                    }
                    // color: ["red", "orange", "yellow", "green", "blue", "indigo", "purple"][forward % 7]
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
                    timer.start()
                }
            }
            Timer {
                id: timer
                interval: 500;
                running: false; repeat: true
                onTriggered: {
                    the_skip_list.forceLayout()
                    stop()
                }
            }
        }
    }
}


