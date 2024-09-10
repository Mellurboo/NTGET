rmdir /s /q build
mkdir build

windres src\windows\resource.rc -O coff -o build\resource.o
gcc -o "build\NTGET Installer.exe" src\setup.c src\pathenv.c build\resource.o
pause