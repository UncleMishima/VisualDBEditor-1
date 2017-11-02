qmake.exe .\VisualDBEditor.pro -spec win32-g++
mingw32-make.exe qmake_all
mingw32-make -f Makefile.Release
