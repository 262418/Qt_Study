import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML Keys事件--测试程序")

    // 创建一个红色的矩形作为接收键盘事件的“区域”
    Rectangle {
        id: keysrecttest
        //把当前控件的中心点（center），对准父控件的中心点（centerIn parent）
        anchors.centerIn: parent

        width: 450
        height: 200
        color: "red"
        radius: 10

        // 核心前提：必须要给它设置焦点，否则键盘按烂了它也不知道
        focus: true

        // 1. 拦截所有的按键按下事件
        Keys.onPressed: {
            console.log("key:" + event.key)                 // 虚拟键码（比如 A 键是 65，回车是 16777220）
            console.log("scancode:" + event.nativeScanCode) // 系统底层的硬件扫描码
            console.log("text:" + event.text)               // 按下的字符（比如 "a"、"1"）

            // 如果你在这里写了 event.accepted = true，那么按键就不会向下传递了
        }

        // 2. 专门拦截 Tab 键按下事件
        // 注意：Keys 对象有很多这种 onXxxPressed 的快捷信号（如 onEnterPressed, onEscapePressed）
        Keys.onTabPressed: {
            console.log("监控区域提示：你已经按下Tab键!")
        }

        // 3. 专门拦截 空格键 按下事件
        Keys.onSpacePressed: {
            console.log("监控区域提示：你已经按下空格键!")
        }
    }
}