#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"

class FennecSwap : public BakkesMod::Plugin::BakkesModPlugin
{
public:
    void onLoad() override;
    void onUnload() override;

private:
    void ApplyFennec();
    std::shared_ptr<bool> enabled;
};
