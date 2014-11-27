CFLAGS=-ll
CC=g++
all:example2
example2: main.cpp 
	$(CC) main.cpp Player.cpp Location.cpp Monopoly.cpp Camera.cpp Keyboard.cpp Location.cpp Math.cpp mouse.cpp loadObject.cpp Texture.cpp Vector3f.cpp skyBoxTexture.cpp -lboost_serialization -lboost_thread -lboost_system -ldrawtext -framework Carbon -framework OpenGL -framework GLUT -framework GLUI -o example2

clean:
	rm -rf *o example2