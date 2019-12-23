CXX = g++
CXXFLAGS = -g -Wall $(INCLUDES)

mainOutput: mainOutput.cc

.PHONY: trace
trace: mainOutput
	./mainOutput > rainbow.ppm 




