qmake.exe .\VisualDBEditor.pro -spec win32-g++ "CONFIG+=release" "DESTDIR=.\Build" 
mingw32-make.exe qmake_all
mingw32-make -f Makefile.Release
