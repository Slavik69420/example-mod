#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;

        // Button erstellen
        auto spr = ButtonSprite::create("AC", 0, false, "goldFont.fnt", "GJ_button_01.png", 30, 0.6f);
        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(MyPlayLayer::toggleQoLAutoclicker)
        );

        auto menu = CCMenu::create();
        menu->addChild(btn);
        menu->setPosition({50, 150}); // Position auf dem Bildschirm
        this->addChild(menu, 100);

        return true;
    }

    void toggleQoLAutoclicker(CCObject*) {
        // 1. Hole dir den QoLMod über seine ID
        auto qolMod = Loader::get()->getLoadedMod("thesillydoggo.qolmod");
        
        if (qolMod) {
            // 2. Suche die Einstellung für den Autoclicker
            // Laut Source Code heißt der Key oft "level/autoclicker"
            auto setting = qolMod->getSettingValue<bool>("level/autoclicker");
            
            // 3. Wert umkehren (Toggle)
            qolMod->setSettingValue("level/autoclicker", !setting);
            
            // Optisches Feedback (optional)
            Notification::create(
                std::string("Autoclicker: ") + (!setting ? "AN" : "AUS"),
                NotificationIcon::Info
            )->show();
        } else {
            log::error("QoLMod wurde nicht gefunden!");
        }
    }
};
