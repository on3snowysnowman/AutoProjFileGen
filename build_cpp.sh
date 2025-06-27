#!/bin/bash

g++ generate_cpp.cpp -o generate_cpp -Iinclude src/FileSystemHandler.cpp src/JsonHandler.cpp src/TextFileHandler.cpp src/TimeObserver.cpp