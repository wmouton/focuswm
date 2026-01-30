# FocusWM

A minimalist, ultra-lightweight tiling window manager for X11, written in C. **FocusWM** is designed for efficiency, speed, and a distraction-free workflow, leveraging Xinerama for multi-monitor support.

## ⚡ Features

* **Ultra-Lightweight:** Compiled with `tcc`, the binary is incredibly small and fast.
* **Built-in Multi-Monitor Support:** Seamlessly switch focus or move windows between monitors using Xinerama.
* **Macro-Driven Configuration:** Keybindings are handled via a central macro table for easy modification.
* **Automatic Fullscreen Tiling:** Windows are automatically resized to fill the current monitor's dimensions.
* **Integrated Shell Commands:** Direct bindings for `rofi`, `brightnessctl`, `nmcli`, and custom dotfile scripts.

## ⌨️ Default Keybindings

The **Mod Key** is set to `Alt` (Mod1).

| Key Combo | Action |
| --- | --- |
| `Alt + ;` | Launch Terminal (`st`) |
| `Alt + f` | Launch File Manager (`lf` in `st`) |
| `Alt + b` | Launch Browser (`Vivaldi`) |
| `Alt + d` | Launch Command Launcher (`Rofi`) |
| `Alt + u` | Cycle Focus / Circulate Windows |
| `Alt + i` | Switch focus to next monitor |
| `Alt + o` | Move current window to next monitor |
| `Alt + '` | Kill current window |
| `Super + [` | Decrease Brightness |
| `Super + ]` | Increase Brightness |
| `Alt + Shift + b` | Launch `Librewolf` |
| `Alt + Esc` | Exit FocusWM |

## 🛠 Installation

### Prerequisites

You will need the X11 and Xinerama development headers installed on your system:

* **Arch Linux:** `sudo pacman -S libx11 libxinerama tcc`
* **Debian/Ubuntu:** `sudo apt install libx11-dev libxinerama-dev tcc`

### Build and Install

Clone the repository and run the provided installation script:

```bash
git clone https://github.com/yourusername/focuswm.git
cd focuswm
chmod +x install.sh
./install.sh

```

## ⚙️ Configuration

Since FocusWM is a "header-less" C project, configuration is done by editing `focuswm.c`.

1. Open `focuswm.c`.
2. Locate the `TBL(x)` macro.
3. Add or modify entries following the format: `x("key_name", action)`.
4. Re-run the installation script to apply changes.

## 🚀 Starting FocusWM

Add the following to your `.xinitrc`:

```bash
exec focuswm

```

---

### A Note on Custom Scripts

FocusWM expects certain scripts to exist in your `~/dotfiles/` directory (e.g., for Rofi menus and power management). If these scripts are missing, those specific keybindings will not trigger any action. You can update these paths in `focuswm.c` to point to your preferred utilities.

