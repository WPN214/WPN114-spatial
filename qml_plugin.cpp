#include "qml_plugin.hpp"

#include <source/surround.hpp>
#include <QQmlEngine>
#include <qqml.h>

//-------------------------------------------------------------------------------------------------
void
qml_plugin::registerTypes(const char *uri)
//-------------------------------------------------------------------------------------------------
{
    Q_UNUSED(uri)

    qmlRegisterUncreatableType<SpeakerNode, 1>
    ("WPN114.Audio.Spatial", 1, 1, "SpeakerNode", "Uncreatable");

    qmlRegisterType<SingleSpeaker, 1>
    ("WPN114.Audio.Spatial", 1, 1, "Speaker");

    qmlRegisterType<SpeakerPair, 1>
    ("WPN114.Audio.Spatial", 1, 1, "SpeakerPair");

    qmlRegisterType<SpeakerRing, 1>
    ("WPN114.Audio.Spatial", 1, 1, "SpeakerRing");

    qmlRegisterType<SpeakerDome, 1>
    ("WPN114.Audio.Spatial", 1, 1, "SpeakerDome");

    qmlRegisterType<SpeakerSetup, 1>
    ("WPN114.Audio.Spatial", 1, 1, "SpeakerSetup");

    qmlRegisterType<Fields, 1>
    ("WPN114.Audio.Spatial", 1, 1, "Fields");
}
