mkdir build
cd build

qmake ../qt-element-ui.pro CONFIG+=release

mingw32-make -j8
