CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES)) #%:通配符

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/liblcthw.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))
# The Target Build
all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS) #$@:自动变量，表示目标文件
	ar rcs $@ $(OBJECTS) 
	ranlib $@
$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)
build: # @表示不显示命令
	@mkdir -p build
	@mkdir -p bin
# The Unit Tests
$(TESTS): %: %.c # $<:自动变量，表示第一个依赖文件 $:自动变量，表示目标文件
	$(CC) $(CFLAGS) $< -o $@ $(LIBS) 
.PHONY: tests
tests: LIBS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh
	
.PHONY: valgrind
valgrind:
	VALGRIND="valgrind --leak-check=full --log-file=/tmp/valgrind-%p.log" $(MAKE) tests
	@echo "Valgrind logs are in /tmp/valgrind-*.log"
	@ls -lh /tmp/valgrind-*.log
# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@egrep $(BADFUNCS) $(SOURCES) && echo "Files with potentially dangerous functions." || true
