CXXFLAGS=-std=c++11 -g
LDFLAGS=-lglui -lglut -lGL -lGLU
oDir=oFiles/
oFiles=ParticalRound.o main.o Partical.o Camera.o
all: $(oDir)
	make --no-print-directory unclear
	make --no-print-directory comp
	make --no-print-directory clear
$(oDir):
	mkdir $(oDir)
comp: $(oFiles)
	g++ -o prog $(oFiles) $(LDFLAGS)
ParticalRound.o: ParticalRound.cpp ParticalRound.hpp Object.hpp Algebra.h \
 includeGL.hpp
main.o: main.cpp Camera.h Algebra.h Object.hpp Partical.hpp includeGL.hpp \
 ParticalRound.hpp
Partical.o: Partical.cpp Partical.hpp Object.hpp Algebra.h includeGL.hpp
Camera.o: Camera.cpp Camera.h Algebra.h
unclear:
	@if ! mv $(oDir)*.o .; then printf "";fi
clear:
	@if ! mv *.o $(oDir); then printf "";fi
clean:
	rm *.o ;rm $(oDir)*.o
