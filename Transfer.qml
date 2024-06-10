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
                text: "收件账户:"
                font.pointSize: 18
                color: "#2e3a45"
                Layout.alignment: Qt.AlignVCenter
                font.family: "Microsoft Yahei"
            }

            CustomComboBox {
                id: receiverBox
                model: user.recentTransfers()
                font.pointSize: 20
                onCurrentIndexChanged: {
                    receiver.enabled = currentIndex === 0;
                }
                TextField {
                    id: receiver
                    width: parent.width - 30 // 调整宽度
                    height: parent.height
                    enabled: parent.currentIndex === 0
                    text: enabled ? text : ""
                }
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
                validator: DoubleValidator { bottom: 0.0; top: 1000000000.0; decimals: 2 }
            }

            Text {
                text: "￥"
                font.pointSize: 18
                font.family: "Microsoft Yahei"
                color: "#2e3a45"
            }
        }
        RoundButton {
            Layout.alignment: Qt.AlignHCenter
            text: "确认转账"
            font.pixelSize: 35
            font.family: "Microsoft Yahei"
            radius: height / 2 - 10
            Layout.fillWidth: true
            Layout.fillHeight: true
            // 背景色
            background: Rectangle {
                color: "lightblue"
                radius: parent.radius
                anchors.fill: parent
            }
            onClicked: {
                var Receiver = receiverBox.currentIndex === 0 ? receiver.text : receiverBox.currentText
                // console.log(Receiver)
                user.transfer(Receiver, amountField.text)
            }
        }
    }
}
