#pragma once

#include <wpn114audio/spatial.hpp>
#include <QVector3D>

// ================================================================================================
class Speaker
// ================================================================================================
{

public:

    sample_t
    x = 0,
    y = 0,
    z = 0,
    v_orientation = 0,
    h_orientation = 0;

    //---------------------------------------------------------------------------------------------
    Speaker()
    //---------------------------------------------------------------------------------------------
    {

    }
};

// ================================================================================================
class SpeakerNode : public QObject, public QQmlParserStatus
// ================================================================================================
{
    Q_OBJECT

    Q_INTERFACES (QQmlParserStatus)

    Q_PROPERTY  (QVector3D coordinates READ coordinates WRITE set_coordinates)
    Q_PROPERTY  (qreal width READ width WRITE set_width)
    Q_PROPERTY  (qreal height READ height WRITE set_height)
    Q_PROPERTY  (qreal depth READ depth WRITE set_depth)

protected:

    QVector3D
    m_coordinates;

    qreal
    m_width     = 0,
    m_height    = 0,
    m_depth     = 0;

    std::vector<Speaker>
    m_speakers;

public:

    //---------------------------------------------------------------------------------------------
    virtual void
    classBegin() override {}

    //---------------------------------------------------------------------------------------------
    virtual void
    componentComplete() override {}

    //---------------------------------------------------------------------------------------------
    nchannels_t
    nspeakers() const { return m_speakers.size(); }

    //---------------------------------------------------------------------------------------------
    std::vector<Speaker>&
    speakers() { return m_speakers; }

    //---------------------------------------------------------------------------------------------
    QVector3D
    coordinates() const { return m_coordinates; }

    qreal
    width() const { return m_width; }

    qreal
    height() const { return m_height; }

    qreal
    depth() const { return m_depth; }

    //---------------------------------------------------------------------------------------------
    void
    set_coordinates(QVector3D coordinates)
    //---------------------------------------------------------------------------------------------
    {
        m_coordinates = coordinates;
    }

    //---------------------------------------------------------------------------------------------
    void
    set_width(qreal width)
    //---------------------------------------------------------------------------------------------
    {
        m_width = width;
    }

    //---------------------------------------------------------------------------------------------
    void
    set_height(qreal height)
    //---------------------------------------------------------------------------------------------
    {
        m_height = height;
    }

    //---------------------------------------------------------------------------------------------
    void
    set_depth(qreal depth)
    //---------------------------------------------------------------------------------------------
    {
        m_depth = depth;
    }
};

// ================================================================================================
class SingleSpeaker : public SpeakerNode
// ================================================================================================
{
    Q_OBJECT

public:

    //---------------------------------------------------------------------------------------------
    SingleSpeaker() {}

    //---------------------------------------------------------------------------------------------
    virtual void
    componentComplete() override
    //---------------------------------------------------------------------------------------------
    {
        Speaker s;
        s.x = m_coordinates.x();
        s.y = m_coordinates.y();
        s.z = m_coordinates.z();

        m_speakers.push_back(s);
    }

};

// ================================================================================================
class SpeakerPair : public SpeakerNode
// ================================================================================================
{
    Q_OBJECT

public:

    //---------------------------------------------------------------------------------------------
    SpeakerPair()
    //---------------------------------------------------------------------------------------------
    {

    }

    //---------------------------------------------------------------------------------------------
    virtual void
    componentComplete() override
    //---------------------------------------------------------------------------------------------
    {

    }

};

// ================================================================================================
class SpeakerRing : public SpeakerNode
// ================================================================================================
{
    Q_OBJECT

    Q_PROPERTY (int nspeakers READ nspeakers WRITE set_nspeakers)
    Q_PROPERTY (qreal phase READ phase WRITE set_phase)

    qreal
    m_phase = 0;

    nchannels_t
    m_nspeakers = 0;

public:

    //--------------------------------------------------------------------------------------------
    SpeakerRing()
    //--------------------------------------------------------------------------------------------
    {

    }

    //--------------------------------------------------------------------------------------------
    virtual void
    componentComplete() override
    //--------------------------------------------------------------------------------------------
    {
        nchannels_t index = 0;

        for (nchannels_t n = 0; n < m_nspeakers; ++n)
        {
            Speaker s;
            qreal p = (qreal)index/m_nspeakers*M_PI*2+m_phase;
            qreal x = (std::sin(p)+1)/2;
            qreal y = (std::cos(p)+1)/2;

            s.x = x;
            s.y = y;
            s.z = m_coordinates.z();
            m_speakers.push_back(s);
            index++;
        }

    }

    //--------------------------------------------------------------------------------------------
    qreal
    phase() const { return m_phase; }

    //--------------------------------------------------------------------------------------------
    void
    set_phase(qreal phase)
    //--------------------------------------------------------------------------------------------
    {
        m_phase = phase*M_PI*2;
    }

    //--------------------------------------------------------------------------------------------
    void
    set_nspeakers(nchannels_t nspeakers)
    //--------------------------------------------------------------------------------------------
    {
        m_nspeakers = nspeakers;
    }

};

// ================================================================================================
class SpeakerDome : public SpeakerNode
// ================================================================================================
{
    Q_OBJECT

public:

    //--------------------------------------------------------------------------------------------
    SpeakerDome()
    //--------------------------------------------------------------------------------------------
    {

    }

    //--------------------------------------------------------------------------------------------
    virtual void
    componentComplete() override
    //--------------------------------------------------------------------------------------------
    {

    }

};

// ================================================================================================
class SpeakerSetup : public QObject, public QQmlParserStatus
// ================================================================================================
{
    Q_OBJECT   

    Q_CLASSINFO   ( "DefaultProperty", "nodes" )
    Q_INTERFACES  ( QQmlParserStatus )

    Q_PROPERTY (QQmlListProperty<SpeakerNode> nodes READ nodes)

    std::vector<Speaker>
    m_speakers;

    QVector<SpeakerNode*>
    m_nodes;

public:

    //---------------------------------------------------------------------------------------------
    SpeakerSetup() {}

    //---------------------------------------------------------------------------------------------
    virtual void
    classBegin() override {}

    //---------------------------------------------------------------------------------------------
    virtual void
    componentComplete() override
    //---------------------------------------------------------------------------------------------
    {
        for (auto& node : m_nodes) {
            auto& speakers = node->speakers();
            for (auto& speaker : speakers)
                m_speakers.push_back(speaker);
        }
    }

    //---------------------------------------------------------------------------------------------
    Q_INVOKABLE nchannels_t
    nspeakers() const { return m_speakers.size(); }

    //---------------------------------------------------------------------------------------------
    std::vector<Speaker>&
    speakers()
    //---------------------------------------------------------------------------------------------
    {
        return m_speakers;
    }

    // --------------------------------------------------------------------------------------------
    QQmlListProperty<SpeakerNode>
    nodes()
    // --------------------------------------------------------------------------------------------
    {
        return QQmlListProperty<SpeakerNode>(
               this, this,
               &SpeakerSetup::append_node,
               &SpeakerSetup::nnodes,
               &SpeakerSetup::node,
               &SpeakerSetup::clear_nodes);
    }

    // --------------------------------------------------------------------------------------------
    Q_INVOKABLE void
    append_node(SpeakerNode* node) { m_nodes.push_back(node); }

    // --------------------------------------------------------------------------------------------
    Q_INVOKABLE int
    nnodes() const { return m_nodes.count(); }

    // --------------------------------------------------------------------------------------------
    Q_INVOKABLE SpeakerNode*
    node(int index) const { return m_nodes[index]; }

    // --------------------------------------------------------------------------------------------
    Q_INVOKABLE void
    clear_nodes() { m_nodes.clear(); }

    // --------------------------------------------------------------------------------------------
    static void
    append_node(QQmlListProperty<SpeakerNode>* list, SpeakerNode* node)
    // static Qml version, see above
    {
        reinterpret_cast<SpeakerSetup*>(list->data)->append_node(node);
    }

    // --------------------------------------------------------------------------------------------
    static int
    nnodes(QQmlListProperty<SpeakerNode>* list)
    // static Qml version, see above
    {
        return reinterpret_cast<SpeakerSetup*>(list)->nnodes();
    }

    // --------------------------------------------------------------------------------------------
    static SpeakerNode*
    node(QQmlListProperty<SpeakerNode>* list, int index)
    // static Qml version, see above
    {
        return reinterpret_cast<SpeakerSetup*>(list)->node(index);
    }

    // --------------------------------------------------------------------------------------------
    static void
    clear_nodes(QQmlListProperty<SpeakerNode>* list)
    // static Qml version, see above
    {
        reinterpret_cast<SpeakerSetup*>(list)->clear_nodes();
    }
};

// ================================================================================================
class Fields : public SpatialProcessor
// ================================================================================================
{
    Q_OBJECT

    Q_PROPERTY (SpeakerSetup* setup READ setup WRITE set_setup)

    std::vector<Speaker>
    m_speakers;

    SpeakerSetup*
    m_setup = nullptr;

public:

    //---------------------------------------------------------------------------------------------
    Fields()
    //---------------------------------------------------------------------------------------------
    {
        m_dispatch = Dispatch::Expand;
    }

    //---------------------------------------------------------------------------------------------
    virtual void
    componentComplete() override
    //---------------------------------------------------------------------------------------------
    {
        SpatialProcessor::componentComplete();
        m_speakers = m_setup->speakers();
    }

    //---------------------------------------------------------------------------------------------
    SpeakerSetup*
    setup() { return m_setup; }

    //---------------------------------------------------------------------------------------------
    void
    set_setup(SpeakerSetup* setup)
    //---------------------------------------------------------------------------------------------
    {
        m_setup = setup;
    }

    //---------------------------------------------------------------------------------------------
    virtual void
    rwrite(pool& inputs, pool& outputs, vector_t nframes) override
    //---------------------------------------------------------------------------------------------
    {
        nchannels_t ctarget = 0;

        for (auto& source : m_spatial_inputs)
        {
            for (nchannels_t c = 0; c < source->nchannels(); ++c)
            {
                // fetch target channel's spatial properties
                auto x = source->get_x()->buffer<audiobuffer_t>()[c];
                auto y = source->get_y()->buffer<audiobuffer_t>()[c];
                auto z = source->get_z()->buffer<audiobuffer_t>()[c];
                auto d = source->get_directivity()->buffer<audiobuffer_t>()[c];
                auto ho = source->get_h_orientation()->buffer<audiobuffer_t>()[c];
                auto vo = source->get_v_orientation()->buffer<audiobuffer_t>()[c];

                // fetch audio channel
                auto in = inputs.audio[0][ctarget];

                for (nchannels_t s = 0; s < m_speakers.size(); ++s)
                {
                    auto speaker = m_speakers[s];
                    auto out = outputs.audio[0][s];

                    for (vector_t f = 0; f < nframes; ++f)
                    {
                        sample_t dx = std::fabs(x[f]-speaker.x);
                        sample_t dy = std::fabs(y[f]-speaker.y);
                        sample_t dz = std::fabs(z[f]-speaker.z);

                        sample_t dh = sqrt(dx*dx+dy*dy);
                        sample_t hg = dh/1;
                        sample_t vg = dz/1;

                        if  (hg > 1 || vg > 1)
                             out[f] = 0;
                        else out[f] = (1-hg)*(1-vg);
                    }
                }

                ctarget++;
            }
        }
    }
};
