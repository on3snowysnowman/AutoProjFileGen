@REM g++ -c generate.cpp src/FileSystemHandler.cpp src/JsonHandler.cpp src/TextFileHandler.cpp src/TimeObserver.cpp -Iinclude && g++ generate.o FileSystemHandler.o JsonHandler.o TextFileHandler.o TimeObserver.o -o generate.exe
@echo off


if not exist "obj" (
    mkdir obj
)

cd obj

g++ -c ../src/FileSystemHandler.cpp ../src/JsonHandler.cpp ../src/TextFileHandler.cpp ../src/TimeObserver.cpp ../generate.cpp -I../include

cd ..

g++ obj/FileSystemHandler.o obj/JsonHandler.o obj/TextFileHandler.o obj/TimeObserver.o obj/generate.o -o generate

rmdir /s /q "obj"
