NAME_L	= libserialize
NAME_G	= game
CC		= g++

UNAME_S := $(shell uname -s)


all: remove lib game

lib:
	$(CC) -Wall -fPIC -c serialize.cpp -std=c++17
ifeq ($(UNAME_S),Darwin)
	$(CC) -dynamiclib -undefined suppress -flat_namespace *.o -o $(NAME_L).dylib
else	
	$(CC) -shared -Wl,-soname,$(NAME_L).so.1 -o $(NAME_L).so *.o $(CFLAGS)
endif

game:
	$(CC) -Wall main.cpp game.cpp -L. -I. -std=c++17 -lserialize -o $(NAME_G)


remove:
	rm -f *.o game