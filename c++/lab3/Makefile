object = build/base_file.o build/bool_array.o build/matrix.o build/mystring.o build/notification.o build/worker_data.o build/worker_db.o 

build/base_file.o: src/base-file/base_file.cpp src/base-file/base_file.hpp
	g++ -c -o build/base_file.o src/base-file/base_file.cpp

build/bool_array.o: src/bool-array/bool_array.cpp src/bool-array/bool_array.hpp
	g++ -c -o build/bool_array.o src/bool-array/bool_array.cpp

build/matrix.o: src/matrix/matrix.cpp src/matrix/matrix.hpp
	g++ -c -o build/matrix.o src/matrix/matrix.cpp

build/mystring.o: src/mystring/mystring.cpp src/mystring/mystring.hpp
	g++ -c -o build/mystring.o src/mystring/mystring.cpp

build/notification.o: src/notification/notification.cpp src/notification/notification.hpp
	g++ -c -o build/notification.o src/notification/notification.cpp

build/worker_data.o: src/worker-data/worker_data.cpp src/worker-data/worker_data.hpp
	g++ -c -o build/worker_data.o src/worker-data/worker_data.cpp

build/worker_db.o: src/worker-db/worker_db.cpp src/worker-db/worker_db.hpp
	g++ -c -o build/worker_db.o src/worker-db/worker_db.cpp

build/test_priority_queue.out: tests/test_priority_queue.cpp $(object)
	g++ -g -o build/test_priority_queue.out tests/test_priority_queue.cpp $(object)

test: build/test_priority_queue.out
	./build/test_priority_queue.out

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