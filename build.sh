#!/bin/bash

g++ generate.cpp -o generate -Iinclude src/FileSystemHandler.cpp src/JsonHandler.cpp src/TextFileHandler.cpp src/TimeObserver.cpp

# If the build directory does not exist.
# if [ ! -d obj ]; then
#     mkdir obj
# fi

# cd obj

# g++ -c ../src/*.cpp -I../include 
# g++ -c ../generate.cpp -I../include

# cd ..

# g++ obj/*.o -o generate

# rm -r obj