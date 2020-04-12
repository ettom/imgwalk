# imgwalk
A program to recursively search for JPEG image files in a directory and filter
them based on Exif data (capture date and camera model)

### Dependencies
* A compiler with C++17 support
  ([clang-8+](http://llvm.org/releases/download.html), [gcc-9.2+](https://gcc.gnu.org/releases.html))
* [cmake 3.6+](https://cmake.org/download/)
* [libexif](https://libexif.github.io/)

### Building and installing
Run in the root directory of the project:
```
mkdir -p build && cd build
cmake ..
make
```

To install:
```
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
sudo make install
sudo ldconfig
```

To run the tests:
```
make test
```

### Usage and examples
See `imgwalk -h` for complete instructions

For example, to list every `.jpg` file in the current directory and its
subdirectories that were taken with a Canon camera:
```
imgwalk -i -f "*.jpg" -c "canon*"
```

To get information about specific files:
```
imgwalk file_1 file_2
```

The utility skips the files and directories it cannot read due to inadequate
permissions and symlinks are not followed.
