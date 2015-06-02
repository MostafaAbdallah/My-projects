extension:= .out
underscore:= _
empty:=
space:= $(empty) $(empty)
trueFolderName:= $(notdir $(CURDIR))
trueFolderName+= $(extension)
folderName:= $(subst $(space),$(underscore),$(trueFolderName))
folderName:= $(subst &,and,$(folderName))

all: main

main: main.cpp
	g++ -g -std=c++0x -O -Wall -Wextra -pedantic -Weffc++ main.cpp -lGL -lGLU -lglut -o $(folderName)

clean:
	rm -rf *.o $(folderName)
