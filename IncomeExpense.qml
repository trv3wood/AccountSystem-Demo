import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    // anchors.fill: parent
    Column {
        id: incomePage
        anchors.centerIn: parent
        spacing: 30
        anchors.topMargin: 30
        // 显示用户信息
        anchors.fill: parent
        SourText { myText: "交易记录"; anchors.horizontalCenter: parent.horizontalCenter }
        Repeater {
            model: user.recentRecords()  // Assuming `user` is an instance of BasicAccount exposed to QML
            delegate: CustomLabel {
                myText: modelData
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        // RoundButton {
        //     id: saveButton
        //     text: "最近"
        //     anchors.horizontalCenter: parent.horizontalCenter
        //     // anchors.horizontalCenter: parent.horizontalCenter
        //     // anchors.top: recordText.bottom
        //     onClicked: {
        //         user.recentRecords()
        //         user.recentTransfers()
        //     }
        // }
    }

}
