#include "modelextended.h"

// 构造函数：初始化数据
ModelExtended::ModelExtended(QObject *parent)
    : QAbstractTableModel(parent)
{
    // ---------- 编号数据 ----------
    empno[1] = "2022001";
    empno[2] = "2022002";
    empno[3] = "2022003";
    empno[4] = "2022004";
    empno[5] = "2022005";

    // ---------- 姓名数据 ----------
    empname[1] = "张三";
    empname[2] = "李四";
    empname[3] = "王五";
    empname[4] = "刘山";
    empname[5] = "张平";

    ModelFunc();   // 初始化表头和部门
}

// 初始化表头和部门
void ModelExtended::ModelFunc()
{
    // 表头标题
    viewlisttitle << "员工编号" << "员工姓名" << "所在部门";

    // 索引（相当于主键 1~5）
    empindex << 1 << 2 << 3 << 4 << 5;
    empnameindex << 1 << 2 << 3 << 4 << 5;

    // 部门数据
    empdepartment << "营销部" << "账务部" << "研发部" << "董事会" << "后勤部";
}

// rowCount —— 返回行数
int ModelExtended::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;                      // 表格模型无层级，父索引有效时返回 0
    return empindex.size();             // 5 行
}
// 为什么 parent.isValid() 时返回 0？
//   QAbstractTableModel 是扁平结构，无父子关系
//   如果 parent 有效，表示"某行的子行"，表格里不存在，所以返回 0

// columnCount —— 返回列数
int ModelExtended::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 3;                           // 3 列
}

// data —— 返回单元格数据（核心函数）
QVariant ModelExtended::data(const QModelIndex &index, int role) const
{
    // ---------- 1. 检查索引有效性 ----------
    if (!index.isValid())
        return QVariant();

    // ---------- 2. 只处理"显示角色" ----------
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            // 第 0 列：员工编号
            // index.row() = 当前行（0~4）
            // empindex[index.row()] = 索引（1~5）
            // empno.value(...) = 对应编号字符串
            return empno.value(empindex[index.row()]);

        case 1:
            // 第 1 列：员工姓名
            return empname.value(empnameindex[index.row()]);

        case 2:
            // 第 2 列：部门
            return empdepartment.value(index.row());

        default:
            return QVariant();
        }
    }

    // ---------- 3. 其它角色返回无效 ----------
    return QVariant();
}

// headerData —— 返回表头数据
QVariant ModelExtended::headerData(int section,
                                   Qt::Orientation orientation,
                                   int role) const
{
    // 只处理"水平表头"（列标题） + "显示角色"
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return viewlisttitle.value(section);

    // 其它情况交给基类处理（比如垂直表头返回 1,2,3...）
    return QAbstractTableModel::headerData(section, orientation, role);
}