CXX = g++
CXXFLAGS = -std=c++0x -O2
CPPFLAGS = -Wall -g
LIBS  = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect
OBJS  = main.o texture.o
TARGET = texture

a1:	$(OBJS)
	$(CXX) $(CXXLFAGS) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -f *.o $(TARGET)

main.o: texture.h 
texture.o : texture.h
