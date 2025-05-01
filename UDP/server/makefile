CPP = g++
CPPFLAGS = -Wall -Wextra -g
SRC ?= main.c
TARGET = $(basename $(SRC))

all: $(TARGET)

$(TARGET): $(SRC)
    $(CPP) $(CPPFLAGS) -o $@ $<

clean:
    rm -f $(TARGET)

run: $(TARGET)
    ./$(TARGET)

build_run: clean all run

.PHONY: all clean run build_run