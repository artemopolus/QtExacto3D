#ifndef QMLCONF_H
#define QMLCONF_H

#include <QObject>
//#include <QtGlobal>
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    // Qt 4
    #include <QDeclarativeEngine>
#else
    // Qt 5
    #include <QQmlEngine>
#endif

class qmlConf : public QObject
{
    Q_OBJECT
public:
    explicit qmlConf(QObject *parent = nullptr);
    // Do not forget to declare your class to the QML system.
#ifdef Q_OS_WIN
    const int FontSize = 18;
    const int ButtonHeight = 100;
#endif
#ifdef Q_OS_ANDROID
    const int FontSize = 48;
    const int ButtonHeight = 200;
#endif
    int getButtonHeight() {return ButtonHeight;}
    static void declareQML() {
        qmlRegisterType<qmlConf>("QMLstyle", 1, 0, "MyQMLstyleValues");
    }

signals:

public slots:
};

#endif // QMLCONF_H
