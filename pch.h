#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginsettingswindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "bakkesmod/wrappers/includes.h"
#include "imgui/imgui.h"
#include <memory>
#include <string>

template <typename S, typename... Args>
void LOG(const S& formatStr, Args&&... args) {
    std::string logMsg = fmt::format(formatStr, std::forward<Args>(args)...);
    globalCvarManager->log(logMsg);
}
