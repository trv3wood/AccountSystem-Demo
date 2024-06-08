import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import Qt3D.Extras 2.15
// import MyCppClassModule 1.0
import "."
Item {
    // MainWindow {
    //         // id: myCppClassInstance // 创建 MainWindow 类的实例
    //     }
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

        flat: true
        width: 100
        height: 80
        anchors.horizontalCenter: parent.horizontalCenter


        Text {
            text: "修改密码"

            font.family : "Microsoft Yahei"
            font.pixelSize: 35
            color: "black"
            //anchors.centerIn: parent
        }

        x:520
        y:600

        onClicked: {
            // myCppClassInstance.create();
        }
    }
}

