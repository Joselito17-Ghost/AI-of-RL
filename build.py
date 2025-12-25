
import subprocess, sys

SRC = [
    "src/main.cpp",
    "external/imgui/imgui.cpp",
    "external/imgui/imgui_draw.cpp",
    "external/imgui/imgui_tables.cpp",
    "external/imgui/imgui_widgets.cpp",
    "external/imgui/backends/imgui_impl_sdl3.cpp",
    "external/imgui/backends/imgui_impl_sdlrenderer3.cpp"
]

CMD = ["g++", "-std=c++20", "-O2"] + SRC + [
    "-Iexternal/imgui",
    "-Iexternal/imgui/backends",
    "-lSDL3",
    "-o", "ai_env"
]

print(" ".join(CMD))
sys.exit(subprocess.call(CMD))
