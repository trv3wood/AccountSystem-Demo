import QtQuick 2.15

// CustomButton.qml
import QtQuick.Controls 2.15

RoundButton {
    id: customButton
    property string buttonText: ""
    property string fontFamily: "Microsoft Yahei"
    flat: true
    width: leftsidebar.width
    height: 50
    anchors.horizontalCenter: leftsidebar.horizontalCenter

    Text {
        text: customButton.buttonText
        font.family: customButton.fontFamily
        font.pointSize: 16
        color: "white"
        anchors.centerIn: parent
    }
}
