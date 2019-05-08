#include <QApplication>
#include <QQmlApplicationEngine>

#include <QGuiApplication>
#include<QQmlContext>

#include <QtQuick/QQuickView>

#include "squircle.h"
#include "../exactolib/basecore.h"
#include "qmlconf.h"

#include <QStringList>

//! [1]
int main(int argc, char **argv)
{

    QGuiApplication app(argc, argv);

    qmlRegisterType<Squircle>("OpenGLUnderQML", 1, 0, "Squircle");

    qmlConf::declareQML();



    QQuickView view;
    QQmlContext * context = view.rootContext();
    BaseSystem basis;
    context->setContextProperty("basis",&basis);

    QStringList cmdlist = basis.getCommandNames();
    context->setContextProperty("cmdModel", QVariant::fromValue(cmdlist));
#ifdef Q_OS_WIN
    QStringList comportlist = basis.getComPortsList();
    context->setContextProperty("comportModel", QVariant::fromValue(comportlist));
    QStringList baudratelist = basis.getComBaudRate();
    context->setContextProperty("baudrateModel", QVariant::fromValue(baudratelist));
#endif

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();

}
//! [1]
