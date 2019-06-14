#include "qml_plugin.hpp"

#include <source/surround.hpp>
#include <QQmlEngine>
#include <qqml.h>

void qml_plugin::registerTypes(const char *uri)
{
    Q_UNUSED(uri)

    qmlRegisterUncreatableType<SpeakerNode, 1>
    ("WPN114.Audio.Spatial", 1, 1, "SpeakerNode", "Uncreatable");

    qmlRegisterType<SpeakerSetup, 1>
    ("WPN114.Audio.Spatial", 1, 1, "SpeakerSetup");

    qmlRegisterType<Surround, 1>
    ("WPN114.Audio.Spatial", 1, 1, "Surround");
}
