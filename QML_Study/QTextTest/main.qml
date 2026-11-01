import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Text元素--测试程序")

    // 外层容器：一个带红色边框的矩形
    Rectangle {
        x: 40
        y: 40
        width: 260
        height: 80
        color: "chartreuse"    // 背景色：黄绿色
        border.color: "red"    // 边框颜色：红色
        border.width: 2        // 边框宽度：2像素

        // 内层元素：显示文字
        Text {
            // 注意：这里的 x 和 y 是相对于父元素（外层矩形）而言的
            x: 30
            y: 23
            text: "bilibili大学"

            // --- 字体属性设置 ---
            font.family: "隶书"      // 字体名称（如果系统没这个字体，会显示默认字体）
            font.pixelSize: 32       // 字体大小（像素单位）
            font.bold: true          // 是否加粗

            // （可选）文字颜色，默认是黑色
            // color: "blue"
        }
    }
}