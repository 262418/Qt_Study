import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5   // 使用 Button、CheckBox 等控件必须导入

// ==================== 主窗口 ====================
Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("Qt Quick测试程序")

    // ---------- 1. 退出按钮 Button ----------
    Button {
        id: exitbutton
        text: "Exit Button"

        // 锚点布局：贴着父元素左下角
        anchors.left: parent.left
        anchors.leftMargin: 100       // 左边距 100
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 500     // 底边距 500

        // 点击事件
        onClicked: {
            Qt.quit();                // 退出整个 QML 应用程序
        }
    }

    // ---------- 2. 矩形 Rectangle ----------
    Rectangle {
        // 绝对定位 (x, y)
        x: 100
        y: 150

        width: 190
        height: 70

        color: "#00B000"              // 绿色
        opacity: 1.2                  // 注意：透明度最大值是 1.0，写 1.2 会自动被截断为 1.0
    }

    // ---------- 3. 自定义复选框 CheckBox ----------
    // ---------- 3. 复选框 CheckBox (Qt 6 原生风格) ----------
    CheckBox {
        id: checkboxcontrol
        text: qsTr("湖南省长沙市")
        checked: true
        x: 100
        y: 300

        // --- 修改文字大小和颜色 ---
        font.pixelSize: 30
        palette.windowText: checkboxcontrol.down ? "#18a81a" : "#333333"

        // --- 修改原生勾选框的大小 ---
        // 在 Qt 6 中，不能改 indicator 内部，但可以缩放整个 indicator
        indicator.width: 60
        indicator.height: 60

        // --- 改变勾选后的颜色 ---
        // Qt 6 里通常通过调色板（Palette）来控制高亮色
        // 当鼠标按下或选中时，原生控件的边框和勾会变成这个颜色
        palette.highlight: "#18a81a"
    }

    // ---------- 4. 状态与动画演示 Rectangle ----------
    Rectangle {
        id: irect
        x: 400
        y: 120
        width: 300
        height: 60

        state: "normal"               // 默认状态是 "normal"

        // states：定义不同的状态
        states: [
            State {
                name: "normal"        // 状态名
                PropertyChanges {
                    target: irect     // 修改目标是 irect
                    color: "red"      // 颜色变红
                }
            },
            State {
                name: "lightblue"
                PropertyChanges {
                    target: irect
                    color: "lightblue"
                    width: 200        // 宽度变 200
                    height: 60
                }
            }
        ]

        // transitions：状态切换时的过渡动画
        transitions: [
            Transition {
                from: "normal"
                to: "lightblue"
                PropertyAnimation {
                    properties: "color,width,height"   // 对这三个属性做动画
                    duration: 3000                     // 耗时 3 秒
                }
            }
        ]
    }

    // ---------- 5. 切换状态的按钮 ----------
    Button {
        id: changesstatess
        x: 400
        y: 190
        text: "change state"
        onClicked: irect.state = "lightblue";   // 切换到 lightblue 状态（触发动画）
    }

    // ---------- 6. 恢复状态的按钮 ----------
    Button {
        id: recoverss
        x: 570
        y: 190
        text: "recoverss state"
        onClicked: irect.state = "normal";      // 切换回 normal 状态
    }
}