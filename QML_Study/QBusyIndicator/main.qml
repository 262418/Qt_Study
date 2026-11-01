import QtQuick
import QtQuick.Controls
import QtQuick.Shapes          // Qt 6 原生模块：提供 ConicalGradient 和 Shape

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("BusyIndicator（繁忙指示器）--测试程序")

    BusyIndicator {
        id: control
        anchors.centerIn: parent

        implicitWidth: 200
        implicitHeight: 200

        // contentItem：重写 BusyIndicator 的内部视觉表现
        contentItem: Item {
            id: content

            // 动态计算圆环的半径和粗细
            // ringRadius：取宽高中的较小值的一半（保证是正圆）
            readonly property real ringRadius: Math.min(width, height) / 2

            // ringThickness：圆环的粗细（半径的 1/4，正好对应老代码的宽/8）
            readonly property real ringThickness: ringRadius / 4

            // 核心动画：让整个 Item（包含渐变圆环和红点）一起绕中心旋转
            RotationAnimation on rotation {
                // 只有当控件可见且 running 为 true 时才旋转
                running: control.visible && control.running
                from: 0
                to: 360
                duration: 2000              // 转一圈 2 秒
                loops: Animation.Infinite   // 无限循环
            }

            // BusyIndicator 的规范：running 为 false 时隐藏自己
            opacity: control.running ? 1 : 0
            Behavior on opacity {
                NumberAnimation { duration: 250 } // 淡入淡出动画
            }

            // ================= 绘制渐变圆环 =================
            Shape {
                id: ring
                anchors.fill: parent

                // 开启抗锯齿（只对这个 Shape 生效，性能极好）
                layer.enabled: true
                layer.samples: 4

                // 核心算法：用 SVG 路径画“甜甜圈”
                // 原理：画一个大圆，再在大圆里画一个方向相反的同心小圆
                // 配合奇偶填充（OddEvenFill），中间的交集部分就会被“挖空”
                function donutPath() {
                    if (width <= 0 || height <= 0)
                        return ""
                    var rOuter = Math.min(width, height) / 2      // 外圆半径
                    var rInner = rOuter - rOuter / 4              // 内圆半径 (外圆 - 粗细)
                    var cx = width / 2                            // 圆心 X
                    var cy = height / 2                           // 圆心 Y
                    // 内部辅助函数：生成画圆的 SVG 路径
                    // sweep=1 顺时针（外圈），sweep=0 逆时针（内圈）
                    function circle(r, sweep) {
                        return "M " + cx + " " + (cy - r) // 移动到顶部
                             + " A " + r + " " + r + " 0 1 " + sweep + " " + cx + " " + (cy + r) // 画半圆到底部
                             + " A " + r + " " + r + " 0 1 " + sweep + " " + cx + " " + (cy - r) // 画半圆回顶部
                             + " Z " // 闭合路径
                    }

                    // 外圆顺时针，内圆逆时针，组合在一起
                    return circle(rOuter, 1) + circle(rInner, 0)
                }

                ShapePath {
                    // 奇偶填充规则：两条路径重叠的地方（圆环区域）才填色
                    fillRule: ShapePath.OddEvenFill

                    // 不要描边，只要填充
                    strokeWidth: -1

                    // 原生圆锥渐变
                    fillGradient: ConicalGradient {
                        centerX: ring.width / 2
                        centerY: ring.height / 2
                        angle: 0            // 0° 从 3 点钟方向开始

                        GradientStop { position: 0.0; color: "chartreuse" }
                        GradientStop { position: 1.0; color: "orange" }
                    }

                    // 把上面算好的“甜甜圈”路径塞进去
                    PathSvg { path: ring.donutPath() }
                }
            }

            // ================= 红色小圆点 =================
            // 精妙之处：圆锥渐变的 0° 和 360° 交界处在 3 点钟方向，会有一条生硬的接缝。
            // 把红点放在 3 点钟方向，正好盖住这个接缝！
            Rectangle {
                width: content.ringThickness  // 粗细和圆环一样
                height: width
                radius: width / 2             // 变成圆
                color: "red"
                antialiasing: true            // 抗锯齿

                // 定位到 3 点钟方向（右侧边缘的正中）
                x: content.width / 2 + content.ringRadius - width
                y: content.height / 2 - height / 2
            }
        }
    }
}