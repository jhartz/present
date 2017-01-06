# Compilers for C and C++
CC ?= gcc
CXX ?= g++

# Flags for compiling both C or C++
WARNING_FLAGS ?= -Wall -Wextra -pedantic -Wno-type-limits
FLAGS = -I./include -I./src $(WARNING_FLAGS)

# Add debug flags if necessaey
ifdef DEBUG
	FLAGS += -g
endif

# C-specific flags
CFLAGS += $(FLAGS) -std=c99

# C++-specific flags
CXXFLAGS += $(FLAGS) -std=c++11


MODULES = clock-time date day-delta month-delta time-delta timestamp
C_OBJECTS = $(MODULES:%=build/%.c.o) build/present-syscalls.c.o
CXX_OBJECTS = $(MODULES:%=build/%.cpp.o)
TEST_SRC = $(MODULES:%=test/%-test.cpp)

LIBRARY_OBJECT_FLAGS = -fpic
LIBRARY_FLAGS = -shared

libpresentc_COMPILER = $(CC)
libpresentc_FLAGS = $(CFLAGS)

libpresent_COMPILER = $(CXX)
libpresent_FLAGS = $(CXXFLAGS)


default: build_dir shared build/present-repl

all: build_dir shared static build/present-repl build/present-test

test: build_dir build/present-test
	./build/present-test

build_dir:
	mkdir -p build/

.PHONY: default all test build_dir

# REPL

build/present-repl: $(C_OBJECTS) $(CXX_OBJECTS) build/repl.o
	$(CXX) $(CXXFLAGS) -L./build -o $@ $^

build/repl.o: src/repl.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Tests

build/present-test: $(C_OBJECTS) $(CXX_OBJECTS) $(TEST_SRC) test/test.cpp
	$(CXX) $(CXXFLAGS) -L./build -o $@ $^

# Shared libraries

shared: build_dir build/libpresent.so build/libpresentc.so

build/libpresent.so: $(C_OBJECTS) $(CXX_OBJECTS)
	$(libpresent_COMPILER) $(libpresent_FLAGS) $(LIBRARY_FLAGS) -o $@ $^

build/libpresentc.so: $(C_OBJECTS)
	$(libpresentc_COMPILER) $(libpresentc_FLAGS) $(LIBRARY_FLAGS) -o $@ $^

.PHONY: shared

# Static libraries

static: build_dir build/libpresent.a build/libpresentc.a

build/libpresent.a: $(C_OBJECTS) $(CXX_OBJECTS)
	ar rcs $@ $^

build/libpresentc.a: $(C_OBJECTS)
	ar rcs $@ $^

.PHONY: static

# Individual object files

build/%.cpp.o: src/%.cpp
	$(libpresent_COMPILER) $(libpresent_FLAGS) $(LIBRARY_OBJECT_FLAGS) -c $< -o $@

build/%.c.o: src/%.c
	$(libpresentc_COMPILER) $(libpresentc_FLAGS) $(LIBRARY_OBJECT_FLAGS) -c $< -o $@

# Cleanup

clean: clean-o clean-so clean-a clean-bin

clean-o:
	rm -f build/*.o

clean-so:
	rm -f build/*.so

clean-a:
	rm -f build/*.a

clean-bin:
	rm -f build/present-repl build/present-test

.PHONY: clean clean-o clean-so clean-a clean-bin

