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

    ListView {
        width: 1360
        height: 100
        model: the_model
        anchors.fill: parent
        orientation : Qt.Horizontal
        delegate:
            Rectangle {
            width: 80
            color: "gray"
            radius: 5
            Column {
                Text {
                    text : model.index
                }
                Text {
                    text : model.element
                }
                Text {
                    text : model.forward()
                }
            }
        }
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
        MouseArea {
            anchors.fill: parent
            onClicked : {
                the_model.addItem (Math.round(Math.random() * 1e5 ) % 1e4)
                console.log ("Count " + the_model.rowCount())
            }
        }
    }

}
