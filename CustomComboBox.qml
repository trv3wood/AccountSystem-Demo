import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
ComboBox {
    id: recipientAccountComboBox
    // property string input: textField.text
    // font.pointSize: 18
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.alignment: Qt.AlignVCenter
    height: 60

    // TextField {
    //     id: textField
    //     width: parent.width - 30 // 调整宽度
    //     height: parent.height
    //     enabled: recipientAccountComboBox.currentIndex === 0
    //     text: enabled ? text : ""
    // }
}
