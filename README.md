# protobuf-dll-cmake
DLL exposes two methods
* char* serialize(struct* DTO);
* struct* deserialize(char* arr);

Struct is meant to work as DTO layer, consists only a primitive cpp structure generated from *.proto and does not require header files from Protobuf.

Protocol Buffer enhanced classes are compiled into DLL so this logic does not leak. 

# how to compile
* install msys2 (https://www.msys2.org/)
* update all dependencies using (pacman -Syu)
    * repeat until no more updates are coming in (!!)

# required C dependencies for build (as pacman cmds)
* pacman -S mingw-w64-x86_64-make
* pacman -S mingw-w64-x86_64-cmake
* pacman -S mingw-w64-x86_64-gcc
* pacman -S mingw-w64-x86_64-gcc-libs
* pacman -S mingw-w64-x86_64-protobuf
* pacman -S mingw-w64-x86_64-python
* pacman -S mingw-w64-x86_64-python-pip

# required Python dependencies for build (as pip cmds)
* pip install pbtools

# how to build
* open MSYS2 Mingw 64-bit shell (installed by msys2)
* ./build

# how to clean
* open MSYS2 Mingw 64-bit shell (installed by msys2)
* ./clean

# required dependencies for runtime
* protobuf.dll

# extra
All available packages for pacman (mingw prefixed):
* https://packages.msys2.org/package/

