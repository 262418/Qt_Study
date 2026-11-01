import QtQuick 2.5
import QtQuick.Controls 2.5

MenuItem {
    id:menuItem
    implicitWidth: 30
    implicitHeight: 40

    // 字体设置
    font: Qt.font({
                      family:"微软雅黑",
                      pointSize:10,
                      weight:Font.Bold
                  })

    // 字体颜色
    contentItem: Text{
        text: menuItem.text
        font:menuItem.font
        opacity: enabled?1.0:0.3
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle{
        implicitHeight: 40
        implicitWidth: 30
        opacity: enabled?1.0:0.3
        color: menuItem.highlighted?"yellowgreen":"transparent"

        Rectangle{
            color: "white"
            height: 1
            width: parent.width
            anchors.top: parent.top
            opacity: 0.5
        }
    }
}
