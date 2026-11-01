import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.1

Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("常见布局RowColumnGridFlow--测试程序")


    // ================= 1. Row（水平行布局） =================
    // 所有的子元素按从左到右的顺序水平排列
    // /*
    Rectangle{
        id:myrowrect1
        x:30; y:20; width: 500; height: 100
        border.width: 4; border.color: "red"

        Row{
            anchors.centerIn: parent
            spacing: 20 // 子元素之间的水平间距
            Rectangle{color:"green";width: 40;height: 40 }
            Rectangle{color:"red";width: 40;height: 40 }
            // ... (排成一行)
        }
    }

    // ================= 2. Column（垂直列布局） =================
    // 所有的子元素按从上到下的顺序垂直排列
    Rectangle{
        id:mycolumnrect2
        x:30; y:150; width: 500; height: 350
        border.width: 4; border.color: "red"

        Column{
            anchors.centerIn: parent
            spacing: 10 // 子元素之间的垂直间距
            Rectangle{color:"green";width: 40;height: 40 }
            Rectangle{color:"red";width: 40;height: 40 }
            // ... (排成一列)
        }
    }
    // */

    /*
    // ================= 3. Grid（网格布局） =================
    // 自动将子元素排成矩阵（表格），配合 columns 或 rows 属性使用
    Rectangle{
        id:myrowrect4
        x:30; y:50; width: 400; height: 400
        border.width: 4; border.color: "red"

        Grid{
            anchors.centerIn: parent
            spacing: 20
            columns: 5 // ★ 核心：强制每行放 5 个元素，放满后自动换行
            Rectangle{color:"green";width: 40;height: 40 }
            Rectangle{color:"red";width: 40;height: 40 }
            Rectangle{color:"red";width: 40;height: 40 }
            Rectangle{color:"red";width: 40;height: 40 }
            Rectangle{color:"red";width: 40;height: 40 }
            // ... (按 5 列排成网格)
        }
    }
    */

    // ================= 4. Flow（流式布局） =================
    // 像水流一样，从左往右排，排满当前宽度后自动换行，不需要强制指定列数
    /*
    Flow{
        // 填满整个窗口
        anchors.fill: parent
        anchors.margins: 5 // 距离窗口四周留 5 像素的白边
        spacing: 20        // 元素之间的间距（横竖都是 20）

        // 这里的子元素会自动往右排，碰到窗口边缘就会自动换到下一行
        Rectangle{color:"green";width: 40;height: 40 }
        Rectangle{color:"red";width: 40;height: 40 }
        Rectangle{color:"blue";width: 40;height: 40 }
        Rectangle{color:"cyan";width: 40;height: 40 }
        Rectangle{color:"orange";width: 40;height: 40 }
        Rectangle{color:"black";width: 40;height: 40 }
        Rectangle{color:"green";width: 40;height: 40 }
        Rectangle{color:"red";width: 40;height: 40 }
        Rectangle{color:"blue";width: 40;height: 40 }
        Rectangle{color:"cyan";width: 40;height: 40 }
        Rectangle{color:"orange";width: 40;height: 40 }
        Rectangle{color:"black";width: 40;height: 40 }
        Rectangle{color:"green";width: 40;height: 40 }
        Rectangle{color:"red";width: 40;height: 40 }
        Rectangle{color:"blue";width: 40;height: 40 }
        Rectangle{color:"cyan";width: 40;height: 40 }
        Rectangle{color:"orange";width: 40;height: 40 }
        Rectangle{color:"black";width: 40;height: 40 }
        Rectangle{color:"green";width: 40;height: 40 }
        Rectangle{color:"red";width: 40;height: 40 }
        Rectangle{color:"blue";width: 40;height: 40 }
        Rectangle{color:"cyan";width: 40;height: 40 }
        Rectangle{color:"orange";width: 40;height: 40 }
        Rectangle{color:"black";width: 40;height: 40 }
        Rectangle{color:"green";width: 40;height: 40 }
    }
    */
}