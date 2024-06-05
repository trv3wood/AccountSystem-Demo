import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import Qt3D.Extras 2.15
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

            Component.onCompleted: {
                        first.columnAlignment(0, Qt.AlignHCenter)
                    }
        }
        ColumnLayout{
            id: second

            SourText { myText: +user.name }
            SourText { myText: user.phoneNum }
            SourText { myText: user.id }
            SourText { myText: user.cardNumber }
            spacing: 50

            Component.onCompleted: {
                        second.columnAlignment(0, Qt.AlignHCenter)
                    }
        }
        Layout.alignment: Qt.AlignVCenter
        spacing: 25
        anchors.centerIn: parent
    }
//    Button{
//        id:changePsswd
//        objectName: changepwbutton
//        text: "修改密码"
//        font.family : "Microsoft Yahei"
//        font:black
//        height: 10
//        width: 15
//        background: "#738e95"
////        onClicked: {
////            forgotpwd.callcpp_clicked();
////        }
//    }
}
