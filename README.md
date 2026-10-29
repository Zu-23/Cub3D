# Cub3D

A C raycasting project from the 42 curriculum. It renders a first-person view of a 2D map using textured walls, player movement, and MiniLibX.

## Features

- `.cub` configuration parsing with directional wall textures and floor/ceiling colors.
- Raycasting and textured wall rendering.
- Forward/backward movement, strafing, rotation, and wall collision checks.
- Keyboard press/release handling and a continuous rendering loop.
- An example map, [Amogus.cub](Amogus.cub), and XPM textures.

## Requirements

The active linker command targets **macOS**, using MiniLibX, OpenGL, and AppKit. A compatible MiniLibX installation, C compiler, Make, and `ar` are required. MiniLibX is not bundled. Although the Makefile defines Linux/X11 linker flags, the final link command uses the macOS flags.

## Checkout and build limitations

The tracked header is named `Cub3d.h`, but the Makefile prerequisites refer to `cub3d.h`. This mismatch prevents a normal build on a case-sensitive filesystem. The default build also relies on a nested Libft archive whose build rules need checking. These are existing source/build issues; this README does not change them.

After resolving the header-name mismatch and ensuring MiniLibX and the nested library are available, the intended commands from the repository root are:

```sh
make -C lib_gnl/lib
make
./cub3D Amogus.cub
```

Run from the repository root so the map's relative texture paths resolve. This macOS graphics build was not executed in the Linux documentation environment. The Makefile provides `clean`, `fclean`, and `re` targets.

## Controls

| Key | Action |
| --- | --- |
| W / S | Move forward / backward |
| A / D | Strafe left / right |
| Left / right arrow | Rotate the view |
| Escape or window close | Exit |

## Map format

The example defines `NO`, `SO`, `WE`, and `EA` texture paths, plus `F` and `C` RGB colors. Its grid uses `1` for walls, `0` for open space, and an `N`, `S`, `E`, or `W` marker for the player's starting orientation.

## Concepts practiced

Raycasting, trigonometry, projection, texture coordinates, map parsing, collision detection, event loops, and C graphics programming.
