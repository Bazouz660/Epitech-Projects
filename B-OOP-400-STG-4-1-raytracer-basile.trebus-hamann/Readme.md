<p align="center">
  <a href="" rel="noopener">
 <img width=200px height=200px src="https://i.kym-cdn.com/photos/images/original/001/405/615/44b.png" alt="Raytracer logo"></a>
</p>

<h3 align="center">Raytracer</h3>

<div align="center">

[![Status](https://img.shields.io/badge/status-active-success.svg)]()
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/kylelobo/The-Documentation-Compendium.svg)](https://github.com/kylelobo/The-Documentation-Compendium/pulls)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

</div>

---

<p align="center"> Ray tracing is a technique used to generate realistic digital images by simulating the inverse path of light.<br>
The goal of this project is to create a program able to generate an image from a file describing the scene.
    <br>
</p>

## 📝 Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)
- [Built Using](#built_using)
- [Contributing](../CONTRIBUTING.md)
- [Authors](#authors)
- [Acknowledgments](#acknowledgement)

## 🧐 About <a name = "about"></a>

Epitech Tek2 project in the Oriented Object Module
Program taking a configuration scene file containing lights, objects and a camera as a parameter and generates an output image once we computed shadows and reflections.

## 🏁 Getting Started <a name = "getting_started"></a>

Copy the url of this repository and clone it :
![](https://github.com/444sofiane/ReadmeRessources/blob/master/copy_repo_url.gif)

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

[Install git]()
- For Linux and MacOS:
Pre-installed on the dump

- For Windows:
Follow this guide : https://git-scm.com/book/fr/v2/D%C3%A9marrage-rapide-Installation-de-Git

[Compilator for c++]()
- For Linux and MacOS:
Use g++ : pre-installed on the dump

- For Windows :
Use gnu : https://gcc.gnu.org/install/binaries.html

[Libconfig]()
- For Linux and MacOS :
Follow this guide : https://zoomadmin.com/HowToInstall/UbuntuPackage/libconfig-dev

- For Windows:
Follow this guide : https://gnuwin32.sourceforge.net/packages/libconfig.htm

### Running <a name = "running">

- Create a scene .yml file at the root of the cloned repository

- Add lights (points or directionnal), shapes (sphere, plans, triangle, objects), camera and render methods (not recommended to change) here's an example :

![](https://github.com/444sofiane/ReadmeRessources/blob/master/scene.png)

- Compile using the build.sh script :
```
./build.sh
```

- Execute the raytracer binary using the scene.yml file created :
```
./raytracer scene.yml
```

## 🔧 Running the tests <a name = "tests"></a>

There's no need of automatic tests for this project 😊

## 🎈 Usage <a name="usage"></a>

```
USAGE: ./raytracer <SCENE_FILE>
  SCENE_FILE: scene configuration
```

## ⛏️ Built Using <a name = "built_using"></a>

- [Libconfig](http://hyperrealm.github.io/libconfig/) - Lib used for parsing
- [CMakeLists](https://cmake.org/) - Building tool

## ✍️ Authors <a name = "authors"></a>

- [@ClementLeRigolo](https://github.com/ClementLeRigolo), [@444sofiane](https://github.com/444sofiane) - parsing and doc
- [@Bazouz660](https://github.com/Bazouz660) - architecture, obj and lighting computing
- [@Ziiibz](https://github.com/Ziiibz) - primitive shapes

## 🎉 Acknowledgements <a name = "acknowledgement"></a>

- [Documentation to render a triangle shape](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution.html)
- [Documentation for aspect ratio](https://www.gamedev.net/blogs/entry/2260865-shadows-and-point-lights/)
- [Readme template](https://marketplace.visualstudio.com/items?itemName=thomascsd.vscode-readme-pattern)
