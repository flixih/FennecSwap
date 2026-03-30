#include "pch.h"
#include "FennecSwap.h"

BAKKESMOD_PLUGIN(FennecSwap, "Fennec Body Swap", "1.0.0", PLUGINTYPE_FREEPLAY)

constexpr int FENNEC_BODY_ID = 1568;

void FennecSwap::onLoad()
{
    enabled = std::make_shared<bool>(true);
    cvarManager->registerCvar("fennecswap_enabled", "1", "Enable Fennec body swap").bindTo(enabled);

    gameWrapper->HookEvent("Function TAGame.GameEvent_Tutorial_TA.BeginState",
        [this](std::string eventName) {
            gameWrapper->SetTimeout([this](GameWrapper* gw) { ApplyFennec(); }, 0.5f);
        });

    gameWrapper->HookEvent("Function GameEvent_Soccar_TA.Active.StartRound",
        [this](std::string eventName) {
            gameWrapper->SetTimeout([this](GameWrapper* gw) { ApplyFennec(); }, 0.3f);
        });

    cvarManager->log("FennecSwap loaded! Use: fennecswap_enabled 0/1");
}

void FennecSwap::onUnload()
{
    gameWrapper->UnhookEvent("Function TAGame.GameEvent_Tutorial_TA.BeginState");
    gameWrapper->UnhookEvent("Function GameEvent_Soccar_TA.Active.StartRound");
}

void FennecSwap::ApplyFennec()
{
    if (!*enabled) return;
    cvarManager->executeCommand("itemmod_body " + std::to_string(FENNEC_BODY_ID));
}
