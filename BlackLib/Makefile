CC=g++
CCFLAGS=-c -std=c++0x
SOURCES=BlackADC.cpp BlackCore.cpp BlackGPIO.cpp BlackI2C.cpp BlackPWM.cpp BlackSPI.cpp BlackUART.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=BlackLib.a

all: $(OBJECTS) $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@
	ar rvs $(LIBRARY) $(OBJECTS)

#BlackADC.o: BlackADC.cpp
#	$(CC) $(CCFLAGS) -c $(input) -o $(output)
#BlackCore.o: BlackCore.cpp
#	$(CC) $(CCFLAGS) -c $(input) -o $(output)
#BlackGPIO.o: BlackGPIO.cpp
#	$(CC) $(CCFLAGS) -c $(input) -o $(output)
#BlackI2C.o: BlackI2C.cpp
#	$(CC) $(CCFLAGS) -c $(input) -o $(output)
#BlackPWM.o: BlackPWM.cpp
#	$(CC) $(CCFLAGS) -c $(input) -o $(output)
#BlackSPI.o: BlackSPI.cpp
#	$(CC) $(CCFLAGS) -c $(input) -o $(output)
#BlackUART.o: BlackUART.cpp
#	$(CC) $(CCFLAGS) -c $(input) -o $(output)
#$(OBJECTS): $@
#	$(CC) $(CCFLAGS) -c $(input) -o $(output)

.cpp.o:
	$(CC) $(CCFLAGS) $< -o $@
