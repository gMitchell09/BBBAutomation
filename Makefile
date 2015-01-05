CXX=g++
PKGCONFIG=gtkmm-2.4 gthread-2.0
CPPFLAGS=-g -mcpu=cortex-a8 -std=c++0x $(shell pkg-config --cflags $(PKGCONFIG))
CPPLIBS=-lpthread $(shell pkg-config --libs $(PKGCONFIG))
ADTLLIB=./BlackLib/BlackLib.a
EXECUTABLE=thermo_gui.out
SRCS=ThermoGUI.cpp NetworkListener.cpp MainWindow.cpp GUIController.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) $(OBJS) $(ADTLLIB) -o $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(CPPLIBS) -c $< -o $@

clean:
	rm $(OBJS)
