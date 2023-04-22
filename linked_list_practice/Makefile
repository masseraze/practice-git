CC     = gcc
SRC    = $(shell find ./ -maxdepth 1 -name '*\.c')
OBJ    = $(patsubst %.c, %.o, $(SRC))
CFLAG  =
TARGET = link_test


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c -o $@ -g $^

clean:
	rm -f $(OBJ) $(TARGET)
