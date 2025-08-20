# cub3D

A small raycasting engine in the style of *Wolfenstein 3D*, written in C with
[MiniLibX](https://github.com/42Paris/minilibx-linux) as part of the 42 curriculum.

It reads a `.cub` scene file and renders a first-person, textured 3D view of
the maze that you can walk around in.

## Demo

▶️ [Watch the demo (docs/demo.mp4)](docs/demo.mp4)

## Building

Requirements:

- `cc` (gcc or clang) and `make`
- **Linux:** X11 and Xext development headers, e.g.
  `sudo apt install libx11-dev libxext-dev zlib1g-dev`
- **macOS:** the bundled `minilibx_mac` (OpenGL + AppKit)

```sh
make        # builds libft, MiniLibX and ./cub3d
make clean  # removes object files
make fclean # removes object files and the binary
make re     # full rebuild
```

The Makefile targets Linux by default. To build on macOS, switch the commented
`MLX_DIR` / `MLX` lines in the [Makefile](Makefile) and the `mlx.h` include in
[cub3d.h](cub3d.h).

## Usage

```sh
./cub3d maps/valid.cub
```

### Controls

| Key           | Action              |
| ------------- | ------------------- |
| `W` / `S`     | Move forward / back |
| `A` / `D`     | Strafe left / right |
| `←` / `→`     | Turn left / right   |
| `ESC`         | Quit                |
| Window cross  | Quit                |

## The `.cub` file format

```
NO tex/Bark.xpm
SO tex/Glass.xpm
WE tex/Grass.xpm
EA tex/Stone.xpm

F 220,100,0
C 225,30,0

        1111111111
        1000000001
11111111100N000001
10000000000000001
11111111111111111
```

- **Elements** (`NO`, `SO`, `WE`, `EA`, `F`, `C`) can appear in any order and
  may be separated by empty lines. Each must appear exactly once.
  - `NO/SO/WE/EA <path>` - XPM texture for the wall facing that direction.
  - `F/C R,G,B` - floor / ceiling colour, each value in `0-255`.
- **The map** must come last and contain only:
  - `1` wall, `0` floor, ` ` (space) empty/void
  - exactly one of `N`, `S`, `E`, `W` - the player's start position and facing.
- The map must be fully enclosed by walls: no floor or player cell may touch a
  space or the edge of the map. Empty lines inside the map are not allowed.

Any invalid scene makes the program exit with an error message.

Sample scenes, valid and deliberately broken, live in [maps/](maps/).

## How it works

### Parsing (`parsing/`)

1. Check the argument count, the `.cub` extension and that the file opens.
2. Read the whole file into an array of lines.
3. Parse the six elements, counting each identifier to catch duplicates or
   missing entries.
4. Locate the map block, reject empty lines inside it and copy it out.
5. Validate the map: allowed characters, a single player, closed borders and
   enclosed spaces/floors.

### Execution (`exec/`)

- **Raycasting** ([rays.c](exec/rays.c)) - for every screen column a ray is cast
  from the player using the DDA algorithm until it hits a wall, giving the
  perpendicular wall distance and the side that was hit.
- **Drawing** ([draw_walls.c](exec/draw_walls.c)) - the wall slice height is
  derived from that distance and the matching N/S/E/W texture is sampled per
  pixel; floor and ceiling are filled with the configured colours.
- **Movement** ([movement.c](exec/movement.c), [moveplayer.c](exec/moveplayer.c)) -
  frame-time based movement and rotation with wall collision.
- **Hooks** ([hooks.c](exec/hooks.c)) - key press/release state, window close and
  the render loop.

## Project layout

```
.
├── main.c, init.c, free.c   entry point, setup, cleanup
├── cub3d.h                  shared types and prototypes
├── parsing/                 .cub file and map validation
├── exec/                    raycasting, rendering, input, movement
├── libft/, get_next_line/   helper libraries
├── minilibx-linux/, minilibx_mac/
├── maps/                    sample scenes
└── tex/                     wall textures (.xpm)
```

## Authors

- mnazar - 42 Abu Dhabi
