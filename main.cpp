#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>

#include "Parser.h"
#include "TextFilters.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ToolsEditsOfText toolEdit;
    ToolsEditsOfText *tl = &toolEdit;
    Dataset dataset;
    Dataset *data = &dataset;
    DataForVisualElements visualElem;
    DataForVisualElements *vel = &visualElem;
    InfoMessages message;
    InfoMessages *msg = &message;
    TextFilters txtFilters;
    Parser parser;
    parser.setDataset(data);
    parser.setToolEdit(tl);
    parser.setPforVisualElem(vel);
    parser.setPInfoMessage(msg);
    visualElem.setPInfoMessage(msg);
    txtFilters.setDataset(data);
    txtFilters.setToolEdit(tl);

    qmlRegisterSingletonInstance("myModul.Parser", 1, 0, "Parser", &parser);
    qmlRegisterSingletonInstance("myModul.Filters", 1, 0, "Filters", &txtFilters);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "WebParser_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/WebParser/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
