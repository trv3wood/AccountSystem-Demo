import QtQuick 2.15
import QtQuick.Layouts 1.15
import "."
Item {
    Row {
        anchors.fill: parent
        spacing: 30
        // anchors.centerIn: parent
        CustomLabel {
            id: label1
            labelText: "存款"
            width: parent.width / 2
            height: parent.height / 1.5
            anchors.verticalCenter: parent.verticalCenter
        }

        CustomLabel {
            id: label2
            labelText: "取款"
            width: parent.width / 2
            height: parent.height / 1.5
            anchors.verticalCenter: parent.verticalCenter
        }

    }
}
