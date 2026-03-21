object = build/mystring.o build/base_file.o

build/mystring.o: src/mystring/mystring.cpp src/mystring/mystring.hpp
	g++ -c -o build/mystring.o src/mystring/mystring.cpp

build/base_file.o: src/base-file/base_file.cpp src/base-file/base_file.hpp
	g++ -c -o build/base_file.o src/base-file/base_file.cpp

build/test_base.out: tests/test_base.cpp $(object)
	g++ -g -o build/test_base.out tests/test_base.cpp $(object)

build/test_base32_2.out: tests/test_base32_2.cpp $(object)
	g++ -g -o build/test_base32_2.out tests/test_base32_2.cpp $(object)

build/test_base32.out: tests/test_base32.cpp $(object)
	g++ -g -o build/test_base32.out tests/test_base32.cpp $(object)

build/test_composition.out: tests/test_composition.cpp $(object)
	g++ -g -o build/test_composition.out tests/test_composition.cpp $(object)

build/test_rle_2.out: tests/test_rle_2.cpp $(object)
	g++ -g -o build/test_rle_2.out tests/test_rle_2.cpp $(object)

build/test_rle.out: tests/test_rle.cpp $(object)
	g++ -g -o build/test_rle.out tests/test_rle.cpp $(object)

test: build/test_base.out build/test_base32_2.out build/test_base32.out build/test_composition.out build/test_rle_2.out build/test_rle.out
	./build/test_base.out
	./build/test_base32_2.out
	./build/test_base32.out
	./build/test_composition.out
	./build/test_rle_2.out
	./build/test_rle.out

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