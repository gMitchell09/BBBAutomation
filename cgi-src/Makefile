CC=g++
CCFLAGS=-c -std=c++0x
SOURCES=*.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(OBJECTS)

.cpp.o:
	$(CC) $(CCFLAGS) $< -o $@

install: $(OBJECTS)
	cp $< /www/pages/rest/$<
