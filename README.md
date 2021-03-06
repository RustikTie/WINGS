## Video Game Development | Assignment 3 | WINGS

Simple platformer game for the first assignment of Game Development class at UPC. Using the SDL and XML libraries. Loading game config, player position and all map data(tiles, background, parallax, colliders) from XML documents. Map created with Tiled, enemies position and type load from Tiled.  

Git: https://github.com/RustikTie/WINGS

## Installation

Simply download a release, unzip the file and execute the WINGS.exe. 
The game is capped at 30FPS by default, you can edit the frame cap by accessing the config.xml file and changing its value, for an uncapped experience set it to 0. Although, VSYNC is on and will cap the game at your monitor's refresh rate. 

## Usage

- Move the player using the WAD keys and SPACEBAR (W to jump, A/D as Left/Right movement and SPACEBAR to glide)
- Press F1 to begin from the first level starting position
- Press F2 begin from the starting position of the current level
- Press F5 to save last saved status
- Press F6 to load current status
- Press F8 to show UI colliders
- Press F9 to show colliders
- Press F10 to enable/disable god mode
- Press F11 to enable/disable frame cap

## Contributing
- Fork it!
- Create your feature branch: git checkout -b my-new-feature
- Commit your changes: git commit -am 'Add some feature'
- Push to the branch: git push origin my-new-feature
- Submit a pull request :D

## Credits

Jump SFX = https://freesound.org/people/RoseTheFl0wer/sounds/442715/
Walk SFX = https://opengameart.org/content/512-sound-effects-8-bit-style
Death SFX = https://opengameart.org/content/512-sound-effects-8-bit-style
Glide SFX = https://opengameart.org/content/512-sound-effects-8-bit-style
Coin SFX = https://opengameart.org/content/512-sound-effects-8-bit-style
Menu Music = https://opengameart.org/content/chill-bgm
BGM = https://opengameart.org/content/games-a-bgm-track
Tileset & Player SPRITE: https://opengameart.org/content/platformer-art-complete-pack-often-updated
GUI = https://opengameart.org/content/free-game-gui
Background: https://www.gameart2d.com/free-platformer-game-tileset.html
Beetle SPRITE = https://www.vectorstock.com/royalty-free-vector/stag-beetle-enemy-game-sprites-vector-21861431
Mushroom SPRITE = https://www.vectorstock.com/royalty-free-vector/mushroom-enemy-game-sprites-vector-21861393

## History

### Clara 

- Collisions
- SFX, Music
- Spritesheets
- Godmode w/ enemies
- Entity System UML
- Blocker Colliders
- Brofiler
- Frame Cap
- Bugfixing

### Ivan

- Entity system
- Pathfinding
- UI System
- Enemies
- Collisions
- Save and load w/ enemies
- Bugfixing
- Gamebalancing

## License

MIT License

Copyright (c) 2018 Ivan Drofiak, Clara Ratera

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the �Software�), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

### Developed by :
Ivan Drofiak: https://github.com/FurryGhoul
Clara Ratera: https://github.com/RustikTie