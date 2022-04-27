all: Makefile example1.out example2.out 

example1.out: Makefile obj/example1.o obj/Chunk.o obj/FixedAllocator.o 
	g++  obj/example1.o obj/Chunk.o obj/FixedAllocator.o -o example1.out

example2.out: Makefile obj/example2.o obj/Chunk.o obj/FixedAllocator.o 
	g++  obj/example2.o obj/Chunk.o obj/FixedAllocator.o -o example2.out

obj/Chunk.o: src/Chunk.cpp include/FixedAllocator.hpp include/Vector.hpp Makefile
	g++ -I . -I ./include -I ./obj -I ./src -I ./src/examples -Wall -Werror -c ./src/Chunk.cpp -o obj/Chunk.o

obj/FixedAllocator.o: src/FixedAllocator.cpp include/FixedAllocator.hpp \
 include/Vector.hpp Makefile
	g++ -I . -I ./include -I ./obj -I ./src -I ./src/examples -Wall -Werror -c ./src/FixedAllocator.cpp -o obj/FixedAllocator.o

obj/example1.o: src/examples/example1.cpp include/FixedAllocator.hpp \
 include/Vector.hpp Makefile
	g++ -I . -I ./include -I ./obj -I ./src -I ./src/examples -Wall -Werror -c src/examples/example1.cpp -o obj/example1.o

obj/example2.o: src/examples/example2.cpp include/FixedAllocator.hpp \
 include/Vector.hpp Makefile
	g++ -I . -I ./include -I ./obj -I ./src -I ./src/examples -Wall -Werror -c src/examples/example2.cpp -o obj/example2.o

