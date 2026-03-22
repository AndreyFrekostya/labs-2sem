object = build/circle.o build/list.o build/point.o

build/circle.o: src/circle/circle.cpp src/circle/circle.hpp src/point/point.hpp
	g++ -c -o build/circle.o src/circle/circle.cpp

build/list.o: src/list/list.cpp src/list/list.hpp src/circle/circle.hpp
	g++ -c -o build/list.o src/list/list.cpp

build/point.o: src/point/point.cpp src/point/point.hpp
	g++ -c -o build/point.o src/point/point.cpp

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