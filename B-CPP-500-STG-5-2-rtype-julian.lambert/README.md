<p align="center">
  <a href="" rel="noopener">
 <img width=200px height=200px src="https://fs-prod-cdn.nintendo-europe.com/media/images/10_share_images/games_15/virtual_console_wii_u_7/H2x1_WiiUVC_RType.jpg" alt="Raytracer logo"></a>
</p>

<h3 align="center">R-Type</h3>

<div align="center">

[![Status](https://img.shields.io/badge/status-active-success.svg)]()
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/kylelobo/The-Documentation-Compendium.svg)](https://github.com/kylelobo/The-Documentation-Compendium/pulls)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

</div>

---

# **R-Type**

![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black) ![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
 ![GitHub Actions](https://img.shields.io/badge/github%20actions-%232671E5.svg?style=for-the-badge&logo=githubactions&logoColor=white) 

***

## **Table of Contents**

- [**Table of Contents**](#table-of-contents)
- [**Introduction**](#introduction)
- [**The Game**](#the-game)
- [**How to play ?**](#how-to-play-)
- [**For developers**](#for-developers)
- [**Authors**](#authors)

***

## **Introduction**

The goal of the Epitech R-Type project is to implement a server and a graphical client for a multiplayer version of the game named R-Type, using an engine that we created.

The project is composed of two parts: the server and the client, both in C++.

### **Supported Platforms**

The R-Type project is supported on Linux AND Windows !

***

## **The Game**

In the vast expanse of the cosmos, where the boundaries between reality and the unknown blur, the R-Type universe unfolds its gripping tale. Set against the backdrop of a galactic conflict, R-Type thrusts players into the role of a courageous pilot navigating a futuristic spacecraft known as the R-9A Arrowhead. As humanity faces an existential threat from the insidious Bydo Empire, a malevolent force originating from an alternate dimension, players embark on a perilous journey through space, battling swarms of biomechanical adversaries. Armed with the cutting-edge technology of the R-9A and fueled by the spirit of relentless determination, players delve into the heart of the cosmic maelstrom to save their home world. The R-Type series, renowned for its challenging gameplay and iconic side-scrolling shoot 'em up mechanics, weaves an immersive narrative of survival, sacrifice, and the eternal struggle between light and darkness in the far reaches of the universe.

***

## **How to play ?**

### **Launch the game**

Once you have downloaded the latest release [here](https://github.com/EpitechPromo2026/B-CPP-500-STG-5-2-rtype-julian.lambert/releases), you can start your R-Type gaming experience.

The archive contains both binaries and the `asset/` folder. Keep them together:
the game locates its assets relative to the executable, so it can be started
from anywhere, double click included.

1. Start `r-type_server`. A console opens and it listens on the port set in
   `config.ini` (`4040` by default).
2. Start `r-type_client`, type the server IP and port in the menu, then click
   **Play**. Both fields are pre-filled with `127.0.0.1` / `4040` for a game on
   the same machine.

Up to 5 players can share the same server.

### **Controls**

-   **Movement:**
    
    -   **Arrow Keys:** Use the arrow keys (up, down, left, right) to navigate your ship through the game environment.
-   **Shooting:**
    
    -   **Spacebar:** Press the spacebar to fire projectiles and attack enemies. Use this to defend yourself and destroy obstacles in your path.
-   **Display:**

    -   **F11:** Toggle fullscreen.

### **Server console**

The server reads commands on its standard input:

| Command | Effect                      |
|---------|-----------------------------|
| `help`  | List the available commands |
| `stop`  | Stop the server cleanly     |

`Ctrl+C`, or closing the console window, also shuts it down cleanly.

***

## **For developers**

### **Build from source**

The only dependency is SFML 2.6, and CMake downloads and builds it through
`FetchContent`: nothing to install by hand besides a compiler and CMake 3.16+.

**Windows** (MinGW-w64, what the CI uses):

```sh
cmake -G "MinGW Makefiles" -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

Ninja works too and is noticeably faster:

```sh
cmake -G Ninja -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

**Linux:**

```sh
sudo apt install cmake g++ libxrandr-dev libxcursor-dev libxi-dev libudev-dev                  libfreetype-dev libflac-dev libvorbis-dev libgl1-mesa-dev
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

The first configure clones SFML, so it takes a couple of minutes; later builds
reuse it.

Both binaries are copied to the repository root once built:

```sh
./r-type_server      # then, in another terminal
./r-type_client
```

### **Packaging**

```sh
cd build && cpack
```

Produces `build/package/r-type-<version>.zip` on Windows and `.tar.gz` on
Linux, containing the binaries, `asset/` and `config.ini`.

### **Configuration**

`config.ini` (JSON despite the extension) sits next to the binaries:

| Key              | Meaning                        | Default |
|------------------|--------------------------------|---------|
| `port`           | UDP port the server listens on | `4040`  |
| `net_tickrate`   | State broadcasts per second    | `30`    |
| `logic_tickrate` | Simulation steps per second    | `60`    |

A missing or invalid file is replaced by the defaults and rewritten.

### **Documentation**

The code documentation is available [here](https://github.com/EpitechPromo2026/B-CPP-500-STG-5-2-rtype-julian.lambert/wiki). <br>

***

## **Authors**

<table>
    <tbody>
        <tr>
            <td align="center"><a href="https://github.com/Bazouz660"><img src="https://avatars.githubusercontent.com/u/91666446?v=4" width="100px;" alt="Bazouz660"/><br/><sub><b>Basile Trebus-Hamann</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/DefinitelyNotMallow"><img src="https://avatars.githubusercontent.com/u/73607796?v=4" width="100px;" alt="DefinitelyNotMallow"/><br/><sub><b>Julian Lambert</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/ClementLeRigolo"><img src="https://avatars.githubusercontent.com/u/91666514?v=4" width="100px;" alt="ClementLeRigolo"/><br/><sub><b>Clément Thomas</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/Ziiibz"><img src="https://avatars.githubusercontent.com/u/91550211?v=4" width="100px;" alt="Ziiibz"/><br/><sub><b>Corentin Wolff</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/Reivax4012"><img src="https://avatars.githubusercontent.com/u/91666543?v=4" width="100px;" alt="Reivax4012"/><br/><sub><b>Xavier Huber</b></sub></a><br/></td>
            <td align="center"><a href="https://github.com/444sofiane"><img src="https://avatars.githubusercontent.com/u/91785730?v=4" width="100px;" alt="444sofiane"/><br/><sub><b>Sofiane Saou</b></sub></a><br/></td>
        </tr>
    </tbody>
</table
