import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    visible: true
    width: 800
    height: 400
    title: qsTr("QML动画基础知识--测试程序")

/*
    // ================= 动画基础1：PropertyAnimation 属性动画 =================
    Rectangle {
        id: myrect1
        x: 30
        y: 40
        width: 30
        height: 60
        color: "cyan" // 青色
    }

    Rectangle {
        id: myrect2
        x: 30
        y: 40 + myrect1.height + 10
        width: 30
        height: 60
        color: "darkorange" // 深橘色
    }

    // 属性动画：控制组件的属性（x、width等）平滑过渡
    PropertyAnimation {
        id: myanimation
        targets: [myrect1, myrect2] // 目标：同时控制这两个矩形
        properties: "width,x"       // 变化的属性
        from: 30                    // 起始值
        to: 800                     // 结束值
        duration: 30000             // 持续时间 30 秒
    }

    // 鼠标区域：点击窗口任意位置开始动画
    MouseArea {
        anchors.fill: parent
        onClicked: myanimation.running = true
    }
*/

/*
    // ================= 动画基础2：Timer 定时器 =================
    Rectangle {
        id: myrect3
        anchors.fill: parent
        color: "white"

        Rectangle {
            id: myrect4
            x: 0
            y: 0
            width: 50
            height: 600
            color: "orange"
        }
    }

    // 定时器：每隔一段时间自动触发一次
    Timer {
        id: mytimer
        interval: 1000       // 间隔时间：1000 毫秒（1秒）
        repeat: true         // 是否重复触发
        running: true        // 是否自动启动
        triggeredOnStart: false // 启动时是否立即触发第一次

        // 每次时间到了执行这里的代码
        onTriggered: {
            // 如果橙色方块还没碰到右边边缘
            if (myrect4.x + myrect4.width < myrect3.width) {
                myrect4.x += 60 // 向右移动 60 像素
            } else {
                myrect4.x = 0   // 碰到边缘，回到起点
            }
        }
    }
*/

/*
    // ================= 动画基础3：倒计时器 =================
    Rectangle {
        id: myrect5
        width: 200
        height: 200
        color: "orange"
        anchors.centerIn: parent

        // QtObject 用于存储纯数据（不可见）
        QtObject {
            id: myattr
            property int counters; // 倒计时数值
            // Component.onCompleted 会在组件加载完成后自动执行
            Component.onCompleted: {
                counters = 10; // 初始化倒计时为 10
            }
        }
    }

    // 显示倒计时的文字
    Text {
        id: mycountersshow
        anchors.centerIn: parent
        color: "white"
        font.pixelSize: 150
    }

    // 倒计时定时器
    Timer {
        id: mycountersdown
        interval: 1000
        repeat: true
        triggeredOnStart: true // 启动时立即触发一次

        onTriggered: {
            mycountersshow.text = myattr.counters // 把当前数字显示到界面上
            myattr.counters = myattr.counters - 1; // 数字减 1

            // 如果数字小于 0，停止定时器
            if (myattr.counters < 0) {
                mycountersdown.stop();
            }
        }
    }

    // 按钮：点击开始倒计时
    Button {
        id: mybuttonstart
        width: 200
        text: "开始倒计时"
        anchors.top: myrect5.bottom
        anchors.horizontalCenter: myrect5.horizontalCenter

        onClicked: {
            myattr.counters = 10 // 重置倒计时
            mycountersdown.start(); // 启动定时器
        }
    }
*/

// /*
    // ================= 动画基础4：Canvas 水波纹进度球 =================
    property int rangevalue: 65; // 目标进度
    property int nowrange: 0;    // 当前进度
    property int mw: 300; // 画布宽
    property int mh: 300; // 画布高
    property int linewidth: 3;
    property double r: mh / 2;          // 圆心坐标
    property double cr: r - 20 * linewidth; // 圆半径
    property int sx: 0;
    property int sy: mh / 2;
    property int axislength: mw;     // 画轴长度
    property double wavewidth: 0.01; // 波浪宽度（越小越宽）
    property double waveheight: 5;   // 波浪高度（越大越高）
    property double speed: 0.08;     // 波浪速度（越大越快）
    property double xoffset: 0;      // 波浪 X 偏移量

    // Canvas 画布：用于自定义绘图
    Canvas {
        id: mycanvas
        width: mw
        height: mh
        anchors.centerIn: parent

        // 核心绘图逻辑
        onPaint: {
            var mytx = getContext("2d");

            // 清空画布
            mytx.clearRect(0, 0, mw, mh);

            // 1. 画外圈红圆
            mytx.beginPath();
            mytx.strokeStyle = 'red';
            mytx.arc(r, r, cr + 2, 0, 2 * Math.PI);
            mytx.stroke();

            // 2. 画内圈，并裁剪（让后续画的波浪只能显示在圆里）
            mytx.beginPath();
            mytx.arc(r, r, cr, 0, 2 * Math.PI);
            mytx.clip();

            // 3. 画正弦波浪
            mytx.save();
            var points = [];
            mytx.beginPath();

            // 循环计算波形的每一个点
            for (var x = sx; x < sx + axislength; x += 20 / axislength) {
                var y = -Math.sin((sx + x) * wavewidth + xoffset); // 正弦函数
                var dy = mh * (1 - nowrange / 100);                // 高度由当前进度决定
                points.push([x, dy + y * waveheight]);
                mytx.lineTo(x, dy + y * waveheight);
            }

            // 封闭图形并填充蓝色
            mytx.lineTo(axislength, mh);
            mytx.lineTo(sx, mh);
            mytx.lineTo(points[0][0], points[0][1]);
            mytx.fillStyle = 'blue';
            mytx.fill();
            mytx.restore();

            // 4. 画中间的百分比文字
            mytx.save();
            var size = 0.4 * cr;
            mytx.font = size + 'px Arial';
            mytx.textAlign = 'center';
            mytx.fillStyle = "rgba(0, 255, 0, 0.8)";
            mytx.fillText(nowrange + '%', r, r + size / 2);
            mytx.restore();

            // 5. 动态更新进度和波浪偏移量（用于下一次重绘）
            if (nowrange <= rangevalue) {
                nowrange = nowrange + 1;
            }

            if (nowrange > rangevalue) {
                nowrange = nowrange - 1;
            }
            xoffset = xoffset + speed;
        }

        // 定时器：不断请求重绘，形成动画
        Timer {
            id: mytimer
            running: false;
            repeat: true;
            interval: 100;
            onTriggered: {
                parent.requestPaint(); // 请求重绘 Canvas
            }
        }
    }

    // 启动/停止按钮
    Button {
        id: mybutton
        width: 80;
        height: 30;
        anchors.horizontalCenter: parent.horizontalCenter

        text: "开始运行"
        onClicked: {
            if (mytimer.running == false) {
                mytimer.start();
                mybutton.text = "停止运行";
            } else {
                mytimer.stop();
                mybutton.text = "开始运行";
            }
        }
    }
// */
}