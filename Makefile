build:
	gcc -Wall -std=c99 ./src/*.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11  -o Renderer

run:
	./Renderer

clean:
	rm Renderer
