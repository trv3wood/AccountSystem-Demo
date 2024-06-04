import QtQuick 2.15
Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "ghostwhite"
    id: depositWithdraw

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
