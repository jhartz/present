# Compilers for C and C++
CC ?= gcc
CXX ?= g++

# Flags for compiling both C or C++
WARNING_FLAGS ?= -Wall -Wextra -pedantic -Wno-type-limits
FLAGS = -I./include -I./src $(WARNING_FLAGS)

# C-specific flags
CFLAGS += $(FLAGS) -std=c99

# C++-specific flags
CXXFLAGS += $(FLAGS) -std=c++11


MODULES = clock-time date day-delta month-delta time-delta timestamp
C_OBJECTS = $(MODULES:%=build/%.c.o)
CXX_OBJECTS = $(MODULES:%=build/%.cpp.o)
TEST_SRC = $(MODULES:%=test/%-test.cpp)

UTIL_HEADERS = include/present/utils/types.h include/present/utils/utils.h \
			   src/impl-constants.h src/impl-utils.h

LIBRARY_OBJECT_FLAGS = -fpic
LIBRARY_FLAGS = -shared

libpresentc_COMPILER = $(CC)
libpresentc_FLAGS = $(CFLAGS)

libpresent_COMPILER = $(CXX)
libpresent_FLAGS = $(CXXFLAGS)


default: build/libpresent.so build/libpresentc.so

all: build/libpresentc.so build/libpresent.so build/present-repl build/present-test

test: build/present-test
	./build/present-test

.PHONY: test

# REPL

build/present-repl: $(C_OBJECTS) $(CXX_OBJECTS) build/repl.o
	$(CXX) $(CXXFLAGS) -L./build -o $@ $^

build/repl.o: src/repl.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Tests

build/present-test: $(C_OBJECTS) $(CXX_OBJECTS) $(TEST_SRC) test/test.cpp
	$(CXX) $(CXXFLAGS) -L./build -o $@ $^

# Shared libraries

build/libpresent.so: $(C_OBJECTS) $(CXX_OBJECTS)
	$(libpresent_COMPILER) $(libpresent_FLAGS) $(LIBRARY_FLAGS) -o $@ $^

build/libpresentc.so: $(C_OBJECTS)
	$(libpresentc_COMPILER) $(libpresentc_FLAGS) $(LIBRARY_FLAGS) -o $@ $^

# Individual object files

build/%.cpp.o: src/%.cpp include/present/%.h include/present/impl/present-%-data.h $(UTIL_HEADERS)
	$(libpresent_COMPILER) $(libpresent_FLAGS) $(LIBRARY_OBJECT_FLAGS) -c $< -o $@

build/%.c.o: src/%.c include/present/%.h include/present/impl/present-%-data.h $(UTIL_HEADERS)
	$(libpresentc_COMPILER) $(libpresentc_FLAGS) $(LIBRARY_OBJECT_FLAGS) -c $< -o $@

clean: clean-o clean-so clean-bin

clean-o:
	rm -f build/*.o

clean-so:
	rm -f build/*.so

clean-bin:
	rm -f build/present-repl build/present-test

.PHONY: clean clean-o clean-so clean-bin

