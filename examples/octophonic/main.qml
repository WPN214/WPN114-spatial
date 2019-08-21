import QtQuick 2.12
import QtQuick.Window 2.12
import WPN114.Audio 1.1 as Audio
import WPN114.Audio.Sampling 1.1
import WPN114.Audio.Spatial 1.1 as Spatial

Window
{
    visible: true
    width: 640
    height: 480
    title: qsTr("sampler-octophonic")

    Spatial.SpeakerSetup
    {
        id: speaker_setup

        Spatial.SpeakerRing {
            nspeakers: 8
            phase: 1/16
        }
    }

    Audio.Graph
    {
        external.backend: Audio.External.Jack

        Spatial.Fields
        {
            setup: speaker_setup

            Sampler
            {
                id: sampler
                file: "audio/example.wav"
                spatial.width: 0.5
                spatial.radius: 0.1
                spatial.align: Spatial.Center
                spatial.attraction: Spatial.Center
                spatial.directivity: Spatial.Cardioid
            }
        }

        Component.onCompleted:
            sampler.play()
    }
}
