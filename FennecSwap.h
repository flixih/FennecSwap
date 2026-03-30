#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginsettingswindow.h"

class FennecSwap : public BakkesMod::Plugin::BakkesModPlugin,
                   public BakkesMod::Plugin::PluginSettingsWindow
{
public:
    void onLoad() override;
    void onUnload() override;

    // Settings window
    void RenderSettings() override;
    std::string GetPluginName() override;
    void SetImGuiContext(uintptr_t ctx) override;

private:
    void HookEvents();
    void ApplyFennecBody(CarWrapper car);
    void OnMatchLoaded(std::string eventName);
    void OnCarSpawned(std::string eventName);

    std::shared_ptr<bool> enabled;
};
