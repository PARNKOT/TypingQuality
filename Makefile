SRC = main.c options.c utils.c
OBJ = $(SRC:.c=.o)
GCC = gcc -g -Wall
CFLAGS = -I includes
NAME = check_typing_quality
SRC_PREFIX = src
BINARY_DIR = binary
TARGET_DIR = ~/.local/bin


.PHONY: all clean install uninstall compile


#all:
#	$(GCC) $(SRC_PREFIX)/*.c -o $(NAME)


build: $(SRC)
	$(GCC) $(LDFLAGS) $(OBJ) -o $(NAME)
	rm -f *.o


compile: $(SRC)
	mkdir $(BINARY_DIR)
	mv *.o $(BINARY_DIR)


%.c:
	$(GCC) -c $(CFLAGS) $(SRC_PREFIX)/$@


install:
	install $(NAME) $(TARGET_DIR)

uninstall:
	rm -f $(TARGET_DIR)/$(NAME)

clean:
	rm -f *.o
	rm -f $(NAME)
	rm -rf $(BINARY_DIR)
