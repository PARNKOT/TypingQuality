#!/usr/bin/bash

set -e

if [ ! -e VERSION ]
then
    echo "1.0" > VERSION
fi


VERSION=`cat VERSION`
NAME="check_typing_quality"
BUILD_DIR="build"
PACKAGE_DIR="package"
DEBIAN_DIR=$PACKAGE_DIR/DEBIAN
CONTROL_FILE=$DEBIAN_DIR/control

# Compile
gcc -I includes/ -o $NAME src/*.c


if [ ! -e $BUILD_DIR ]
then
    mkdir -p $BUILD_DIR
fi 

mv $NAME $BUILD_DIR


# Build
if [ ! -e $PACKAGE_DIR ]
then
    mkdir -p $PACKAGE_DIR
fi


if [ ! -e $DEBIAN_DIR ]
then
    mkdir -p $DEBIAN_DIR
fi


if [ ! -e $CONTROL_FILE ]
then
echo "
Version: $VERSION
Section: misc
Priority: optional
Maintainer: Egor Konyakhin <atomic14@mail.ru>
Depends: libc6
Package: checktypingquality
Architecture: amd64
Essential: No
Description: Test quality of manual typing.
  The programm reads lines from <file> and suggest to repeat them manually.
  It collects two metrics: time interval per one line and percents...
" > $CONTROL_FILE
fi

if [ ! -e $PACKAGE_DIR/usr/bin ]
then
mkdir -p $PACKAGE_DIR/usr/bin/
fi

cp $BUILD_DIR/$NAME $PACKAGE_DIR/usr/bin/

dpkg-deb --build $PACKAGE_DIR $NAME.deb

