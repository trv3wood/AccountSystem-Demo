import QtQuick 2.15
import QtQuick.Layouts 1.15
import "."
Rectangle {
    color: "ghostwhite"
    id: depositWithdraw
    border.color: "#dcdcdc"
    border.width: 1
    radius: 10
    Row {
        anchors.fill: parent
        spacing: 30
        anchors.centerIn: parent
        CustomLabel {
            id: label1
            labelText: "存款"
            width: parent.width / 2
            height: parent.height / 1.5
        }

        CustomLabel {
            id: label2
            labelText: "取款"
            width: parent.width / 2
            height: parent.height / 1.5
        }

    }
}
