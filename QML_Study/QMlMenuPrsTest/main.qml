import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true
    width: 900
    height: 550
    title: qsTr("QML高级编程--下拉菜单实现")
    menuBar: MenuBar{
        Menu {
            title:qsTr("bilibili大学课程")
            Action{
                text:qsTr("Linux内核分析课程")
                onTriggered: console.log("同志你好，你现已经点击【Linux内核分析课程】!!!")
            }
            Action{ text:qsTr("BAT大厂技术面试课程")
                onTriggered: console.log("同志你好，你现已经点击【BAT大厂技术面试课程】!!!")
            }
            Action{ text:qsTr("音视频技术高级课程")}
            Action{ text:qsTr("Qt开发高级课程")}
            Action{ text:qsTr("后台服务器架构课程")}
            Action{ text:qsTr("后继课程等研发...")}

            delegate:GreenMenuItem{}
            background: GreenMenuBarBg{}
        }
        Menu {
            title:qsTr("Qt开发课程")
            Action{ text:qsTr("C/C++开发基础专栏")}
            Action{ text:qsTr("数据结构算法专栏")}
            Action{ text:qsTr("Qt入门到精通专栏")}
            Action{ text:qsTr("MySQL数据库专栏")}
            Action{ text:qsTr("SQLite数据库专栏")}
            Action{ text:qsTr("C++设计模式专栏")}
            Action{ text:qsTr("OpenCV高级专栏")}
            Action{ text:qsTr("Qt工程师进阶专栏")}
            Action{ text:qsTr("Qt企业项目开发专栏")}

            delegate:GreenMenuItem{}
            background: GreenMenuBarBg{}
        }
        Menu {
            title:qsTr("讲师团队")
            Action{ text:qsTr("K老师")}
            Action{ text:qsTr("D老师")}
            Action{ text:qsTr("M老师")}
            Action{ text:qsTr("N老师")}
            Action{ text:qsTr("V老师")}
            Action{ text:qsTr("依老师")}
            Action{ text:qsTr("贝老师")}
            Action{ text:qsTr("秋老师")}
            Action{ text:qsTr("桃老师")}
            Action{ text:qsTr("柚老师")}
            Action{ text:qsTr("诗老师")}
            delegate:GreenMenuItem{}
            background: GreenMenuBarBg{}
        }
        delegate: GreenMenuBar{}
        background: GreenMenuBarBg{}
    }
}
