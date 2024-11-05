# Kai Procedural Generation (KaiProc / KPG)

Exploring various proc gen tools.

Goal of having a nice 2D dungeon/terrain generator for a top down tile based game.

https://wiki.libsdl.org/SDL2/MigrationGuide#if-your-game-just-wants-to-get-fully-rendered-frames-to-the-screen
https://gamedev.stackexchange.com/questions/157604/how-to-get-access-to-framebuffer-as-a-uint32-t-in-sdl2

1. make component
2. make way to just have framebuffer to show perlin noise
3. play around with fdm
5. make some basic imgui debug ui
4. port tile editor from worldedit

## Summary

## Getting Started

**Building**

```bash
git clone <url>
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
```

**Running**
```bash
./kaiproc
```
