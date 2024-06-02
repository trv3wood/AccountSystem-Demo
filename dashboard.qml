import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "."

ApplicationWindow {
    id: root
    title: "Dashboard"
    // 全屏
    width: 1800
    height: 1200
    visible: true
    color: "ghostwhite"

    RowLayout {
        anchors.fill: parent

        // Left Sidebar
        Rectangle {
            id: leftsidebar
            width: root.width * 0.2
            Layout.fillHeight: true
            color: "dodgerblue"

            Column {
                spacing: 30
                y: parent.y + 30
                Layout.fillWidth: true

                CustomButton {
                    buttonText: "存取"
                }

                CustomButton {
                    buttonText: "转账"
                }

                CustomButton {
                    buttonText: "收支"
                }

                CustomButton {
                    buttonText: "账户"
                }
            }
            Rectangle {
                width: 100
                height: 30
                visible: true
                color: "dodgerblue"
                Button {
                    flat: true
                    width: leftsidebar.width
                    anchors.fill: parent
                }
                Text {
                    id: t
                    text: qsTr("登出")
                    color: "white"
                    font.family: "Microsoft Yahei"
                    anchors.centerIn: parent
                }
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
            }
        }

        // Main content area
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "ghostwhite"
            id: mainArea

            Column {

                spacing: 30
                anchors.centerIn: parent

                Text {
                    text: "账户名: 用户123\n"
                    font.pointSize: 12
                }

                Text {
                    text: "邮箱"
                    font.pointSize: 12
                }
                Text {
                    text: "地址"
                    font.pointSize: 12
                }
            }
        }
    }
}
