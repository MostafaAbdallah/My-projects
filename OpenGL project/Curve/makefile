extension:= .out
underscore:= _
empty:=
space:= $(empty) $(empty)
trueFolderName:= $(notdir $(CURDIR))
trueFolderName+= $(extension)
folderName:= $(subst $(space),$(underscore),$(trueFolderName))
folderName:= $(subst &,and,$(folderName))

all: main

main: main.o BezierCurve.o
	g++ -std=c++0x -O -Wall -Wextra -pedantic -Weffc++ $^ -lGL -lGLU -lglut -o $(folderName)

main.o: main.cpp BezierCurve.o
	g++ -c -std=c++0x -O -Wall -Wextra -pedantic -Weffc++ $< -lGL -lGLU -lglut

BezierCurve.o:	BezierCurve.cpp
	g++ -c -std=c++0x -O -Wall -Wextra -pedantic -Weffc++ $< -lGL -lGLU -lglut

clean:
	rm -rf *.o $(folderName)
