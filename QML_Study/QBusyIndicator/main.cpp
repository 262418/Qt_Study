#include <QGuiApplication>       // GUI 应用程序基类（非 QWidget）
#include <QQmlApplicationEngine> // QML 引擎，负责加载和运行 QML

int main(int argc, char *argv[])
{
    // 开启高 DPI 缩放（让界面在高分屏上不模糊）
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // 创建 Qt 应用程序对象（QML 程序用 QGuiApplication，不是 QApplication）
    QGuiApplication app(argc, argv);

    // 创建 QML 引擎
    QQmlApplicationEngine engine;

    // QML 文件的路径（注意 qrc:/ 表示从资源文件里加载）
    const QUrl url(QStringLiteral("qrc:/QBusyIndicator/main.qml"));

    // 如果 QML 加载失败（比如语法错误），退出程序
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    // 加载 QML 文件
    engine.load(url);

    // 进入事件循环
    return app.exec();
}