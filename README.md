# FennecSwap — BakkesMod Plugin
### Makes your car appear as a Fennec (client-side only)

---

## What this does
- Swaps your car's rendered body to a Fennec visually
- Works in: Freeplay, Custom Training, Online matches
- **Client-side only** — other players still see your actual car body
- Has an in-game settings toggle (F2 → Plugins → Fennec Body Swap)

---

## How to Build

### Requirements
- **Windows 10/11**
- **Visual Studio 2022** (with "Desktop development with C++" workload)
- **BakkesMod Plugin Template** (easiest way to get the SDK)

---

### Step 1 — Get the BakkesMod Plugin Template

1. Go to: https://github.com/bakkesmodorg/BakkesModPluginTemplate
2. Click **"Use this template"** → Create a new repo (or just download the ZIP)
3. Clone/open it locally

---

### Step 2 — Drop in the plugin files

Replace the template's source files with these three files:
```
FennecSwap.h
FennecSwap.cpp
pch.h
```

Make sure `pch.h` is set as the **Precompiled Header** in your .vcxproj:
- Right-click `pch.h` → Properties → C/C++ → Precompiled Header → **Create (/Yc)**
- Right-click `FennecSwap.cpp` → Properties → C/C++ → Precompiled Header → **Use (/Yu)**

---

### Step 3 — Configure the project

In Visual Studio:
- Set configuration to **Release | x64**
- The BakkesMod SDK paths should already be set by the template

---

### Step 4 — Build

Press **Ctrl+Shift+B** or go to **Build → Build Solution**

Output DLL will be at:
```
x64/Release/FennecSwap.dll
```

---

### Step 5 — Install in BakkesMod

1. Copy `FennecSwap.dll` to:
   ```
   C:\Users\<YOU>\AppData\Roaming\bakkesmod\bakkesmod\plugins\
   ```

2. Open Rocket League with BakkesMod running

3. Open the BakkesMod console (F6) and type:
   ```
   plugin load fennecswap
   ```

4. To load it automatically every time, open BakkesMod settings (F2):
   **Plugins → Plugin Manager → check FennecSwap**

---

## Usage

- **F2 → Plugins → Fennec Body Swap** — toggle on/off
- Or use the console cvar:
  ```
  fennecswap_enabled 1   (on)
  fennecswap_enabled 0   (off)
  ```

---

## Notes

- If the swap doesn't apply immediately, drive around / respawn and it'll kick in
- This is purely cosmetic and local — no risk of bans for visual-only mods
- If RL updates and breaks the body ID, the Fennec ID to look for is **1568**

---

## Files
| File | Purpose |
|------|---------|
| `FennecSwap.h` | Plugin class declaration |
| `FennecSwap.cpp` | All plugin logic + settings UI |
| `pch.h` | Precompiled header (required by BakkesMod SDK) |
