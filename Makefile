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
C_OBJECTS = $(MODULES:%=build/%.c.o) build/utils/time-utils.c.o
TEST_SRC = $(MODULES:%=test/%-test.cpp) test/test-utils.cpp test/test.cpp
UTIL_HEADERS = include/present.h include/present-config.h	\
			   include/present/internal/header-utils.h		\
			   include/present/internal/typedefs-nostdint.h	\
			   include/present/internal/typedefs-stdint.h	\
			   include/present/internal/types.h				\
			   src/utils/constants.h src/utils/impl-utils.h	\
			   src/utils/time-utils.h

LIBRARY_OBJECT_FLAGS = -fpic
LIBRARY_FLAGS = -shared

libpresent_COMPILER = $(CC)
libpresent_FLAGS = $(CFLAGS)


default: build_dir shared build/present-repl

all: build_dir shared static build/present-repl build/present-test

test: build_dir build/present-test
	./build/present-test

build_dir:
	mkdir -p build/utils/

.PHONY: default all test build_dir

# REPL

build/present-repl: $(C_OBJECTS) build/repl.o
	$(CXX) $(CXXFLAGS) -L./build -o $@ $^

build/repl.o: src/repl.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Tests

build/present-test: $(C_OBJECTS) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -L./build -o $@ $^

# Shared libraries

shared: build_dir build/libpresent.so

build/libpresent.so: $(C_OBJECTS)
	$(libpresent_COMPILER) $(libpresent_FLAGS) $(LIBRARY_FLAGS) -o $@ $^

.PHONY: shared

# Static libraries

static: build_dir build/libpresent.a

build/libpresent.a: $(C_OBJECTS)
	ar rcs $@ $^

.PHONY: static

# Individual object files

build/%.c.o: src/%.c include/present/%.h include/present/internal/present-%-data.h $(UTIL_HEADERS)
	$(libpresent_COMPILER) $(libpresent_FLAGS) $(LIBRARY_OBJECT_FLAGS) -c $< -o $@

build/utils/%.c.o: src/utils/%.c $(UTIL_HEADERS)
	$(libpresent_COMPILER) $(libpresent_FLAGS) $(LIBRARY_OBJECT_FLAGS) -c $< -o $@

# Cleanup

clean: clean-o clean-so clean-a clean-bin

clean-o:
	rm -f build/*.o build/utils/*.o

clean-so:
	rm -f build/*.so

clean-a:
	rm -f build/*.a

clean-bin:
	rm -f build/present-repl build/present-test

.PHONY: clean clean-o clean-so clean-a clean-bin

