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
            width: 400
            Layout.fillHeight: true
            color: "#738e95"

            Column {
                spacing: 30
                y: parent.y + 30
                Layout.fillWidth: truedd

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
            CustomButton {
                buttonText: "登出"
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

            Row {
                anchors.fill: parent
                spacing: 30
                anchors.centerIn: parent
                CustomLabel {
                    id: label1
                    labelText: "存款"
                    width: mainArea.width / 2
                    height: mainArea.height / 1.5
                }

                CustomLabel {
                    id: label2
                    labelText: "取款"
                    width: mainArea.width / 2
                    height: mainArea.height / 1.5
                }

            }
        }
    }
}
