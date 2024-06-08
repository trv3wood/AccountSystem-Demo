import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
        id: submitbtn
        property bool normalColorStaus: true
        property color defaultColor: "#738e95"
        property color clickedColor: "steelblue"

        Text {
            anchors.centerIn: parent
            text: "提交"
            color: "White"
            font.family: "Microsoft Yahei"
            font.pointSize: 18
        }
        flat: true


        Timer {
            id: colorTimer
            interval: 100// 200 milliseconds
            repeat: false
            onTriggered: { parent.normalColorStaus = true; }
        }

        background: Rectangle {
            id: backg
            color: parent.normalColorStaus ? parent.defaultColor : parent.clickedColor
            radius: 20
            width: 200
            height: 80
            anchors.centerIn: parent
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    submitbtn.normalColorStaus = false;
                    colorTimer.start();
                }
        }
        }
    }
