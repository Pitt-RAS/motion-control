#!/bin/sh

mkdir build
cd build

case "$TYPE" in
	x86gcc)
		cmake ..
		make
	;;
	x86clang)
		export CC=clang
		cmake ..
		make
	;;
	pi3)
		sudo apt-get install -y libc6-dev-armhf-cross gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
		cmake -DCMAKE_SYSTEM_NAME=Linux -DCMAKE_C_COMPILER=/usr/bin/arm-linux-gnueabihf-gcc -DCMAKE_CXX_COMPILER=/usr/bin/arm-linux-gnueabihf-g++ ..
		make
	;;
esac