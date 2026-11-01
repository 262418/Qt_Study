import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("Rectangle元素--测试程序")

    // ================= 第一组：黄色背景 + 绿色小方块 =================
    // 注意：这个黄色矩形没有写 x 和 y，所以默认位置是 (0, 0)
    Rectangle {
        width: 640
        height: 480
        color: "yellow"

        // 嵌套在黄色矩形内部的绿色小矩形
        Rectangle {
            // 重点：这里的 x:30, y:30 是相对于“父元素（黄色矩形）”的左上角而言的
            x: 30
            y: 30
            width: 60
            height: 50
            color: "lightgreen"
        }
    }

    // ================= 第二组：红色矩形 + 蓝色小方块 =================
    Rectangle {
        // 这个 x, y 是相对于最外层的 Window 窗口而言的
        x: 30
        y: 100
        width: 400
        height: 150
        color: "red"

        // 嵌套在红色矩形内部的蓝色小矩形
        Rectangle {
            // 重点：这里的 x:100, y:40 同样是相对于“父元素（红色矩形）”的左上角
            // 所以它在整个窗口里的实际绝对坐标是：
            // 绝对X = 30 (父) + 100 (自己) = 130
            // 绝对Y = 100 (父) + 40 (自己) = 140
            x: 100
            y: 40
            width: 200
            height: 60
            color: "deepskyblue"
        }
    }
}