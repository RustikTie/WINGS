# Team

![Pic](website%20Images/both.png)

### Ivan Drofiak

[Git](https://github.com/FurryGhoul)

- Entity system
- Player
- Enemies
- Map Design
- Ui system
- Save and Load
- Main Menu

### Clara R. Gracia

[Git](https://github.com/RustikTie)



# Subsystems

- Main Menu with Start, Continue, Options, Credit and Quit working elements.
- Player data, important game data and map information is loaded from an XML file
- FPS capped by default at 30FPS, can be uncapped in-game and FPS cap can be edited from the config.xml file
- Maps created on tiled, contain collider information, loaded through their XML file 
- Two types of enemies, ground and air, pathfind their way to the player 
- Game music and sound FX can be lowered or increased through the Options menu
- GUI is managed through an GUIManager system which creates and updates all UI during runtime.
- Enemies and interactive items(Candy) are managed through an EntityManager system which creates and updates them. 

# The Game

- Move the player using the WAD keys and SPACEBAR (W to jump press, SPACEBAR to glide, A/D as Left/Right movement)
- Press F1 to begin from the first level starting position
- Press F2 begin from the starting position of the current level
- Press F5 to save current status
- Press F6 to load last saved status
- Press F8 to show UI debug
- Press F9 to show colliders and pathfinding
- Press F10 to enable/disable god mode
- Press F11 to enable/disable frame cap

[REPO](https://github.com/RustikTie/WINGS)

[LATEST RELEASE](https://github.com/RustikTie/Pumpkin-Knight/releases/tag/v2.0)

# License
MIT License

Copyright (c) 2018 Clara Ratera, Ivan Drofiak

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

