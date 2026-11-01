import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Image元素--测试程序")

    /*
    Image {
        id:image01
        anchors.centerIn: parent
        source: "/new/prefix1/images/qq.jpg" // 加载资源文件路径
    }
*/
    Column{
        anchors.centerIn: parent
        spacing: 8 // 间隔

        Image {
            width: 60
            height: 60
            source: "/new/prefix1/images/qq.jpg" // 加载资源文件路径
            fillMode: Image.Pad // 填充模式不会变形
        }

        Image {
            width: 20
            height: 40
            source: "/new/prefix1/images/qq.jpg" // 加载资源文件路径
            fillMode: Image.PreserveAspectFit // 图像填充模式--按照比例缩放填充 不裁剪
        }

        Image {
            width: 100
            height: 100
            source: "/new/prefix1/images/qq.jpg" // 加载资源文件路径
            fillMode: Image.TileVertically // 图像填充模式--水平填充 垂直复制
        }

        Image {
            width: 200
            height: 200
            source: "/new/prefix1/images/qq.jpg" // 加载资源文件路径
            fillMode: Image.TileHorizontally // 图像填充模式--垂直填充 水平复制
        }

    }





}
