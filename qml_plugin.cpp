#include "qml_plugin.hpp"

#include <source/rooms/rooms.hpp>
#include <QQmlEngine>
#include <qqml.h>

void qml_plugin::registerTypes(const char *uri)
{
    Q_UNUSED    ( uri );

    qmlRegisterType<RoomSetup, 1>         ( "WPN114.Spatial", 1, 0, "RoomSetup" );
    qmlRegisterType<MonoSource, 1>        ( "WPN114.Spatial", 1, 0, "MonoSource" );
    qmlRegisterType<StereoSource, 1>      ( "WPN114.Spatial", 1, 0, "StereoSource" );
    qmlRegisterType<Rooms, 1>             ( "WPN114.Spatial", 1, 0, "Rooms" );
    qmlRegisterType<SpeakerPair, 1>       ( "WPN114.Spatial", 1, 0, "SpeakerPair" );
    qmlRegisterType<SpeakerRing, 1>       ( "WPN114.Spatial", 1, 0, "SpeakerRing" );
}
