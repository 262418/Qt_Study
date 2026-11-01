import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5  // 控件模块（Button 在这里）

Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("Button元素--测试程序")
    // 定义变量统计单击次数。
    // property 用于在 QML 中声明自定义属性
    property int count: 1

    // ---------- 第一个按钮：测试点击次数 ----------
    Button {
        id: mybutton1
        x: 200
        y: 150
        width: 120
        height: 40
        text: "测试点击按钮次数"

        // 信号槽连接：当按钮被单击时触发 onClicked 信号
        onClicked: {
            // console.log 会在 Qt Creator 下方的“应用程序输出”窗口打印信息
            // count++ 是后缀递增，会先使用当前 count 的值，然后再加 1
            console.log("你好，mybutton1按钮已经被你单击:" + count++)
        }
    }
    // ---------- 第二个按钮：带图标的按钮 ----------
    Button {
        id: mybutton2
        x: 400
        y: 150
        width: 120
        height: 40

        // 添加图标
        // 注意：路径必须和你的 .qrc 资源文件里配置的完全一致
        icon.source: "qrc:/new/prefix1/images/login01.bmp"

        // 设置图标颜色为透明（针对位图格式，通常不需要设置颜色，这里保持原样即可）
        icon.color: "transparent"

        text: "登录系统"
    }
}