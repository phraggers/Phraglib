# __PhragLib__
### (c) Phragware 2024


After copy-pasting the same platform layer and painstakingly having to go through and rename all the things, I decided to make a single header platform layer library I can just include in every project.

- (At the moment only WINDOWS is done)
- Designed to run on any default x64 system
- no need for extra libraries, dlls or runtime installers for end users.
- Creates default resizable bordered Window (defaults to 960x540)
- loads modern OpenGL functions at startup

## How to use:
- #include <PL/PL.h>
- add PL/PL.c to your compiler input
- Don't define main(), instead define: void PL_Startup(), void PL_Frame(), void PL_ErrorCallback().
- PL_ErrorCallback is called when an error occurs.
- PL_Startup is called once before main loop.
- PL_Frame is called every frame after input/event handling, before window update.
- see PL.h for documentation, it is all commented.

## update history

### 2024-04-18
- updated to GL4.5
- fixed C++ build

### 2024-04-15
- added hash, RNG
- fixed stdout/stderr printing using visual studio
- added main() redirection if compiled using subsystem:console
- fixed input processing/updating per frame to show correct button wasDown and mousewheel states

### 2024-04-14
- finished first version of Windows platform layer
- my usual types, macros/helpers
- openGL 3.3
- Windows: XAudio2 API, XInput API basically done