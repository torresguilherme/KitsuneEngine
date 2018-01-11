#!/bin/bash

CC="g++"
CFLAGS=" -no-pie -g3 -std=c++17"
SRCS="main.cpp display.cpp game.cpp input.cpp render/mesh.cpp"
HDRS="display.hpp game.hpp input.hpp render/mesh.hpp"
BIN=" exec"
GL_LINKS=" -lGL -lGLEW -lSDL2"
DB="gdb"

if [ "$1" ] && [ $1 == "clean" ]
then
	echo "Deleting objects..."
	for SRC in $SRCS
	do
		OBJ=${SRC/%.cpp/.o}
		rm -f $OBJ
	done
	echo "Done!"
	exit
fi

build_obj()
{
	echo "Compiling objects..."
	for SRC in $SRCS
	do
		OBJ=${SRC/%.cpp/.o}
		OBJS="$OBJ $OBJS"
		for HDR in $HDRS
		do
			if [ $HDR -nt $OBJ ] || [ $SRC -nt $OBJ ]
			then
				echo "Compiling $SRC"
				$CC $CFLAGS -c $SRC -o $OBJ $GL_LINKS
			fi
		done
	done
	echo "Done compiling the objects!"
}

link()
{
	for OBJ in $OBJS
	do
		if [ $OBJ -nt $BIN ]
		then
			echo "Linking objects..."
			$CC $CFLAGS $OBJS -o $BIN $GL_LINKS
			break
		fi
	done
}

build_obj $SRCS
link $OBJS
echo "Done!"
