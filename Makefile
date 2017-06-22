#   FLAGS   #

CC = g++
CFLAGS  = -c -g -Wall -std=c++11
LDFLAGS =

CFLAGS  += `root-config --cflags --glibs` -lRGL -lGeom
LDFLAGS += `root-config --cflags --glibs` -lRGL -lGeom

#   FILES   #

SOURCES  = $(wildcard sources/*.cc)
SOURCES += sources/EclFrameDict.cc
SOURCES += $(wildcard sources/dummyClasses/*.cc)

OBJECTS  = $(SOURCES:.cc=.o)

EXECUTABLE = ecldisplay.out

#   MAKE TARGETS   #

.PHONY: all clean
.SECONDARY: main-build

#   MAKE PROCESS   #

all: pre-build main-build

pre-build:
	@echo $(SOURCES)
	@echo $(OBJECTS)
	@echo Pre-build: generating ROOT dictionary for EclFrame class
	cd sources; rootcint -f EclFrameDict.cc -c EclFrame.h linkdef.h

main-build: $(SOURCES) $(EXECUTABLE)

#   MAKE PROCESS - SECONDARY   #

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

sources/EclFrameDict.o:
	$(CC) $(CFLAGS) sources/EclFrameDict.cc -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf sources/*.o sources/dummyClasses/*.o $(EXECUTABLE)
	rm -rf sources/EclFrameDict.*

