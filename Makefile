CXX=g++
INCDIR=include/
CXXFLAGS=-lm -std=c++11 -g
SRCDIR=src/
EXECUTABLE=ULMPExampleProgram

$(EXECUTABLE): clean
	$(CXX) $(CXXFLAGS) $(SRCDIR)*.cpp -I$(INCDIR) -o $(EXECUTABLE) 

.PHONY: clean

clean:
	rm -f $(EXECUTABLE)
