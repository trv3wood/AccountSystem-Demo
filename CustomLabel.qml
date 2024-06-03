import QtQuick 2.15

Rectangle {
    id: customLabel
    color: "#a7b7b6"
    property string labelText: ""
    radius: 10
    Text {
        text: customLabel.labelText
        font.family: "Microsoft Yahei"
        font.pointSize: 20
        color: "white"
        anchors.centerIn: parent
    }
    Row {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        LineEdit {
            width: label1.width / 2
            height: 80
            anchors.bottom: parent.bottom
        }
        Text {
            text: "￥"
            font.pointSize: 16

        }
    }
}
