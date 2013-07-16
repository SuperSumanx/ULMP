CXX=g++
INCDIR=include/
SRCDIR=src/
EXECUTABLE=ULMPExampleProgram

$(EXECUTABLE): clean
	$(CXX) -lm -std=c++11 -g $(SRCDIR)*.cpp -I$(INCDIR) -o $(EXECUTABLE) 

.PHONY: clean

clean:
	rm -f $(EXECUTABLE)
