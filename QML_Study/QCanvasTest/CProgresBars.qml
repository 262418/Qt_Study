import QtQuick 2.9

// 自定义组件，继承自最基本的 Item
Item {
    id: myroot

    // 暴露给外部的自定义属性
    property int size: 150           // 整体大小（宽高一致）
    property int linewidth: 5        // 圆环的线条粗细
    property real value: 0           // 进度值（0.0 到 1.0）
    property color primarycolor: "blue"    // 进度条的颜色
    property color secondarycolor: "red"   // 底部背景环的颜色
    property int animationduration: 1000   // 动画持续时间（毫秒）

    width: size
    height: size

    // 当外部的 value 发生改变时触发
    onValueChanged: {
        // 将 0.0~1.0 的进度值转换为 0~360 的角度，交给 Canvas 去画
        mycanvas.degree = value * 360;
        // （原代码这里有一个多余的 can，我已经帮你删掉了）
    }

    // 核心绘图组件
    Canvas {
        id: mycanvas
        property real degree: 0 // 当前绘制的角度
        anchors.fill: parent
        antialiasing: true      // 开启抗锯齿，让圆环边缘平滑

        // 当角度发生变化时，请求重新绘制
        onDegreeChanged: {
            requestPaint();
        }

        // 核心绘图逻辑
        onPaint: {
            var ctx = getContext("2d"); // 获取 2D 绘图上下文
            var x = myroot.width / 2;   // 圆心 X 坐标
            var y = myroot.height / 2;  // 圆心 Y 坐标
            var radius = myroot.size / 2 - myroot.linewidth; // 圆的半径（减去线宽防止超出边界）

            // 计算起始角度和结束角度（把角度转为弧度）
            // 270度在 Canvas 里是 12点钟方向（正上方）
            var startangle = (Math.PI / 180) * 270;
            var fullAngle = (Math.PI / 180) * (270 + 360); // 完整的 360 度圆
            var progressAngle = (Math.PI / 180) * (270 + degree); // 当前进度对应的角度

            ctx.reset();

            // --- 1. 画底部的背景圆环（红色） ---
            ctx.lineCap = 'round'; // 线条两端圆润
            ctx.lineWidth = myroot.linewidth;
            ctx.beginPath();
            ctx.arc(x, y, radius, startangle, fullAngle); // 画完整的圆弧
            ctx.strokeStyle = myroot.secondarycolor;      // 红色
            ctx.stroke();

            // --- 2. 画顶部的进度圆环（蓝色） ---
            ctx.beginPath();
            ctx.arc(x, y, radius, startangle, progressAngle); // 画部分圆弧
            ctx.strokeStyle = myroot.primarycolor;            // 进度色
            ctx.stroke();
        }

        // 角度变化时的平滑动画
        Behavior on degree {
            NumberAnimation {
                duration: myroot.animationduration
            }
        }
    }
}