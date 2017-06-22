CC = g++
CFLAGS  = -c -g -Wall -std=c++11
LDFLAGS =

CFLAGS  += `root-config --cflags --glibs` -lRGL -lGeom
LDFLAGS += `root-config --cflags --glibs` -lRGL -lGeom

SOURCES  = $(wildcard *.cc)
SOURCES += $(wildcard dummyClasses/*.cc)

OBJECTS  = $(SOURCES:.cc=.o)
# OBJECTS += EclFrameDict.o
EXECUTABLE=ecldisplay.out

all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

EclFrameDict.o:
	rootcint -f EclFrameDict.cc -c EclFrame.h linkdef.h
	$(CC) $(CFLAGS) EclFrameDict.cc -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
	rm -rf EclFrameDict.cc

