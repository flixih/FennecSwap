#include "pch.h"
#include "FennecSwap.h"

BAKKESMOD_PLUGIN(FennecSwap, "Fennec Body Swap", "1.0.0", PLUGINTYPE_FREEPLAY | PLUGINTYPE_CUSTOM_TRAINING | PLUGINTYPE_ONLINE)

constexpr int FENNEC_BODY_ID = 1568;

void FennecSwap::onLoad()
{
    enabled = std::make_shared<bool>(true);
    cvarManager->registerCvar("fennecswap_enabled", "1", "Enable Fennec body swap", true, true, 0, true, 1)
        .bindTo(enabled);

    HookEvents();
    cvarManager->log("FennecSwap plugin loaded! Use 'fennecswap_enabled 0/1' to toggle.");
}

void FennecSwap::onUnload()
{
    gameWrapper->UnhookEvent("Function TAGame.Car_TA.EventVehicleSetup");
    gameWrapper->UnhookEvent("Function GameEvent_Soccar_TA.Active.StartRound");
    gameWrapper->UnhookEvent("Function TAGame.GameEvent_Tutorial_TA.BeginState");
}

void FennecSwap::HookEvents()
{
    gameWrapper->HookEvent(
        "Function TAGame.Car_TA.EventVehicleSetup",
        [this](std::string eventName) { OnCarSpawned(eventName); }
    );
    gameWrapper->HookEvent(
        "Function GameEvent_Soccar_TA.Active.StartRound",
        [this](std::string eventName) { OnMatchLoaded(eventName); }
    );
    gameWrapper->HookEvent(
        "Function TAGame.GameEvent_Tutorial_TA.BeginState",
        [this](std::string eventName) { OnMatchLoaded(eventName); }
    );
}

void FennecSwap::ApplyFennecBody(CarWrapper car)
{
    if (car.IsNull()) return;
    auto body = car.GetBody();
    if (body.IsNull()) return;
    body.SetBodyID(FENNEC_BODY_ID);
}

void FennecSwap::OnCarSpawned(std::string eventName)
{
    if (!*enabled) return;
    if (!gameWrapper->IsInGame() && !gameWrapper->IsInFreeplay() && !gameWrapper->IsInCustomTraining()) return;
    gameWrapper->SetTimeout([this](GameWrapper* gw) {
        auto car = gw->GetLocalCar();
        if (!car.IsNull()) ApplyFennecBody(car);
    }, 0.1f);
}

void FennecSwap::OnMatchLoaded(std::string eventName)
{
    if (!*enabled) return;
    gameWrapper->SetTimeout([this](GameWrapper* gw) {
        auto car = gw->GetLocalCar();
        if (!car.IsNull()) ApplyFennecBody(car);
    }, 0.5f);
}
