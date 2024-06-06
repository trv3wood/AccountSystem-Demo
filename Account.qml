import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import Qt3D.Extras 2.15
import "loginwindow.h"
import "."
Item {
    Row {
        ColumnLayout{
            id:first

            SourText { myText: "用户姓名：" }
            SourText { myText: "绑定手机号：" }
            SourText { myText: "身份证号码：" }
            SourText { myText: "卡号：" }
            spacing: 50

        }
        ColumnLayout{
            id: second

            SourText { myText: user.name }
            SourText { myText: user.phoneNum }
            SourText { myText: user.id }
            SourText { myText: user.cardNumber }
            spacing: 50

        }
        x:480
        y:220
        spacing: 25

    }
    Button{
        id:changePsswd
        objectName: changepwbutton

        property string buttonText: ""
        property string fontFamily: "Microsoft Yahei"
        flat: true
        width: 100
        height: 80
        anchors.horizontalCenter: parent.horizontalCenter


        Text {
            text: changePsswd.buttonText
            font.family: changePsswd.fontFamily
            font.pixelSize: 80
            color: "black"
            anchors.centerIn: parent
        }
        text: "修改密码"
        font.family : "Microsoft Yahei"
        x:520
        y:600

        onClicked: {
            MainWindow.callcpp_clicked();
        }
    }
}

