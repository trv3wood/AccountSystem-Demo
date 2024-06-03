import QtQuick 2.15

// CustomButton.qml
import QtQuick.Controls 2.15

Button {
    id: customButton
    property string buttonText: ""
    property string fontFamily: "Microsoft Yahei"
    flat: true
    width: leftsidebar.width
    height: 80
    anchors.horizontalCenter: parent.horizontalCenter

    Text {
        text: customButton.buttonText
        font.family: customButton.fontFamily
        font.pointSize: 20
        color: "white"
        anchors.centerIn: parent
    }
}
