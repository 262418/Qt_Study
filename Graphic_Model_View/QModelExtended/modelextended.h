#ifndef MODELEXTENDED_H
#define MODELEXTENDED_H

#include <QAbstractTableModel>    // 表格模型基类
#include <QVector>                // Qt 动态数组
#include <QMap>                   // Qt 键值对
#include <QStringList>            // 字符串列表

// ============================================================================
// ModelExtended —— 自定义表格模型
// 继承 QAbstractTableModel，重写 4 个虚函数
// ============================================================================
class ModelExtended : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModelExtended(QObject *parent = 0);   // 建议用 nullptr

    // ---------- 必须重写的 4 个虚函数 ----------
    // 行数
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // 列数
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // 单元格数据（核心）
    QVariant data(const QModelIndex &index, int role) const override;

    // 表头数据
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;

public slots:

private:
    // ---------- 数据存储 ----------
    // 索引向量（相当于数据库主键）
    QVector<short> empindex;        // 员工编号索引
    QVector<short> empnameindex;    // 员工姓名索引

    // 键值对存储（键 → 值）
    QMap<short, QString> empno;        // 编号索引 → 编号字符串
    QMap<short, QString> empname;      // 姓名索引 → 姓名字符串

    // 表头和部门数据
    QStringList viewlisttitle;      // 表头标题
    QStringList empdepartment;       // 部门列表

    // 初始化数据
    void ModelFunc();
};

#endif