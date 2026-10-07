#include "readwritexml.h"
#include "ui_readwritexml.h"

// ==================== 构造函数 ====================
ReadWriteXml::ReadWriteXml(QWidget *parent)
    : QDialog(parent)              // 调用父类 QDialog 的构造函数
    , ui(new Ui::ReadWriteXml)     // 创建界面对象
{
    ui->setupUi(this);             // 加载 .ui 文件里的界面布局

    QDir dirs;                     // 创建目录对象（此处未使用，可删）
    strcurrentfilepath = "d:/xmlfiles";              // XML 文件所在目录
    strcurrentfilename = "/factoryworkersxml.xml";   // XML 文件名

    if (!dirs.exists(strcurrentfilepath)) {
        dirs.mkpath(strcurrentfilepath);
    }
}

// ==================== 析构函数 ====================
ReadWriteXml::~ReadWriteXml()
{
    delete ui;   // 释放界面对象，防止内存泄漏
}

// ==================== 打开指定文件 ====================
bool ReadWriteXml::openxmlfiles(QString filenamepath)
{
    // 拼接完整路径，例如 "d:/xmlfiles/factoryworkersxml.xml"
    m_qfiles.setFileName(strcurrentfilepath + filenamepath);

    // 以"读写 + 文本"方式打开文件
    // 返回 true 表示成功，false 表示失败（文件不存在、无权限等）
    return m_qfiles.open(QIODevice::ReadWrite | QFile::Text);
}

// ==================== 写入 XML 文件 ====================
void ReadWriteXml::writexmlfiles()
{
    // 先打开文件，失败则直接退出
    if (!openxmlfiles(strcurrentfilename))
    {
        qDebug() << "写入：打开XML文件失败，请重新检查？";
        return;
    }
    qDebug() << "写入：打开XML文件成功，请认真操作xml！";

    // 1. 创建 XML 文档对象
    QDomDocument domdoct;

    // 2. 写入 XML 头部声明：<?xml version="1.0" encoding="UTF-8"?>
    QDomProcessingInstruction version;
    version = domdoct.createProcessingInstruction(
        "xml", "version=\"1.0\" encoding=\"UTF-8\"");
    domdoct.appendChild(version);

    // 3. 创建根节点 <factory>
    QDomElement domrootelement = domdoct.createElement("factory");
    domdoct.appendChild(domrootelement);

    // 4. 创建父节点 <worker>
    QDomElement itemrootelement = domdoct.createElement("worker");
    {
        // ---------- 子节点1：工号 <WNo> ----------
        QDomElement node1 = domdoct.createElement("WNo");   // 创建元素 <WNo>
        QDomText domtext1 = domdoct.createTextNode("WNo");  // 创建文本节点
        domtext1.setData(ui->lineEdit_No->text());          // 把输入框内容设为文本
        node1.appendChild(domtext1);                        // 文本挂到 <WNo> 里
        itemrootelement.appendChild(node1);                 // <WNo> 挂到 <worker> 里

        // ---------- 子节点2：姓名 <WName> ----------
        QDomElement node2 = domdoct.createElement("WName");
        QDomText domtext2 = domdoct.createTextNode("WName");
        domtext2.setData(ui->lineEdit_Name->text());
        node2.appendChild(domtext2);
        itemrootelement.appendChild(node2);

        // ---------- 子节点3：性别 <WSex> ----------
        QDomElement node3 = domdoct.createElement("WSex");
        QDomText domtext3 = domdoct.createTextNode("WSex");
        domtext3.setData(ui->lineEdit_Sex->text());
        node3.appendChild(domtext3);
        itemrootelement.appendChild(node3);

        // ---------- 子节点4：学历 <WEducation> ----------
        QDomElement node4 = domdoct.createElement("WEducation");
        QDomText domtext4 = domdoct.createTextNode("WEducation");
        domtext4.setData(ui->lineEdit_Education->text());
        node4.appendChild(domtext4);
        itemrootelement.appendChild(node4);

        // ---------- 子节点5：部门 <WDepartment> ----------
        QDomElement node5 = domdoct.createElement("WDepartment");
        QDomText domtext5 = domdoct.createTextNode("WDepartment");
        domtext5.setData(ui->lineEdit_Department->text());
        node5.appendChild(domtext5);
        itemrootelement.appendChild(node5);

        // ---------- 子节点6：工资 <WSalary> ----------
        QDomElement node6 = domdoct.createElement("WSalary");
        QDomText domtext6 = domdoct.createTextNode("WSalary");
        domtext6.setData(ui->lineEdit_Salary->text());
        node6.appendChild(domtext6);
        itemrootelement.appendChild(node6);
    }

    // 5. 把 <worker> 挂到根节点 <factory>
    domrootelement.appendChild(itemrootelement);

    // 6. 把整个 XML 文档转成字符串并写入文件
    //    toLocal8Bit() 转本地编码，data() 转 const char*
    m_qfiles.write(domdoct.toString().toLocal8Bit().data());
    m_qfiles.close();   // 关闭文件（重要，否则数据可能没落盘）

    // 7. 弹窗提示成功
    QMessageBox::information(this, "提示",
                             "恭喜你，写入XML文件数据成功，请查看目录文件?", QMessageBox::Yes);
}

// ==================== 读取 XML 文件 ====================
void ReadWriteXml::readxmlfiles()
{
    // 1. 打开文件
    if (!openxmlfiles(strcurrentfilename))
    {
        qDebug() << "读取：打开XML文件失败，请重新检查？";
        return;
    }
    qDebug() << "读取：打开XML文件成功，请认真操作xml!";

    // 2. 把文件内容解析成 XML 文档树
    QDomDocument docs;
    if (!docs.setContent(&m_qfiles))
    {
        m_qfiles.close();
        qDebug() << "读取：操作setContent失败,请重新检查？";
        return;
    }
    qDebug() << "读取：操作setContent成功,请认真操作!";

    // 3. 获取根节点（这里是 <factory>）
    QDomElement root = docs.documentElement();

    // 4. 获取第一个子节点
    QDomNode node = root.firstChild();

    // 5. 循环遍历所有兄弟节点
    while (!node.isNull())
    {
        QDomNodeList sonlist = node.childNodes();       // 当前节点的所有子节点
        QString rootname = node.toElement().tagName();  // 当前节点的标签名

        if (rootname.compare("worker") == 0)            // 如果是 <worker>
        {
            readrootxml(sonlist);                       // 交给子函数处理
        }
        node = node.nextSibling();                      // 移到下一个兄弟节点
    }
}

// ==================== 读取子节点数据 ====================
void ReadWriteXml::readrootxml(QDomNodeList sonnodelist)
{
    // 遍历 worker 的所有子节点
    for (int sonnode = 0; sonnode < sonnodelist.size(); sonnode++)
    {
        // 取出当前子节点并转成元素
        QDomElement sonelement = sonnodelist.at(sonnode).toElement();

        // 根据标签名判断是哪个字段，填到对应只读输入框
        if (sonelement.tagName().compare("WNo") == 0)
            ui->lineEdit_No_R->setText(sonelement.text());

        else if (sonelement.tagName().compare("WName") == 0)
            ui->lineEdit_Name_R->setText(sonelement.text());

        else if (sonelement.tagName().compare("WSex") == 0)
            ui->lineEdit_Sex_R->setText(sonelement.text());

        else if (sonelement.tagName().compare("WEducation") == 0)
            ui->lineEdit_Education_R->setText(sonelement.text());

        else if (sonelement.tagName().compare("WDepartment") == 0)
            ui->lineEdit_Department_R->setText(sonelement.text());

        else if (sonelement.tagName().compare("WSalary") == 0)
            ui->lineEdit_Salary_R->setText(sonelement.text());
    }
}

// ==================== "写入"按钮点击 ====================
void ReadWriteXml::on_pushButton_WriteXml_clicked()
{
    writexmlfiles();   // 调用写入函数
}

// ==================== "读取"按钮点击 ====================
void ReadWriteXml::on_pushButton_ReadXml_clicked()
{
    readxmlfiles();    // 调用读取函数
}