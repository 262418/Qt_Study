import QtQuick 2.0
import QtQuick.Controls 2.0

Button {
    id:mybutton
    property var backColor: "white" // 背景颜色
    property var fontPixelSize: 20
    property var fontColor: "#FFFFFF"

    text: "button"
    implicitWidth: 100
    implicitHeight: 30;
    hoverEnabled: true;

    // 设置文本
    contentItem: Label {
        id:buttonForeGround
        text: parent.text
        font.family: "微软雅黑"
        font.pixelSize: fontPixelSize
        color: fontColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight;
    }

    // 绘制亮度范围
    background: Rectangle {
        id:mybuttonback
        color: backColor
        radius: 6

        Rectangle {
            width: mybuttonback.width*0.8
            height: mybuttonback.height*0.5
            x:mybuttonback.width*0.05
            y:mybuttonback.height*005

            radius: 3
            color: Qt.lighter(mybuttonback.color,1.10)
        }
    }

    onDownChanged: {
        mybuttonback.color=down?Qt.lighter(backColor,0.9):backColor; // 设置按下的背景颜色
    }

    onHoveredChanged: {
        mybuttonback.color=hovered?Qt.lighter(backColor,1.9):backColor; // 设置徘徊的背景颜色
    }
}
