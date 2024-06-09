import QtQuick 2.15

Rectangle {
    radius: height / 2 -10
    border.width: 5
    border.color: "#b6b6b6"
    color: "white"
    property string amount: input.text
    TextInput {
        id: input
        anchors.fill: parent
        font.pointSize: 18
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        // 设置文字居中
        color: "#333"
        // 输入数字验证
        validator: RegExpValidator {
            // 小数点后两位
            regExp: /^[0-9]+(.[0-9]{0,2})?$/
        }
        // 设置输入框最大长度
        maximumLength: 30
    }
}
