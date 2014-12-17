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
                        //anchors.fill: parent
                        model : the_model.height() - forward
                        delegate :
                            Rectangle {
                            width: 64
                            height: 32
                            Rectangle {
                                height: 32
                                anchors {
                                    centerIn: parent
                                    topMargin: 0
                                    leftMargin: 30
                                }
                                width: 4
                                color : "gray"
                            }
                            Rectangle {
                                width: 64
                                anchors {
                                    centerIn: parent
                                    topMargin: 14
                                }
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


