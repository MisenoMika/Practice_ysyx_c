CC=gcc
CFLAGS=-g -Wall -fPIC -I. -Iinclude
LDFLAGS=
SRCS=$(wildcard src/**/*.c src/*.c)

EXE=bin/minirvEMU.exe
SO=build/libminirvEMU.so

.PHONY: all clean build

all: build $(EXE) $(SO)

$(EXE): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SRCS)

$(SO): $(SRCS) | build
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o $@ $(SRCS)

build:
	@mkdir -p build
	@mkdir -p bin

clean:
	rm -f $(EXE) $(SO) build/minirv_test_runner