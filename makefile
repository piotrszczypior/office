all: office
office: src/main.cpp
		g++ src/main.cpp -o office -lncurses -pthread
