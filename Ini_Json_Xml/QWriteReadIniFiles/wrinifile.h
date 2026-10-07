#ifndef WRINIFILE_H
#define WRINIFILE_H

// 三个全局函数（不是类的成员函数）
// 直接调用即可，不需要创建对象

void WriteIniFiles();      // 写配置文件
void ReadIniFiles();       // 读配置文件（按已知的键读取）
void ReadIniFilesIsKey();  // 读配置文件（遍历所有键）

#endif // WRINIFILE_H