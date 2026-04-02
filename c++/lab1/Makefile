object = build/barrel.o build/matrix.o build/mystring.o build/rect.o build/textwrapper.o

build/barrel.o: src/barrel/barrel.cpp src/barrel/barrel.hpp
	g++ -c -o build/barrel.o src/barrel/barrel.cpp

build/matrix.o: src/matrix/matrix.cpp src/matrix/matrix.hpp
	g++ -c -o build/matrix.o src/matrix/matrix.cpp

build/mystring.o: src/mystring/mystring.cpp src/mystring/mystring.hpp
	g++ -c -o build/mystring.o src/mystring/mystring.cpp

build/rect.o: src/rect/rect.cpp src/rect/rect.hpp
	g++ -c -o build/rect.o src/rect/rect.cpp

build/textwrapper.o: src/textwrapper/textwrapper.cpp src/textwrapper/textwrapper.hpp src/mystring/mystring.hpp
	g++ -c -o build/textwrapper.o src/textwrapper/textwrapper.cpp

build/test_bounding_rect.out: tests/test_bounding_rect.cpp build/rect.o
	g++ -g -o build/test_bounding_rect.out tests/test_bounding_rect.cpp build/rect.o

build/test_rect_basic_methods.out: tests/test_rect_basic_methods.cpp build/rect.o
	g++ -g -o build/test_rect_basic_methods.out tests/test_rect_basic_methods.cpp build/rect.o

build/test_rect_operations.out: tests/test_rect_operations.cpp build/rect.o
	g++ -g -o build/test_rect_operations.out tests/test_rect_operations.cpp build/rect.o

build/test_rect_properties.out: tests/test_rect_properties.cpp build/rect.o
	g++ -g -o build/test_rect_properties.out tests/test_rect_properties.cpp build/rect.o

test: build/test_bounding_rect.out build/test_rect_basic_methods.out build/test_rect_operations.out build/test_rect_properties.out
	./build/test_bounding_rect.out
	./build/test_rect_basic_methods.out
	./build/test_rect_operations.out
	./build/test_rect_properties.out

debug: build/debug.out
	gdb build/debug.out

build/debug.out: $(object) src/main.cpp
	g++ -g -o build/debug.out $(object) src/main.cpp

build/leaks.out: $(object) src/main.cpp
	g++ -g -fsanitize=address -o build/leaks.out $(object) src/main.cpp

leaks: build/leaks.out
	./build/leaks.out

clean:
	rm -rf build build/*