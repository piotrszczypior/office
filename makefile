all: office

office: src/main.cpp
		mkdir -p build
		g++ src/main.cpp -o build/office -lncurses -pthread

clean:
	rm -r build