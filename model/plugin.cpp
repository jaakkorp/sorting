#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/qqml.h>

#include "sortboxmodel.h"
#include "raceresults.h"
#include "readysteadygo.h"

QT_USE_NAMESPACE

class SortBoxModelPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface" FILE "plugin.json")

public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("Qt.labs.sortingmodel"));

        qmlRegisterType<SortBoxModel>(uri, 1, 0, "SortBoxModel");
        qmlRegisterType<RaceResults>(uri, 1, 0, "RaceResults");
        qmlRegisterType<ReadySteadyGo>(uri, 1, 0, "ReadySteadyGo");
    }
};

#include "plugin.moc"
