#!/bin/bash

mkdir eclDisplay
mkdir eclDisplay/include eclDisplay/src

cp sources/*.h eclDisplay/include
cp sources/*.cc eclDisplay/src

cp module_files/*.h eclDisplay/include
cp module_files/*.cc eclDisplay/src
cp module_files/SConscript eclDisplay

rm eclDisplay/*/EclFrameDict.*
rm eclDisplay/*/main.*

# Changing include paths from dummy files to BASF2 files.
sed -i \
    -e "s/\"dummyClasses\/Logger.h\"/<framework\/logging\/Logger.h>/" \
    -e "s/\"dummyClasses\/ECLDigit.h\"/<ecl\/dataobjects\/ECLDigit.h>/" \
    -e "s/\"dummyClasses\/eclChannelMapper.h\"/<ecl\/utility\/eclChannelMapper.h>/" \
    eclDisplay/include/*.h eclDisplay/src/*.cc

sed -i \
    -e "s/\(\#include <.*\)\/include\(.*>\)/\1\2/" \
    -e "s/#include \"\(.*\)\"/#include <ecl\/modules\/eclDisplay\/\1>/" \
    eclDisplay/src/*.cc eclDisplay/include/*.h

echo "Done. The generated module is placed in eclDisplay folder"

