import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.2   // 必须导入 Layouts 模块

Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("Layout布局管理器--测试程序")

    // ================= 1. RowLayout（水平行布局） =================
    // 子元素从左到右排列，并且可以通过 Layout 属性进行精细控制
    RowLayout {
        // （这里没有指定宽高，它会自动包裹住里面的三个矩形）

        Rectangle {
            Layout.preferredHeight: 100   // 期望高度
            Layout.preferredWidth: 100    // 期望宽度
            Layout.alignment: Qt.AlignLeft // 在行内靠左对齐（实际上在 RowLayout 里默认也是水平排列）
            color: "red"
        }

        Rectangle {
            Layout.preferredHeight: 75
            Layout.preferredWidth: 120
            Layout.alignment: Qt.AlignLeft
            color: "cyan"
        }

        Rectangle {
            Layout.preferredHeight: 50
            Layout.preferredWidth: 250
            Layout.alignment: Qt.AlignRight // 在行内靠右对齐
            color: "darkorange"
        }
    }

    // ================= 2. ColumnLayout（垂直列布局） =================
    // 子元素从上到下排列，同样支持对齐和尺寸控制
    ColumnLayout {
        x: 150   // 绝对定位，把这个列布局放到窗口的 (150, 150) 位置
        y: 150

        Rectangle {
            Layout.alignment: Qt.AlignCenter // 在列内水平居中对齐
            color: "yellow"
            Layout.preferredHeight: 120
            Layout.preferredWidth: 60
        }

        Rectangle {
            Layout.alignment: Qt.AlignRight // 在列内靠右对齐
            color: "blue"
            Layout.preferredHeight: 90
            Layout.preferredWidth: 50
        }

        Rectangle {
            Layout.alignment: Qt.AlignBottom // 底部对齐（实际上在 ColumnLayout 里，垂直方向是顺延的，这个主要是水平方向的对齐起作用）
            color: "blueviolet"
            Layout.preferredHeight: 180
            Layout.preferredWidth: 55
        }
    }
}