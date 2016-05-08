CXXFLAGS=-std=c++11 -g
LDFLAGS=-lglui -lglut -lGL -lGLU
oDir=oFiles/
oFiles=Partical.o Camera.o Bezier.o Physics.o ParticalRound.o main.o Object.o
all: $(oDir)
	make --no-print-directory unclear
	make --no-print-directory comp
	make --no-print-directory clear
$(oDir):
	mkdir $(oDir)
comp: $(oFiles)
	g++ -o Prog $(oFiles) $(LDFLAGS)
Partical.o: Partical.cpp Partical.hpp Object.hpp Algebra.h Bezier.hpp \
 includeGL.hpp
Camera.o: Camera.cpp Camera.h Algebra.h
Bezier.o: Bezier.cpp Bezier.hpp Algebra.h
Physics.o: Physics.cpp Physics.hpp Algebra.h Object.hpp Bezier.hpp
ParticalRound.o: ParticalRound.cpp ParticalRound.hpp Object.hpp Algebra.h \
 Bezier.hpp includeGL.hpp
main.o: main.cpp Camera.h Algebra.h Object.hpp Bezier.hpp Partical.hpp \
 includeGL.hpp ParticalRound.hpp Physics.hpp Shape.h Cube.h
Object.o: Object.cpp Object.hpp Algebra.h Bezier.hpp
unclear:
	@if ! mv $(oDir)*.o .; then printf "";fi
clear:
	@if ! mv *.o $(oDir); then printf "";fi
clean:
	rm *.o ;rm $(oDir)*.o
