#include "pch.h"
#include "FennecSwap.h"

BAKKESMOD_PLUGIN(FennecSwap, "Fennec Body Swap", "1.0.0", PLUGINTYPE_FREEPLAY | PLUGINTYPE_CUSTOM_TRAINING | PLUGINTYPE_ONLINE)

// Fennec car body ID in Rocket League
constexpr int FENNEC_BODY_ID = 1568;

void FennecSwap::onLoad()
{
    enabled = std::make_shared<bool>(true);
    cvarManager->registerCvar("fennecswap_enabled", "1", "Enable Fennec body swap", true, true, 0, true, 1)
        .bindTo(enabled);

    HookEvents();
    LOG("FennecSwap plugin loaded!");
}

void FennecSwap::onUnload()
{
    gameWrapper->UnhookEvent("Function TAGame.Car_TA.EventVehicleSetup");
    gameWrapper->UnhookEvent("Function GameEvent_Soccar_TA.Active.StartRound");
    LOG("FennecSwap plugin unloaded.");
}

void FennecSwap::HookEvents()
{
    // Fires every time a car is set up / respawned
    gameWrapper->HookEvent(
        "Function TAGame.Car_TA.EventVehicleSetup",
        [this](std::string eventName) { OnCarSpawned(eventName); }
    );

    // Also re-apply on round start (kickoff)
    gameWrapper->HookEvent(
        "Function GameEvent_Soccar_TA.Active.StartRound",
        [this](std::string eventName) { OnMatchLoaded(eventName); }
    );

    // Apply in freeplay on load
    gameWrapper->HookEvent(
        "Function TAGame.GameEvent_Tutorial_TA.BeginState",
        [this](std::string eventName) { OnMatchLoaded(eventName); }
    );
}

void FennecSwap::ApplyFennecBody(CarWrapper car)
{
    if (car.IsNull()) return;

    // Get the car's body component and set body ID to Fennec
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
        if (!car.IsNull()) {
            ApplyFennecBody(car);
        }
    }, 0.1f); // slight delay so the car finishes loading
}

void FennecSwap::OnMatchLoaded(std::string eventName)
{
    if (!*enabled) return;

    gameWrapper->SetTimeout([this](GameWrapper* gw) {
        auto car = gw->GetLocalCar();
        if (!car.IsNull()) {
            ApplyFennecBody(car);
        }
    }, 0.5f);
}

// ---- Settings Window ----

void FennecSwap::RenderSettings()
{
    ImGui::TextUnformatted("Fennec Body Swap");
    ImGui::Separator();
    ImGui::Spacing();

    bool en = *enabled;
    if (ImGui::Checkbox("Enable Fennec Body Swap", &en)) {
        cvarManager->getCvar("fennecswap_enabled").setValue(en);
    }

    ImGui::Spacing();
    ImGui::TextDisabled("Makes your car look like a Fennec (client-side only).");
    ImGui::TextDisabled("Other players still see your actual car.");
}

std::string FennecSwap::GetPluginName()
{
    return "Fennec Body Swap";
}

void FennecSwap::SetImGuiContext(uintptr_t ctx)
{
    ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}
