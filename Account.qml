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
            id:roww
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
            width: roww.width / 3
            height: 80
            anchors.horizontalCenter: parent.horizontalCenter
    //        anchors.horizontalCenter: parent.horizontalCenter
            background: Rectangle{
                anchors.fill: changebutton
                color:
                    if(changebutton.pressed)return "#999999"
                    else return "lightblue"
                radius: height / 2 - 10
            }
            Text {
                text: "修改密码"

                font.family : "Microsoft Yahei"
                font.pixelSize: 30
                color: "black"
                anchors.centerIn: parent
            }

//             x:20
//             y:800

            onClicked: {
                myobj.cppSlot();
            }
        }
    }

}

