# GameSample

A DirectX 11 game development project written in C++ featuring 2D sprite rendering, animation, and texture management.

## Features

- **DirectX 11 Rendering**: Hardware-accelerated 2D graphics rendering
- **Sprite Animation System**: Frame-based sprite animation with customizable timing
- **Texture Management**: Efficient texture loading and management using DirectXTex
- **Debug Text Rendering**: ASCII-based debug text overlay system
- **Polygon Rendering**: Basic polygon rendering capabilities
- **Shader Support**: Vertex and pixel shader pipeline
- **Timer System**: High-precision timing for frame rate control

## Project Structure

### Core Files
- `main.cpp` - Application entry point and main game loop
- `direct3d.cpp/h` - DirectX 11 initialization and management
- `game_window.cpp/h` - Window creation and message handling

### Rendering System
- `sprite.cpp/h` - 2D sprite rendering
- `sprite_anim.cpp/h` - Sprite animation system
- `texture.cpp/h` - Texture loading and management
- `polygon.cpp/h` - Polygon rendering
- `shader.cpp/h` - Shader compilation and management

### Utilities
- `debug_text.cpp/h` - Debug text rendering system
- `debug_ostream.cpp/h` - Debug output stream
- `system_timer.cpp/h` - High-precision timing

### Shaders
- `shader_vertex_2d.hlsl` - 2D vertex shader
- `shader_pixel_2d.hlsl` - 2D pixel shader

### Assets
- Various PNG texture files for sprites and UI elements
- `consolab_ascii_512.png` - ASCII font texture for debug text
- `ascii_texture_generator.py` - Python script for generating ASCII textures

## Requirements

- **Visual Studio 2022** (v143 toolset)
- **Windows 10 SDK**
- **DirectX 11**
- **DirectXTex library** (included)

## Building

1. Open `GameSample01.sln` in Visual Studio 2022
2. Select your target configuration (Debug/Release) and platform (x64 recommended)
3. Build the solution (Ctrl+Shift+B)
4. Run the executable

## Controls

- **ESC** - Exit the application
- Window close button shows confirmation dialog

## Dependencies

- **DirectXTex** - For texture loading and processing
- **WICTextureLoader11** - For loading various image formats
- **DirectXMath** - For mathematical operations

## License

This project is for educational and development purposes.

## Author

LCH - Game Development Sample Project