# Aloha

Aloha is a small C++20 rendering playground for experimenting with graphics
programming. It currently runs on PC with OpenGL and provides a simple ImGui
menu for switching between rendering examples.

## Examples

- **Clear Color** — adjust the framebuffer clear color.
- **Boxes** — move a camera through textured cubes.
- **Phong** — inspect textured cubes with Phong lighting and adjust the light
  position.

## Build

### Requirements

- CMake 3.31 or newer
- A C++20 compiler
- Git, for fetching CMake dependencies on the first configure
- An OpenGL-capable graphics driver

On Linux, install the development packages required by GLFW for your display
server. For Ubuntu: `libwayland-dev`, `libxkbcommon-dev`, and `xorg-dev`.

Configure and build a Debug version:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

The project stages the executable and runtime assets in `dist/pc`. Run Aloha
from that directory so its relative `assets/` paths resolve correctly.

The first configure fetches GLFW, GLM, Dear ImGui, and Tracy with CMake
FetchContent, so it requires network access. Subsequent builds reuse those
sources in the build directory.

## Controls

- Select an example from the **Tests** menu.
- In **Boxes** and **Phong**, use **W/A/S/D** to move the camera.
- Press **Enter** to capture the mouse for camera look; press **Backspace** to
  release it.
- Press **Escape** or use the **Close** button to exit.

## Graphics backends

The current buildable configuration is PC/OpenGL. Graphics resource interfaces
are kept separate from the PC/OpenGL implementation so additional platform and
graphics backends can be added without exposing native graphics handles in
shared headers. Wii U/GX2 is not implemented yet.

## Profiling

PC builds enable Tracy instrumentation by default. Tracy's client is linked
into Aloha and records CPU zones across the application and rendering examples,
as well as OpenGL GPU zones for clears, draws, and ImGui rendering. To disable
instrumentation, configure with:

```sh
cmake -S . -B build -DALOHA_ENABLE_TRACY=OFF
```

The Tracy Profiler GUI is a separate application and is not built or staged by
this project. Run it alongside Aloha to inspect live profiling data.

## License

Aloha is distributed under the GNU General Public License v3.0. See
[LICENSE](LICENSE) for the full text.
