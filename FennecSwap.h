#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"

class FennecSwap : public BakkesMod::Plugin::BakkesModPlugin
{
public:
    void onLoad() override;
    void onUnload() override;

private:
    void HookEvents();
    void ApplyFennecBody(CarWrapper car);
    void OnMatchLoaded(std::string eventName);
    void OnCarSpawned(std::string eventName);

    std::shared_ptr<bool> enabled;
};
