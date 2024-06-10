import QtQuick 2.15


Rectangle {
    property string myText: ""
        width: incomePage.width / 1.2
        height: 80
        radius: height / 2
        border.color: "black"
        border.width: 3
        Text {
            text: myText
            font.family: "Microsoft YaHei"
            font.pointSize: 12
            anchors.centerIn: parent
        }
}
