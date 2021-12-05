#pragma once

#include <Foundation>

class AParticleEmitterHandle
{
public:
    virtual ~AParticleEmitterHandle() {}
    virtual void draw() const = 0;
};

class AParticle
{
    friend class AParticleEmitter;

    struct Data
    {
        Math::Vector position;
        float size;
        AColor color;
    } *data = nullptr;

public:

    static constexpr size_t getSize() { return sizeof(Data); }

    Math::Vector deltaPosition;
    float deltaSize;
    AColor deltaColor;
    int64_t interval;

    void update()
    {
        this->data->position += deltaPosition;
        this->data->size += deltaSize;
        this->data->color += deltaColor;
    }

};

class AParticleEmitter
{

    class AParticleSystem
    {

        bool running = true;
        AMilliseconds interval = AMilliseconds(17);
        std::thread thread;// = AThread(&AParticleSystem::run, this);
        AMutex mutex;
        Array<AParticleEmitter*> emitters;

    public:

        static AParticleSystem *instance() { static AParticleSystem system; return &system; }

        AParticleSystem()
        {
            this->thread = std::thread(&AParticleSystem::run, this);
        }

        ~AParticleSystem()
        {
            this->running = false;
            this->thread.join();
        }

        AMilliseconds emittingInterval() const { return this->interval; }
        void setEmittingInterval(AMilliseconds interval) { this->interval = interval; }

        void append(AParticleEmitter *emitter) { ArrayUtils::Add(this->emitters, emitter); }
        void remove(AParticleEmitter *emitter) { ArrayUtils::Remove(this->emitters, emitter); }

    private:

        void run()
        {
            while(this->running)
            {
                for(AParticleEmitter *emitter : this->emitters)
                {
                    for(AParticle &particle : emitter->particles)
                    {
                        particle.update();
                        if(particle.interval == 0)
                        {
                            emitter->reset(particle);
                        }
                        else
                        {
                            --particle.interval;
                        }
                    }
                }
                AThread::sleep(this->interval);
            }
        }

    };

    friend class AParticleSystem;

public:

    using PositionRange = Math::Templates::Range<Math::Vector>;
    using SizeRange = Math::Range;
    using ColorRange = Math::Templates::Range<AColor>;
    using IntervalRange = Math::Templates::Range<int64_t>;

private:

    bool emitting;

    PositionRange positionRange;
    SizeRange sizeRange = SizeRange(0.0f, 1.0f);
    ColorRange colorRange;

    PositionRange deltaPositionRange;
    SizeRange deltaSizeRange = SizeRange(0.0f);
    ColorRange deltaColorRange = ColorRange(AColor(AColorName::Black));

    IntervalRange intervalRange = IntervalRange(1000);
    IntervalRange initialIntervalRange = IntervalRange(0, 1000);

    Array<AParticle::Data> data;
    Array<AParticle> particles;
    ::SharedReference<AParticleEmitterHandle> handle;

public:

    static AMilliseconds emittingInterval() { return AParticleSystem::instance()->emittingInterval(); }
    static void setEmittingInterval(AMilliseconds interval) { AParticleSystem::instance()->setEmittingInterval(interval); }

    ~AParticleEmitter()
    {
        if(this->emitting)
            AParticleSystem::instance()->remove(this);
    }

    const PositionRange &getPositionRange() const { return this->positionRange; }
    void setPositionRange(const PositionRange &range) { this->positionRange = range; }

    const SizeRange &getSizeRange() const { return this->sizeRange; }
    void setSizeRange(const SizeRange &range) { this->sizeRange = range; }

    const ColorRange &getColorRange() const { return this->colorRange; }
    void setColorRange(const ColorRange &range) { this->colorRange = range; }

    const IntervalRange &getIntervalRange() const { return this->intervalRange; }
    void setIntervalRange(const IntervalRange &range) { this->intervalRange = range; }

    const PositionRange &getDeltaPositionRange() const { return this->deltaPositionRange; }
    void setDeltaPositionRange(const PositionRange &range) { this->deltaPositionRange = range; }

    const SizeRange &getDeltaSizeRange() const { return this->deltaSizeRange; }
    void setDeltaSizeRange(const SizeRange &range) { this->deltaSizeRange = range; }

    const ColorRange &getDeltaColorRange() const { return this->deltaColorRange; }
    void setDeltaColorRange(const ColorRange &range) { this->deltaColorRange = range; }

    size_t getSize() const { return this->particles.size(); }
    void setSize(size_t size)
    {
        this->particles.assign(size, AParticle());
        this->data.assign(size, AParticle::Data());
        initial();
    }

    void initial()
    {
        for(Array<AParticle>::size_type i = 0; i < this->particles.size(); ++i)
        {
            AParticle &particle = this->particles.at(i);
            particle.data = &this->data.at(i);
            particle.deltaPosition = this->deltaPositionRange.interpolate((rand() % 100) / 100.0f);
            particle.deltaSize = this->deltaSizeRange.interpolate((rand() % 100) / 100.0f);
            particle.deltaColor = this->deltaColorRange.interpolate((rand() % 100) / 100.0f);

            particle.data->position = this->positionRange.interpolate((rand() % 100) / 100.0f);
            particle.data->size = this->sizeRange.interpolate((rand() % 100) / 100.0f);
            particle.data->color = this->colorRange.interpolate((rand() % 100) / 100.0f);
            particle.interval = this->initialIntervalRange.interpolate((rand() % 100) / 100.0f);
        }
    }

    void update()
    {
        for(Array<AParticle>::size_type i = 0; i < this->particles.size(); ++i)
        {
            AParticle &particle = this->particles.at(i);
            particle.data = &this->data.at(i);
            reset(particle);
        }
    }

    void reset(AParticle &particle)
    {
        particle.deltaPosition = this->deltaPositionRange.interpolate((rand() % 100) / 100.0f);
        particle.deltaSize = this->deltaSizeRange.interpolate((rand() % 100) / 100.0f);
        particle.deltaColor = this->deltaColorRange.interpolate((rand() % 100) / 100.0f);

        particle.data->position = this->positionRange.interpolate((rand() % 100) / 100.0f);
        particle.data->size = this->sizeRange.interpolate((rand() % 100) / 100.0f);
        particle.data->color = this->colorRange.interpolate((rand() % 100) / 100.0f);
        particle.interval = this->intervalRange.interpolate((rand() % 100) / 100.0f);
    }

    const ::SharedReference<AParticleEmitterHandle> &getHandle() const { return this->handle; }
    void setHandle(const ::SharedReference<AParticleEmitterHandle> &handle) { this->handle = handle; }

    bool isEmitted() { return this->emitting; }
    void setEmitting(bool emitting)
    {
        if (this->emitting == emitting)
        {
            return;
        }

        this->emitting = emitting;
        if (this->emitting)
        {
            AParticleSystem::instance()->append(this);
        }
        else
        {
            AParticleSystem::instance()->remove(this);
        }
    }

    float *getData() { return &this->data[0].position.x; }
    const float *getData() const { return &this->data[0].position.x; }

};
