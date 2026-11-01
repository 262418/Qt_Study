import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    visible: true
    width: 600
    height: 400
    title: qsTr("MouseArea事件--测试程序")

    Rectangle {
        id: mouseareatest
        anchors.centerIn: parent // 将红色矩形定位到窗口正中心
        width: 450
        height: 200
        color: "red"

        // MouseArea：鼠标区域。它专门用来捕获鼠标的点击、拖动、悬停等事件
        MouseArea {
            // 核心：让鼠标区域填满它的父控件（红色矩形）
            // 如果不写这句，鼠标区域默认大小是 0x0，你点破了天也没反应
            anchors.fill: parent

            // 设置接受的鼠标按键：Qt.AllButtons 表示左键、右键、中键都接收
            // 如果只写 Qt.LeftButton，那点右键就没反应了
            acceptedButtons: Qt.AllButtons

            // 开启悬停（Hover）：只有开启了这个，鼠标进入(onEntered)、离开(onExited)、
            // 移动(onPositionChanged) 事件才会被触发
            hoverEnabled: true

            // 鼠标移动事件
            onPositionChanged: {
                // mouseX 和 mouseY 是鼠标相对于当前 MouseArea 左上角的坐标
                console.log("监控区域提示：你当前鼠标移动坐标为：(" + mouseX + "," + mouseY + ")");
            }

            // 鼠标点击事件
            onClicked: {
                // mouse.button 用来判断是哪个键按下了
                if (mouse.button === Qt.LeftButton) {
                    console.log("监控区域提示：你已经按下鼠标左键!");
                }
                else if (mouse.button === Qt.RightButton) {
                    console.log("监控区域提示：你已经按下鼠标右键!");
                }
                else if (mouse.button === Qt.MidButton) {
                    console.log("监控区域提示：你已经按下鼠标中间键!");
                }
            }

            // （可选）双击事件
            // onDoubleClicked: {
            //     console.log("你双击了鼠标！");
            // }
        }
    }
}