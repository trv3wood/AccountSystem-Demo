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
                Layout.fillWidth: true

                CustomButton {
                    buttonText: "欢迎 " + user.phoneNum
                    background: Rectangle {
                        color: "#738e95"
                    }
                }

                CustomButton {
                    buttonText: "存取"
                    onClicked: contentLoader.source = listModel.get(0).source
                }

                CustomButton {
                    buttonText: "转账"
                    onClicked: contentLoader.source = listModel.get(1).source
                }

                CustomButton {
                    buttonText: "收支"
                    onClicked: contentLoader.source = listModel.get(2).source
                }

                CustomButton {
                    buttonText: "账户"
                    onClicked: contentLoader.source = listModel.get(3).source
                }
            }
            CustomButton {
                buttonText: "登出"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                onClicked: {
                    root.close()
                }
            }
        }

        // Main content area
        ListModel {
            id: listModel
            ListElement { name: "存取"; source: "qrc:/qml/Deposit.qml" }
            ListElement { name: "转账"; source: "qrc:/qml/Transfer.qml" }
            ListElement { name: "收支"; source: "qrc:/qml/IncomeExpense.qml" }
            ListElement { name: "账户"; source: "qrc:/qml/Account.qml" }
        }

        Loader {
            id: contentLoader
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
