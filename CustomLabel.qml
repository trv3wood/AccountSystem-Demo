import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: customLabel
    color: "transparent"
    property string labelText: ""
    radius: 10

    Column {
        anchors.centerIn: parent
        spacing: 100
        Text {
            text: customLabel.labelText
            font.family: "Microsoft Yahei"
            font.pointSize: 20
            color: "gray"
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
                font.pointSize: 20
                y: line.y
            }
        }

        SubmitBtn {
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
