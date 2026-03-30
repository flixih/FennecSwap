#include "pch.h"
#include "FennecSwap.h"

BAKKESMOD_PLUGIN(FennecSwap, "Fennec Body Swap", "1.0.0", PLUGINTYPE_FREEPLAY)

// Fennec body product ID
constexpr int FENNEC_BODY_ID = 1568;

void FennecSwap::onLoad()
{
    enabled = std::make_shared<bool>(true);
    cvarManager->registerCvar("fennecswap_enabled", "1", "Enable Fennec body swap")
        .bindTo(enabled);

    // Hook car spawning events
    gameWrapper->HookEventWithCaller<CarWrapper>(
        "Function TAGame.Car_TA.SetVehicleInput",
        [this](CarWrapper caller, void* params, std::string eventName) {
            if (!*enabled) return;
            if (!caller) return;
            // Only apply to local player's car
            CarWrapper localCar = gameWrapper->GetLocalCar();
            if (!localCar) return;
            if (caller.memory_address != localCar.memory_address) return;
            ApplyFennec();
        }
    );

    // Also apply when entering freeplay/game
    gameWrapper->HookEvent("Function TAGame.GameEvent_Tutorial_TA.BeginState",
        [this](std::string eventName) {
            gameWrapper->SetTimeout([this](GameWrapper* gw) { ApplyFennec(); }, 0.5f);
        });

    gameWrapper->HookEvent("Function GameEvent_Soccar_TA.Active.StartRound",
        [this](std::string eventName) {
            gameWrapper->SetTimeout([this](GameWrapper* gw) { ApplyFennec(); }, 0.3f);
        });

    LOG("FennecSwap loaded! Toggle: fennecswap_enabled 0/1");
}

void FennecSwap::onUnload()
{
    gameWrapper->UnhookEvent("Function TAGame.Car_TA.SetVehicleInput");
    gameWrapper->UnhookEvent("Function TAGame.GameEvent_Tutorial_TA.BeginState");
    gameWrapper->UnhookEvent("Function GameEvent_Soccar_TA.Active.StartRound");
}

void FennecSwap::ApplyFennec()
{
    if (!*enabled) return;
    CarWrapper car = gameWrapper->GetLocalCar();
    if (!car) return;

    // Get the loadout and change body ID to Fennec
    int currentBody = car.GetLoadoutBody();
    if (currentBody == FENNEC_BODY_ID) return; // already Fennec

    // Use item mod approach via cvar to set the body
    cvarManager->executeCommand("itemmod_body " + std::to_string(FENNEC_BODY_ID));
}
