CXXFLAGS=-g
LDFLAGS=-lglui -lglut -lGL -lGLU
oDir=oFiles/
oFiles=Object.o Bezier.o ParticalRound.o main.o Physics.o Partical.o Camera.o
all: $(oDir)
	make --no-print-directory unclear
	make --no-print-directory comp
	make --no-print-directory clear
$(oDir):
	mkdir $(oDir)
comp: $(oFiles)
	g++ -o Prog $(oFiles) $(LDFLAGS)
Object.o: Object.cpp Object.hpp Algebra.h
Bezier.o: Bezier.cpp Bezier.hpp Algebra.h
ParticalRound.o: ParticalRound.cpp ParticalRound.hpp Object.hpp Algebra.h \
 includeGL.hpp
main.o: main.cpp Camera.h Algebra.h Object.hpp Partical.hpp includeGL.hpp \
 ParticalRound.hpp Physics.hpp
Physics.o: Physics.cpp Physics.hpp Algebra.h Object.hpp
Partical.o: Partical.cpp Partical.hpp Object.hpp Algebra.h includeGL.hpp
Camera.o: Camera.cpp Camera.h Algebra.h
unclear:
	@if ! mv $(oDir)*.o .; then printf "";fi
clear:
	@if ! mv *.o $(oDir); then printf "";fi
clean:
	rm *.o ;rm $(oDir)*.o
