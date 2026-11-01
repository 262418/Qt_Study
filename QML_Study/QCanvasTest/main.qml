import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 900
    height: 300
    title: qsTr("Qt Quick Canvas画布--测试程序")

    // 使用 Row 将 5 个进度条横向排列
    Row {
        anchors.centerIn: parent
        spacing: 20

        // 实例化自定义的组件 CProgresBars，并传入不同的属性
        CProgresBars {
            id: progress1
            linewidth: 10
            value: 0.13              // 13% 进度
            size: 150
            secondarycolor: "red"    // 背景环颜色
            primarycolor: "blue"     // 进度条颜色

            // 在圆心添加文字
            Text {
                // parseInt 将 0.13*100 转为整数 13
                text: parseInt(progress1.value * 100) + "%"
                anchors.centerIn: parent
                font.pointSize: 20
                color: progress1.primarycolor
            }
        }

        CProgresBars {
            id: progress2
            linewidth: 10
            value: 0.25              // 25%
            size: 150
            secondarycolor: "red"
            primarycolor: "green"

            Text {
                text: parseInt(progress2.value * 100) + "%"
                anchors.centerIn: parent
                font.pointSize: 20
                color: progress2.primarycolor
            }
        }

        CProgresBars {
            id: progress3
            linewidth: 10
            value: 0.55              // 55%
            size: 150
            secondarycolor: "red"
            primarycolor: "aqua"

            Text {
                text: parseInt(progress3.value * 100) + "%"
                anchors.centerIn: parent
                font.pointSize: 20
                color: progress3.primarycolor
            }
        }

        CProgresBars {
            id: progress4
            linewidth: 10
            value: 0.75              // 75%
            size: 150
            secondarycolor: "red"
            primarycolor: "darkblue"

            Text {
                text: parseInt(progress4.value * 100) + "%"
                anchors.centerIn: parent
                font.pointSize: 20
                color: progress4.primarycolor
            }
        }

        CProgresBars {
            id: progress5
            linewidth: 10
            value: 0.95              // 95%
            size: 150
            secondarycolor: "red"
            primarycolor: "darkorange"

            Text {
                text: parseInt(progress5.value * 100) + "%"
                anchors.centerIn: parent
                font.pointSize: 20
                color: progress5.primarycolor
            }
        }
    }
}