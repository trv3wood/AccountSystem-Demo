import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: transferPage

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 100

        Text {
            text: "转账"
            font.family: "Microsoft Yahei"
            font.pointSize: 24
            color: "#2e3a45"
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            // Layout.fillWidth: true
            spacing: 10

            Text {
                text: "发件账户:"
                font.pointSize: 18
                font.family: "Microsoft Yahei"
                color: "#2e3a45"
                Layout.alignment: Qt.AlignVCenter
                height: transferPage / 3
            }

            CustomComboBox {
                model: ["", "账户1", "账户2", "账户3"]
            }
        }

        RowLayout {
            // Layout.fillWidth: true
            spacing: 10

            Text {
                text: "收件账户:"
                font.pointSize: 18
                color: "#2e3a45"
                Layout.alignment: Qt.AlignVCenter
                font.family: "Microsoft Yahei"
            }

            CustomComboBox {
                model: ["", "账户1", "账户2", "账户3"]
            }
        }

        Row {
            // Layout.fillWidth: true
            spacing: 10

            Text {
                text: "金额:  "
                font.pointSize: 18
                font.family: "Microsoft Yahei"
                color: "#2e3a45"
            }

            TextField {
                id: amountField
                placeholderText: "请输入转账金额"
                font.family: "Microsoft Yahei"
                font.pointSize: 18
                width: transferPage.width / 3
            }

            Text {
                text: "￥"
                font.pointSize: 18
                font.family: "Microsoft Yahei"
                color: "#2e3a45"
            }
        }

        Button {
            text: "提交"
            font.family: "Microsoft Yahei"
            font.pointSize: 18
            width: 150
            height: 50
            background: Rectangle {
                color: "#738e95"
                radius: 10
            }
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                // 提交转账操作
            }
        }
    }
}
