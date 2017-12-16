## Video Game Development | Assignment 1 | Pumpkin Knight

Simple platformer game for the first assignment of Game Development class at UPC. Using the SDL and XML libraries. Loading game config, player position and all map data(tiles, background, parallax, colliders) from XML documents. Map created with Tiled, enemies position and type load from Tiled.  

Git: https://github.com/RustikTie/Pumpkin-Knight
Git Pages: https://rustiktie.github.io/Pumpkin-Knight/

## Installation

Simply download a release, unzip the file and execute the Pumpkin_Knight.exe. 
The game is capped at 30FPS by default, you can edit the frame cap by accessing the config.xml file and changing its value, for an uncapped experience set it to 0. Although, VSYNC is on and will cap the game at your monitor's refresh rate. 

## Usage

- Move the player using the WAD keys (W to jump/double jump, press W twice to double jump, A/D as Left/Right movement)
- Press F1 to begin from the first level starting position
- Press F2 begin from the starting position of the current level
- Press F5 to load last saved status
- Press F6 to save current status
- Press F9 to show colliders
- Press F10 to enable/disable god mode
- Press F11 to enable/disable frame cap
- Quit hitting Escape

## Contributing
- Fork it!
- Create your feature branch: git checkout -b my-new-feature
- Commit your changes: git commit -am 'Add some feature'
- Push to the branch: git push origin my-new-feature
- Submit a pull request :D

## History
- Added entity system
- Added enemies
- Added god mode
- Implemented Brofiler
- Implemented frame cap
- Normalized movement

## Credits

### Skeleton Sprite by: 
Jesse M / Twitter- @Jsf23Art / https://jesse-m.itch.io/skeleton-pack
Modified to sport a pumpkin head and created a quick jump animation. 

### Wolf Enemy Sprite by:
William.Thompsonj / https://opengameart.org/content/lpc-wolf-animation

### Bat Enemy Sprite by: 
MoikMellah / https://opengameart.org/content/bat-32x32

### Candy Sprites by:
lumimae / http://thecandyjam.com/ / https://opengameart.org/content/candy-pack-1

### GUI assets by:
https://www.gameart2d.com/free-fantasy-game-gui.html

### Background images and parallax from: 
http://www.gameart2d.com/free-graveyard-platformer-tileset.html
Separated the background in different layers and modified the image tone to fit the mood. 

### Tileset by: 
KIIRA / https://opengameart.org/content/metroidvania-tileset-v2

### Music by: 
Title: This Is Halloween 8-bit / https://www.youtube.com/watch?v=6_wfIDixlHE

### Intro music by:
Title: Spooky Scary Skeletons 8-bit / https://www.youtube.com/watch?v=IHI6bfFIUCk

### Walk FX by:
Finnolia Productions Inc / https://www.soundeffectsplus.com/product/footsteps-walking-on-road-01/
 
### Developed by :
Ivan Drofiak: https://github.com/FurryGhoul
Clara Ratera: https://github.com/RustikTie
