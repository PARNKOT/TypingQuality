SRC = main.c options.c utils.c
OBJ = $(SRC:.c=.o)
GCC = gcc -g -Wall
CFLAGS = -I includes
NAME = check_typing_quality
SRC_PREFIX = src
BINARY_DIR = binary


.PHONY: all clean install uninstall compile


all:
	$(GCC) $(SRC_PREFIX)/*.c -o $(NAME)


build: $(SRC)
	$(GCC) $(LDFLAGS) $(OBJ) -o $(NAME)


compile: $(SRC)
	mkdir $(BINARY_DIR)
	mv *.o $(BINARY_DIR)


%.c:
	$(GCC) -c $(CFLAGS) $(SRC_PREFIX)/$@


clean:
	rm -f *.o
	rm -f $(NAME)
	rm -rf $(BINARY_DIR)