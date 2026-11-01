import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("Anchors（锚布局）--测试程序")


    // Text靠最上边，水平居中
    Text{
        id:mytext
        x:50
        y:50

        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.topMargin: 300;

        text:"零声教育--Qt开发课程";
        color: "blue";
        font.pixelSize: 25; //像素大小
    }

    // 矩形
    Rectangle{
        id:myrect
        x:50
        y:100
        anchors.left: mytext.left

        width: 300
        height: 100
        color: "cyan"; // 矩形填充颜色
        border.width: 10; // 矩形边框粗细程度
        border.color: "orange"; // 矩形边框颜色
        radius: 10; // 圆角

        TextInput{
            id:mynumber;
            width: 300
            height: 45;
            focus: true; // 给矩形设置焦点
            x:15;
            y:15;
        }
    }

    // 显示图像
    Image {
        x:50;
        y:300;

        anchors.horizontalCenter: mytext.horizontalCenter;
        anchors.top: myrect.bottom;
        anchors.topMargin: 20;

        width: 500;
        height: 300;

        source: "file:/d:/1.jpg";
        fillMode: Image.PreserveAspectFit; // 按照比例填充，不会变形


    }



}
