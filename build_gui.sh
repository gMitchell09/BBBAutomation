#-D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_{1,2,4} 
g++ -mcpu=cortex-a8 -lpthread `pkg-config gtkmm-2.4 --cflags --libs` `pkg-config --libs gthread-2.0` -std=c++0x ./thermo_gui.cpp ./BlackLib/BlackLib.a -o thermo_gui

