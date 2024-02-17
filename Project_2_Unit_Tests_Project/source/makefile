CC = gcc
CFLAGS = -Wall -Werror

TARGET = main
SRC = main.c uint_to_binstr.c unit_test.c
HEADERS = uint_to_binstr.h unit_test.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $^ -o $@

trial: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $^ -g -o $@

clean:
	rm -f $(TARGET)

