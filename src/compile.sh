#!/bin/bash

CC="g++"
CFLAGS="-no-pie -std=c++17"
SRCS="main.cpp
display.cpp game.cpp input.cpp 
render/mesh.cpp render/shader.cpp render/texture.cpp
node/node.cpp 
node/physics/staticbody.cpp node/physics/kinematicbody.cpp
node2d/node2d.cpp node2d/sprite.cpp"
HDRS="display.hpp game.hpp input.hpp
render/mesh.hpp render/shader.hpp render/texture.hpp
node/node.hpp
node/physics/staticbody.hpp node/physics/kinematicbody.hpp
node2d/node2d.hpp node2d/sprite.hpp"
BIN=" exec"
GL_LINKS=" -lGL -lGLEW -lSDL2 -llua5.2"
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

build_obj
link
echo "Done!"
