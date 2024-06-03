import QtQuick 2.15

Rectangle {
    radius: height / 2 -10
    border.width: 5
    border.color: "#b6b6b6"
    color: "white"
    TextInput {
        anchors.fill: parent
        font.pixelSize: 24
        horizontalAlignment: Text.AlignHCenter
        // 设置文字居中
        verticalAlignment: Text.AlignVCenter
        // 设置文字颜色
        color: "#333"
        // 输入数字验证
        validator: RegExpValidator { regExp: /^[0-9]*$/ }
        // 设置输入框最大长度
        maximumLength: 20
    }
}
