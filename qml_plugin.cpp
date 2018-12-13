#include "qml_plugin.hpp"

#include <source/rooms/rooms.hpp>
#include <QQmlEngine>
#include <qqml.h>

void qml_plugin::registerTypes(const char *uri)
{
    Q_UNUSED    ( uri );

    qmlRegisterUncreatableType<StreamNode, 1>   ( "WPN114.Spatial", 1, 0, "StreamNode","Uncreatable");
    qmlRegisterUncreatableType<RoomNode, 1>     ( "WPN114.Spatial", 1, 0, "RoomNode", "Uncreatable" );
    qmlRegisterUncreatableType<RoomSource, 1>   ( "WPN114.Spatial", 1, 0, "RoomSource", "Uncreatable");
    qmlRegisterType<Speaker, 1>                 ( "WPN114.Spatial", 1, 0, "Speaker" );
    qmlRegisterType<SpeakerArea, 1>             ( "WPN114.Spatial", 1, 0, "SpeakerArea" );

    qmlRegisterType<RoomSetup, 1>         ( "WPN114.Spatial", 1, 0, "RoomSetup" );
    qmlRegisterType<MonoSource, 1>        ( "WPN114.Spatial", 1, 0, "MonoSource" );
    qmlRegisterType<StereoSource, 1>      ( "WPN114.Spatial", 1, 0, "StereoSource" );
    qmlRegisterType<Rooms, 1>             ( "WPN114.Spatial", 1, 0, "Rooms" );
    qmlRegisterType<SpeakerPair, 1>       ( "WPN114.Spatial", 1, 0, "SpeakerPair" );
    qmlRegisterType<SpeakerRing, 1>       ( "WPN114.Spatial", 1, 0, "SpeakerRing" );
}
