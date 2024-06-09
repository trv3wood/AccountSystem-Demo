import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import "."
Item {
    Column {
        anchors.centerIn: parent
        spacing: 50
        Label {
            Text {
                text: "存款金额"
                font.pixelSize: 35
                font.bold: true
                font.family: "Microsoft YaHei"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            width: 600
            height: 50
        }
        LineEdit {
            id: deposit
            width: 600
            height: 80
        }
        RoundButton {
            text: "存款"
            font.pixelSize: 35
            font.family: "Microsoft YaHei"
            radius: height / 2 - 10
            width: 600
            height: 80
            background: Rectangle {
                color: "lightgreen"
                radius: parent.radius
                anchors.fill: parent
            }
            onClicked: {
                if (deposit.amount === "") {
                    return
                }
                var amount = parseFloat(deposit.amount)
                // if (isNaN(amount)) {
                //     return
                // }
                user.deposit(amount);
                // 清空
                deposit.children[0].text = ""
            }
        }
        Label {
            Text {
                text: "取款金额"
                font.pixelSize: 35
                font.bold: true
                font.family: "Microsoft YaHei"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            font.pixelSize: 24
            font.bold: true
            font.family: "Microsoft YaHei"
            width: 600
            height: 50
        }

        LineEdit {
            id: withdraw
            width: 600
            height: 80
        }

        RoundButton {
            text: "取款"
            font.pixelSize: 35
            font.family: "Microsoft Yahei"
            radius: height / 2 - 10
            width: 600
            height: 80
            // 背景色
            background: Rectangle {
                color: "lightblue"
                radius: parent.radius
                anchors.fill: parent
            }
            onClicked: {
                if (withdraw.amount === "") {
                    return
                }
                var amount = parseFloat(withdraw.amount)
                // if (isNaN(amount)) {
                //     return
                // }
                user.withdraw(amount);
                // 清空
                withdraw.children[0].text = ""
            }
        }
        
        Text {
            id: balance_f
            text: "余额：" + user.balance
            font.pixelSize: 35
            font.bold: true
            font.family: "Microsoft YaHei"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        
        Text {
            id: balance
            text: "余额：" + user.balance_f
            font.pixelSize: 35
            font.bold: true
            font.family: "Microsoft YaHei"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
