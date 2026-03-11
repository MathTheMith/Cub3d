# 🧱 cub3D

> A 3D raycasting engine inspired by Wolfenstein 3D, built in C using MiniLibX.

![Language](https://img.shields.io/badge/language-C-blue)
![School](https://img.shields.io/badge/school-42-black)
![Status](https://img.shields.io/badge/status-finished-brightgreen)

---

## 📸 Preview

> *A first-person 3D maze rendered in real-time using raycasting.*

---

## 📖 Description

**cub3D** is a graphical project from École 42. The goal is to implement a basic 3D game engine from scratch using the **raycasting** technique — the same algorithm used in the original Wolfenstein 3D (1992).

The engine parses a `.cub` map file, validates it, and renders it in a first-person perspective with textured walls, a minimap, and smooth player movement.

---

## ✨ Features

- 🎮 First-person 3D rendering using raycasting (DDA algorithm)
- 🧱 Textured walls with different textures per direction (N/S/E/W)
- 🗺️ Configurable floor and ceiling colors (RGB)
- 🧭 Minimap system
- 🏃 Player movement: WASD + arrow keys + mouse rotation
- 💨 Sprint (Shift)
- 📄 `.cub` map file parser with full validation
- 🔒 Flood-fill based map validation (closed map check)
- 🧠 Custom `libft` (standard library reimplementation)

---

## 🗂️ Project Structure

```
cub3D/
├── src/
│   ├── game/          # Raycasting, drawing, movement
│   ├── init/          # Map parsing, textures, colors
│   ├── parsing/       # .cub file validation
│   └── exit/          # Error handling & memory cleanup
├── libft/             # Custom standard library
├── maps/              # Sample .cub map files
├── textures/          # Wall textures (.xpm)
├── include/cub.h      # Main header
└── Makefile
```

---

## 🚀 Getting Started

### Requirements

- Linux (Ubuntu 20.04+ recommended)
- `gcc`, `make`
- MiniLibX dependencies: `libXext`, `libX11`

```bash
sudo apt-get install libxext-dev libx11-dev libbsd-dev
```

### Build & Run

```bash
# Clone the repo
git clone https://github.com/MathTheMith/cub3D.git
cd cub3D

# Build (MiniLibX is cloned and compiled automatically)
make

# Run with a map
./cub3D maps/map.cub
```

---

## 🗺️ Map Format (.cub)

```
NO ./textures/wall_N.xpm
SO ./textures/wall_S.xpm
WE ./textures/wall_W.xpm
EA ./textures/wall_E.xpm

F 140,140,140
C 135,206,235

11111
10N01
10001
11111
```

| Symbol | Meaning              |
|--------|----------------------|
| `1`    | Wall                 |
| `0`    | Empty space          |
| `N/S/E/W` | Player spawn + direction |
| `NO/SO/WE/EA` | Texture paths   |
| `F`    | Floor color (RGB)    |
| `C`    | Ceiling color (RGB)  |

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| `W / A / S / D` | Move forward / left / backward / right |
| `← →` | Rotate view |
| `Mouse` | Rotate view (mouse mode) |
| `Shift` | Sprint |
| `ESC` | Quit |

---

## 👥 Authors

- **Mathéo Vachon** — [@mvachon](https://github.com/MathTheMith) — *École 42 Lyon*
- **tfournie** — *École 42*

---

## 📚 Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — The reference for DDA raycasting
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
