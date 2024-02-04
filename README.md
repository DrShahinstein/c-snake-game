## Snake Game in C using Raylib

This has been the first project of mine where I used C and learned a lot.

## Keys

| Key              | Func          |
| ---------------- | ------------- |
| <kbd>Space</kbd> | Pause game    |
| <kbd>Enter</kbd> | Unpause game  |
| <kbd>Enter</kbd> | Restart game  |

## Showcase

https://github.com/DrShahinstein/c-snake-game/assets/81323808/005fed72-1ef5-4db2-8dbf-11a335bdc867

## Build

See [releases](https://github.com/DrShahinstein/c-snake-game/releases/tag/LTS) to get executable binaries right away.
If you want to build from source, [raylib](https://github.com/raysan5/raylib) must be installed and maintained on your machine.

### Linux

Clone the repository and simply run `make` tool to build snake game in Linux.

```
$ git clone https://github.com/DrShahinstein/c-snake-game
$ cd c-snake-game/
$ make
$ make run
```

### Windows

Make sure you have [w64devkit](https://github.com/skeeto/w64devkit) installed on your machine.
Using w64devkit terminal, you can follow the exact same instruction with Linux.

```
$ git clone https://github.com/DrShahinstein/c-snake-game
$ cd c-snake-game/
$ make
$ make run
```

### Troubleshooting

In Windows, if you ever face an issue like raylib window not being initialized just as in here:

![problem](https://github.com/DrShahinstein/c-snake-game/assets/81323808/84f0ca09-dbce-4713-b267-97640971e17f)

You can change the compatibility of the executable to run on Windows 8 or anything else if necessarry like this:

![windowscompatibility](https://github.com/DrShahinstein/c-snake-game/assets/81323808/7e91a2c9-d8ed-4589-a6ef-1c5e149a7cf3)
