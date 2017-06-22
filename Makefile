CC = g++
CFLAGS  = -c -g -Wall -std=c++11
LDFLAGS =

CFLAGS  += `root-config --cflags --glibs` -lRGL -lGeom
LDFLAGS += `root-config --cflags --glibs` -lRGL -lGeom

SOURCES  = $(wildcard sources/*.cc)
SOURCES += $(wildcard sources/dummyClasses/*.cc)

OBJECTS  = $(SOURCES:.cc=.o)
# OBJECTS += EclFrameDict.o
EXECUTABLE=ecldisplay.out

all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

EclFrameDict.o:
	rootcint -f sources/EclFrameDict.cc -c sources/EclFrame.h sources/linkdef.h
	$(CC) $(CFLAGS) sources/EclFrameDict.cc -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf sources/*.o sources/dummyClasses/*.o $(EXECUTABLE)
	rm -rf sources/EclFrameDict.cc

