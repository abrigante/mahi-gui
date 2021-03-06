<p align="center">
<img src="https://raw.githubusercontent.com/mahilab/mahi-gui/master/mahi-gui.png" width="256"> 
</p>

## mahi-gui

This library provides an lightweight, all-in-one package for making GUIs and 2D visualizations in C++. It bundles [GLFW](https://www.glfw.org/) and [glad](https://github.com/Dav1dde/glad) for creating Windows and OpenGL contexts, [Dear ImGui](https://github.com/ocornut/imgui) with several custom extension classes and methods for all your GUI needs, [NanoVG](https://github.com/memononen/nanovg) and [NanoSVG](https://github.com/memononen/nanosvg) for drawing vector graphics, [NFD](https://github.com/mlabbe/nativefiledialog) for native file/folder dialogs, and a few custom utility classes such as Coroutines and Events to spice things up. 

### Integration

The library is small and intended to be used with CMake's `FetchContent`:

```cmake
include(FetchContent) 
FetchContent_Declare(mahi-gui GIT_REPOSITORY https://github.com/mahilab/mahi-gui.git) 
FetchContent_MakeAvailable(mahi-gui)

add_executable(my_app "my_app.cpp")
target_link_libraries(my_app mahi::gui)
```

That's it! You should also be able to install or use the library as a git-submodule + CMake subdirectory if you prefer.

### Example Usage

```cpp
// my_app.cpp
#include <Mahi/Gui.hpp>
#include <Mahi/Util.hpp>

using namespace mahi::gui;
using namespace mahi::util;

// Inherit from Application
class MyApp : public Application {
public:
    // 640x480 px window
    MyApp() : Application(640,480,"My App") { }
    // Override update (called once per frame)
    void update() override {
        // App logic and/or ImGui code goes here
        ImGui::Begin("Example");
        if (ImGui::Button("Press Me!"))
          print("Hello, World!"); 
        ImGui::End();
    }
};

int main() {
    MyApp app;
    app.run();
    return 0;
}
```

Run and consult the examples for other features. Pay particular attention to [demo.cpp](https://github.com/mahilab/mahi-gui/blob/master/examples/demo.cpp) which shows all of the functionality of the **ImGui** library. It calls the `ImGui::ShowDemoWindow()` function from [imgui_demo.cpp](https://github.com/mahilab/mahi-gui/blob/master/3rdparty/imgui/imgui_demo.cpp), which itself is the absolute best place for **ImGui** examples. For a real-world example, see [Syntacts' GUI](https://github.com/mahilab/Syntacts/tree/master/gui/src), which is built entirely using **mahi gui**.

### Requirements

- C++17 compiler (MSVC or Clang)

### Building for Windows

On Windows, we recommend using to MSVC 2019:

```shell
> cd mahi-gui
> mkdir build
> cmake .. -G "Visual Studio 16 2019" -A x64
> cmake --build . --config Release
```

### Building for macOS

If you're on a relatively new version of macOS, you should be able to use the defeault Apple Clang compiler:

```shell
> cd mahi-gui
> mkdir build && cd build
> cmake .. -DCMAKE_BUILD_TYPE="Release"
> cmake --build .
```

If your Apple Clang compiler is too [old](https://en.wikipedia.org/wiki/Xcode#Version_comparison_table), you can use `LLVM Clang` to build `mahi-gui`. For example, using Clang 9.0.0 downloaded from [here](http://releases.llvm.org/download.html):

```shell
> cd mahi-gui
> mkdir build && cd build
> cmake .. -DCMAKE_C_COMPILER="/path/to/clang/bin/clang" -DCMAKE_CXX_COMPILER="/path/to/clang/bin/clang++" -DCMAKE_BUILD_TYPE="Release"
> cmake --build .
```

### See Also
- [ImGui::Plot Discussion](https://github.com/ocornut/imgui/issues/3067)
