# Aloha

## Graphics backend structure

The graphics resource declarations, vertex-layout description, and ImGui layer interface are independent of OpenGL/GLFW types. Platform/API-specific implementations live under `src/platform`; currently CMake includes only `src/platform/pc/opengl`. There is no runtime backend switch. Configure the supported target with `cmake --preset pc`; target choices are exposed as `ALOHA_PLATFORM` and `ALOHA_GRAPHICS_API`.

Local configure/build presets belong in the ignored `CMakeUserPresets.json`; the file is machine-specific and is intentionally not shared. On Windows, the build stages the executable and assets into `dist/<platform>`. On Wii U, staging installs the generated RPX/WUHB files and assets to `dist/wiiu`. Visual Studio's debugger launches the staged PC executable with the staged directory as its working directory. The `wiiu` user preset selects `WIIU/GX2` (the only graphics API allowed for Wii U), but CMake rejects the target until its platform and GX2 backend sources exist. To add a backend, provide implementations of the resource interfaces in its own platform/API directory and add them to the corresponding CMake source list. Public headers should remain free of native graphics handles, while backend-specific details stay in private implementation types.

## Profiling

Tracy profiling is enabled by default on the PC target. Aloha links Tracy's client library, records named CPU zones for the frame loop, test updates, UI, resource loading, and draw submission, and records GPU zones for OpenGL clears, draws, and ImGui rendering. Configure with `-DALOHA_ENABLE_TRACY=OFF` to skip fetching/building Tracy and compile Aloha without instrumentation; the `TracyProfiler` target is only available when this option is enabled.

The client is not a separate executable: it is compiled into Aloha and sends profiling data while Aloha runs. Its static library is built at `build/pc/_deps/tracy-build/Debug/TracyClient.lib`; the running client is `build/pc/Debug/Aloha.exe` (also staged at `dist/pc/Aloha.exe`). Build it explicitly with `cmake --build build/pc --config Debug --target TracyClient`.

The separate Tracy Profiler application is the GUI used to connect to Aloha and inspect captures. Build it with the root project's `TracyProfiler` target:

```powershell
cmake --build build/pc --config Debug --target TracyProfiler
```

The GUI executable is `build/pc/tracy-profiler/Release/tracy-profiler.exe`. Run Aloha and the profiler; the profiler can discover the running client or connect to it through its connection dialog. Tracy's client and profiler are build dependencies/tools, not part of Aloha's staged installation.