# The Maze Project!

This is the first time I'm working with SDL2 with the purpose of making a 3D maze game.<br>
I encountered difficulties running it on Linux, so unfortunately, I won't be able to provide instructions for Linux users.

## How to install (Windows only)

If you want to install this game you must have a C compiler installed on your device.

If it's not already installed, you can easily set it up by following the installation process provided here.

```
https://code.visualstudio.com/docs/cpp/config-mingw
```

Then, you will need to clone the repository and execute the 'make' command. If you don't have 'make' installed on your device, you can simply open the Makefile, copy the GCC line, run it in the console, and then run the executable file.

Use this command to clone the repository

```
git clone https://github.com/Diego-Bonora/Maze-project.git
```

If you dont have GitHub installed you can do it here.

```
https://git-scm.com/downloads
```

## How to play

This is a simple maze game. The controls are 'w', 'a', 's', 'd', or arrow keys. The objective of the game is to reach the end. The starting point is indicated by green walls, and the endpoint is marked by red walls.

When you reach the end of the map, the game will stop, and a giant win message will appear. The only action available at this point is to close the game and open it again to restart.

You can modify the layout of the map by changing the matrix located at the beginning of the ['map.c'](map.c) file. Further instructions about the layout options can be found there.

## Authors

### Diego Bonora

['LinkedIn'](https://www.linkedin.com/in/diego-bonora/) | ['GitHub'](https://github.com/Diego-Bonora)
