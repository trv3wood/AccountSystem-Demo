import QtQuick 2.15
import QtQuick.Layouts 1.15
 import QtQuick.Controls 2.15
import Sourchange 1.0
import "."
Item {
    Sourchange{
        id:myobj
    }
    Column {
        anchors.centerIn: parent
        spacing: 30
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
        }

        Button{
            id:changebutton
            flat: true
            width: 200
            height: 80
            anchors.horizontalCenter: parent.horizontalCenter
    //        anchors.horizontalCenter: parent.horizontalCenter
            background: Rectangle{
                anchors.fill: changebutton
                color:
                    if(changebutton.pressed)return "#999999"
                    else return "#738e95"
                radius: 10
            }
            Text {
                text: "修改密码"

                font.family : "Microsoft Yahei"
                font.pixelSize: 35
                color: "black"
                anchors.centerIn: parent
            }

            // x:480
            // y:650

            onClicked: {
                myobj.cppSlot();
            }
        }
    }

}

