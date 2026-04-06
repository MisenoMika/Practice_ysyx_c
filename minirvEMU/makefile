CC=gcc
CFLAGS=-g -Wall -fPIC -I. -Iinclude
LDFLAGS=
CSRCS=$(wildcard src/**/*.c src/*.c)

EXE=bin/minirvEMU.exe
SO=build/libminirvEMU.so


.PHONY: all clean build

all: build $(EXE) $(SO)

$(EXE): $(CSRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(CSRCS)

$(SO): $(CSRCS) | build
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o $@ $(CSRCS)

build:
	@mkdir -p build
	@mkdir -p bin

clean:
	rm -f $(EXE) $(SO) build/minirv_test_runner