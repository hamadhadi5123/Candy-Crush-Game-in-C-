# 🍬 Candy Crush - C++ & SFML Pro Edition (PF Project)

An interactive, feature-rich **Candy Crush** clone built with **C++** and **SFML 2.6.1**, developed as a Programming Fundamentals (PF) semester project.

![Candy Crush Gameplay](bg_image.jpg)

---

## 🌟 Features

- **🎮 Dual Control Schemes:**
  - **Mouse Controls:** Click any candy to select, click an adjacent candy to swap.
  - **Keyboard Controls:** Arrow keys to navigate the glowing cursor frame, `Enter` to select and swap.
- **✨ Dynamic Match-3 & Cascades:**
  - Match 3 candies (+10 pts)
  - Match 4 candies (+20 pts bonus combo)
  - Continuous cascading chain reactions
- **🔊 SFML Audio:**
  - Crisp audio effects when candies crush and combo matches occur.
- **⏱️ Timed Mode & High Scores:**
  - 60-second challenge with smooth visual timer progress bar.
  - Persistent high score saved to `high.txt`.
- **📋 Game States:**
  - **Main Menu**: Start Game, How to Play instructions, Exit.
  - **How to Play**: Two-column layout with detailed rules and scoring guide.
  - **Pause Menu (`P` / `ESC`)**: Resume, Restart (`R`), or return to Menu.
  - **Game Over Screen**: Shows final score, target goal status, and instant Play Again.
- **🌐 Web Version Included:**
  - Standalone HTML5 Canvas / JavaScript port (`index.html`) ready to play in any modern browser.

---

## 🚀 How to Play / Run

### Option 1: Direct Execution (Windows)
Double-click `run_game.bat` or run in terminal:
```powershell
.\candy_crush.exe
```

### Option 2: Run in VS Code
1. Open this repository in Visual Studio Code.
2. Press **F5** or click the top-right **Run / Play** button.

### Option 3: Compile from Source (MinGW 64-bit + SFML)
Run the fast compiler batch script:
```cmd
compile.bat
```
Or manually run:
```cmd
g++ -include pch.h candy_crush.cpp -o candy_crush.exe -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
```

---

## 📂 Project Structure

```
PF Project/
├── candy_crush.cpp      # Main C++ SFML Game Source Code
├── pch.h                # Precompiled Header for fast compilation
├── compile.bat          # Fast compilation script
├── run_game.bat         # One-click launcher
├── index.html           # Web / Browser version of the game
├── server.js            # Node.js local preview server
├── .vscode/             # VS Code tasks and launch configurations
│   ├── tasks.json
│   ├── launch.json
│   └── c_cpp_properties.json
├── *.png / *.jpg        # Candy gems, background, and UI sprites
├── *.ttf / *.otf        # Fonts (Arial, Big Marker, Skeina)
├── *.wav                # Sound effects (match, combo, etc.)
└── *.dll                # SFML runtime DLLs for Windows
```

---

## 🎮 Controls Summary

| Action | Mouse | Keyboard |
|---|---|---|
| Select Candy | Left Click | Arrow Keys + Enter |
| Swap Candy | Click Adjacent Candy | Enter on Adjacent Candy |
| Pause / Resume | Click Pause Button | `P` or `ESC` |
| Quick Restart | Click Restart Button | `R` |
| Menu Navigation | Click Buttons | `ESC` |

---

## 👥 Author
- **Muhammad Hamad Asghar**
- Programming Fundamentals (PF) Project
