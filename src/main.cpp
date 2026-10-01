#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(FrameWindowPlayLayer, PlayLayer) {
    struct Fields {
        double t240 = 0.0;
        CCLabelBMFont* label = nullptr;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        auto size = CCDirector::sharedDirector()->getWinSize();

        m_fields->label = CCLabelBMFont::create(
            "FWD 240TPS  Tick: 0",
            "bigFont.fnt"
        );

        m_fields->label->setAnchorPoint({0.f, 1.f});
        m_fields->label->setPosition({8.f, size.height - 8.f});
        m_fields->label->setScale(0.38f);
        m_fields->label->setZOrder(9999);

        this->addChild(m_fields->label);

        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        if (!m_fields->label)
            return;

        {
            m_fields->t240 += static_cast<double>(dt) * 240.0;
        }

        auto tick = static_cast<uint64_t>(m_fields->t240);

        m_fields->label->setString(
            fmt::format("FWD 240TPS  Tick: {}", tick).c_str()
        );
    }
};
