# 🏖️ Aloha

**Aloha** is a lightweight, extensible framework for building cross-platform applications and games using **Lua scripting** as the primary development language.  
It currently supports **PC** (via [Raylib](https://www.raylib.com)) and **Nintendo 3DS** (via [Citro2D](https://github.com/devkitPro/citro2d)), with additional platforms planned for the future.


## ✨ Features

- 🧠 **Full Lua integration** — logic, rendering, and window handling are all scriptable.
- 💻 **Cross-platform rendering backends:**
  - **Raylib** on PC
  - **Citro2D** on Nintendo 3DS
- 🎮 Simple drawing API (rectangles, circles, colors, windows, etc.)
- ⚙️ Built with **CMake** for easy configuration and portability.
- 🧩 Includes a **demo Lua project** (`example.lua`) to showcase basic functionality.
- 📦 Modular Lua architecture (`Aloha` namespace).


## 🛠️ Building the Project

### Prerequisites

- **CMake** 3.13 or newer  
- **Lua 5.1+** development files  
- **Raylib** (for PC build)  
- **Catnip SDK** (for 3DS build)

### PC Build

```bash
git clone https://github.com/Licantropo3392/Aloha.git
cd aloha
cmake -B build -S .
cmake --build build
./build/aloha
```

### Nintendo 3DS (Catnip) Build

Ensure you have the [devkitPro environment](https://devkitpro.org/wiki/Getting_Started) set up with Catnip installed.

Make sure your Lua files are located inside the romfs directory — they will be automatically bundled into a single file.

```bash
git clone https://github.com/Licantropo3392/Aloha.git
cd aloha
catnip -T 3ds -B 3ds
```

This produces a .3dsx binary that can be launched through the Homebrew Launcher.


## ▶️ Running

### PC

Simply run the executable — it will automatically load the Lua files from the romfs directory.

### Nintendo 3DS

After building, copy the Aloha.3dsx file from 3ds/main.release/ to your SD card.

You can also use 3dslink to send the build over the network (recommended):

Open the Homebrew Launcher on your 3DS and press Y — it should display a message saying it's waiting for a 3dslink connection.

On your PC, run:

```bash
3dslink 3ds/main.release/Aloha.3dsx
```

This will copy the file to your SD card and launch it automatically.


## 🧠 Lua Example

This demo shows how Aloha handles rendering and timing directly from Lua, running identically on both PC and Nintendo 3DS.

First, the script sets up a platform-specific window:

```lua
if Aloha.__3DS__ then
    window = Aloha.Window:New(400, 240, 60, "Aloha 3DS")
else
    window = Aloha.Window:New(800, 480, 180, "Aloha PC")
end
```

Then it creates two drawable objects — a blue rectangle and an orange circle:

```lua
rect = Aloha.Rectangle:New(40, 40, 80, 80, Aloha.Color:New(0, 121, 241))
circle = Aloha.Circle:New(window.width / 2, window.height / 2, 60, Aloha.Color:New(255, 161, 0))
```

Finally, on each frame, you can change the position of your objects and control what to render and in which order:

```lua
rect:SetX(newX)
rect:SetY(newY)

rect:Draw()
circle:Draw()
```

You can reference a short script that demonstrates **Aloha’s real-time rendering**, **delta-time logic**, and **cross-platform Lua control** — all in under 50 lines of code — inside romfs/example.lua.

## 📁 Project Structure

```
src/                    → C++ core source
romfs/lua/Aloha/        → Core Lua modules (Color, Window, Shapes, etc.)
romfs/lua/main.lua      → Demo script
CMakeLists.txt          → Build configuration
```


## 🔮 Future Plans

* Additional backends
* Support for the Wii U
* Audio module for both PC and 3DS
* Lua-based UI framework
* Network and file utilities


## 📜 License

Released under the **MIT License**.
You’re free to use, modify, and distribute Aloha in your own projects.


## ❤️ Credits

Developed with love using **C++**, **Lua**, and a lot of **Aloha spirit** 🌺
Powered by **Raylib** and **Citro2D**.
