#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/loader/SettingEvent.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;

        // Button erstellen mit Cocos2d-Standardmethoden
        auto spr = ButtonSprite::create("AC", 0, false, "goldFont.fnt", "GJ_button_01.png", 30, 0.6f);
        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(MyPlayLayer::toggleQoLAutoclicker)
        );

        auto menu = CCMenu::create();
        menu->addChild(btn);
        
        // Position: Unten links (X=30, Y=100)
        menu->setPosition({30, 100}); 
        this->addChild(menu, 100);

        return true;
    }

    void toggleQoLAutoclicker(CCObject* sender) {
        // Suche nach dem QoL Mod
        auto qolMod = Loader::get()->getLoadedMod("thesillydoggo.qolmod");
        
        if (qolMod) {
            // Wir prüfen sicherheitshalber, ob die Einstellung existiert
            if (qolMod->hasSetting("level/autoclicker")) {
                bool currentVal = qolMod->getSettingValue<bool>("level/autoclicker");
                
                // Toggle den Wert
                qolMod->setSettingValue("level/autoclicker", !currentVal);
                
                // Benachrichtigung anzeigen
                std::string status = !currentVal ? "Eingeschaltet" : "Ausgeschaltet";
                Notification::create("Autoclicker: " + status, NotificationIcon::Info)->show();
            } else {
                Notification::create("Setting 'level/autoclicker' nicht gefunden!", NotificationIcon::Error)->show();
            }
        } else {
            Notification::create("QoLMod nicht installiert!", NotificationIcon::Error)->show();
        }
    }
};
