import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: customLabel
    color: "#a7b7b6"
    property string labelText: ""
    radius: 10

    Column {
        spacing: 50
        anchors.centerIn: parent

        Text {
            text: customLabel.labelText
            font.family: "Microsoft Yahei"
            font.pointSize: 20
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            LineEdit {
                id: line
                width: 400
                height: 80
            }
            Text {
                text: "￥"
                font.pointSize: 24
                y: line.y
            }
        }

        Button {
            id: submitbtn
            Text {
                anchors.centerIn: parent
                text: "提交"
                color: "White"
                font.family: "Microsoft Yahei"
                font.pointSize: 18
            }

            width: 200
            height: 80
            anchors.horizontalCenter: parent.horizontalCenter
            background: Rectangle {
                color: "#738e95"
                radius: 20
            }
            flat: true
        }
    }
}
