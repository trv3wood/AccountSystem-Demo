import QtQuick 2.15
//用于定义一个普遍的文字模板

Text{
    property string myText: ""  //自定义一个属性名,string类，信息是""里面的
    text: myText                //显示的文字就是myText后面的信息
    font.family: "Microsoft Yahei"
    font.pixelSize: 35
    color: "#738e95"
}
