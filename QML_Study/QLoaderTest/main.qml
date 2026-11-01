import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 400
    height: 200
    title: qsTr("QML Loader对象动态操作--测试程序")

    function onLoad(){
        loader1.source="qrc:/QloaderTest/DynamicButton.qml"
        loader2.source="qrc:/QloaderTest/DynamicButton.qml"
    }

    function onRemove(){
        loader1.source=""
        loader2.source=""
    }

    // 打印输出触发消息
    function onConfirmButtonClicked(){
        console.log("同志你好，现在你已经点击【Confirm】按钮");
    }

    function onCancelButtonClicked(){
        console.log("同志你好，现在你已经点击【Cancel】按钮");
    }

    Row {
        id:row
        spacing: 20
        padding: 20

        Button{
            id:load
            font.pixelSize: 18
            text: "加载按钮"
            onClicked: onLoad();
        }

        Button{
            id:remove
            font.pixelSize: 18
            text: "移除按钮"
            onClicked: onRemove();
        }
    }

    Column{
        anchors.top: row.bottom

        spacing: 20
        padding: 20

        Loader{
            id:loader1
            onLoaded: {
                item.text="Confirm"
                item.backColor="red"
                item.clicked.connect(onConfirmButtonClicked);
            }
        }
        Loader{
            id:loader2
            onLoaded: {
                item.text="Cancel"
                item.backColor="blue"
                item.clicked.connect(onCancelButtonClicked);
            }
        }
    }
}
