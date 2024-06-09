import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
       width: 400
       height: 300


    // 显示用户信息
    Text {
        text: "Hello " + user.name + "!\n"
              +" Your account number is " + user.cardNumber + ".\n"
              +" Your current balance is $" + user.balance_f + ".\n"
        anchors.centerIn: parent
    }

       // 读取用户信息文件的函数
       function datafile() {
           // 实现文件读取逻辑
       }

       // 用于显示收支记录的文本框
       Text {
           id: recordText
           anchors.centerIn: parent
           width: parent.width * 0.8
           wrapMode: Text.WordWrap
       }

       // 创建一个下拉菜单供用户选择操作
       CustomComboBox {
           id: operationComboBox
           anchors.horizontalCenter: parent.horizontalCenter
           anchors.bottom: recordText.top
           width: parent.width * 0.6
           model: ["存钱", "取钱", "转账", "所有"]
           onActivated: {
               // 用户选择不同操作时执行不同的逻辑
               switch (operationComboBox.currentIndex) {
                   case 0: // 存钱
                       recordText.text = "执行存钱操作的逻辑";
                       break;
                   case 1: // 取钱
                       recordText.text = "执行取钱操作的逻辑";
                       break;
                   case 2: // 转账
                       recordText.text = "执行转账操作的逻辑";
                       break;
                   case 3: // 查看所有记录
                       recordText.text = "执行查看所有记录操作的逻辑";
                       break;
                   default:
                       break;
               }
           }
       }

       // 当界面可见时执行初始化逻辑
       Component.onCompleted: {
           // 读取用户信息文件，你需要根据自己的文件路径和格式来实现这部分逻辑
           datafile();
       }
}
