QT_VERSION = 5.14.2
PROJECT_NAME = qt-element-ui
PROJECT_VERSION = 0.1.0

ifeq ($(OS), Windows_NT)
    MAKE = mingw32-make
	DEPLOY_DIR = $(PROJECT_NAME)_$(PROJECT_VERSION)_$(OS)_$(QT_VERSION)
else
    MAKE = make
	DEPLOY_DIR = $(PROJECT_NAME)_$(PROJECT_VERSION)_$(shell uname)_$(QT_VERSION)
endif


.PHONY: all build run clean deploy

all:
	make build && make run

build:
	mkdir -p build
	cd build && qmake.exe ../qt-element-ui.pro
	cd build && $(MAKE) -j16

run:
	cd build/release && ./qt-element-ui

clean:
	rm -rf build

ifeq ($(OS), Windows_NT)
deploy: build
	cd build && $(MAKE) clean
	cd build && cp -r release $(DEPLOY_DIR)
	cd build && windeployqt $(DEPLOY_DIR)/qt-element-ui.exe
	cd build && zip -r $(DEPLOY_DIR).zip $(DEPLOY_DIR)

else ifeq ($(shell uname), Linux)
deploy: build
	cd build && $(MAKE) clean
	cd build && mkdir -p $(DEPLOY_DIR)
	cd build && cp qt-element-ui $(DEPLOY_DIR)
	cp statics/qt-element-ui.desktop statics/qt-element-ui.png build/$(DEPLOY_DIR)
	cd build && linuxdeployqt $(DEPLOY_DIR)/qt-element-ui -appimage -unsupported-allow-new-glibc -always-overwrite
# if cannot found -lGL, do
# `sudo apt install libgl1-mesa-dev` on Ubuntu/Debian,
# `sudo dnf install mesa-libGL-devel` on Fedora/RHEL,
# `sudo pacman -S mesa` on Arch Linux.
# if linuxdeployqt not found, do
# ```
# wget https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
# mv linuxdeployqt-continuous-x86_64.AppImage linuxdeployqt
# chmod +x linuxdeployqt
# sudo mv linuxdeployqt /usr/local/bin/linuxdeployqt
# linuxdeployqt --version
# ```
# if failed to download runtime file,
# please set the network proxy environment variables.

else ifeq ($(shell uname), Darwin)
deploy: build
	cd build && $(MAKE) clean
	cd build && mkdir -p $(DEPLOY_DIR)
	cd build && cp -r $(PROJECT_NAME).app $(DEPLOY_DIR)
	cd build && macdeployqt $(DEPLOY_DIR)/$(PROJECT_NAME).app # -dmg
endif
