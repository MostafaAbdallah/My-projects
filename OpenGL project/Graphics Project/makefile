extension:= .out
underscore:= _
empty:=
space:= $(empty) $(empty)
trueFolderName:= $(notdir $(CURDIR))
trueFolderName+= $(extension)
folderName:= $(subst $(space),$(underscore),$(trueFolderName))
folderName:= $(subst &,and,$(folderName))

all: main

main: *.cpp
	g++ -g -std=c++0x -O -pedantic  *.cpp -lGL -lGLU -lglut -lGLEW -o $(folderName)

clean:
	rm -rf *.o $(folderName)
