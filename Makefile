LINK_TARGET = bin/c_compiler
CC = g++
CPPFLAGS += -std=c++17 -W -Wall -g #-Wno-unused-parameter
CPPFLAGS += -I include -I src
HPPFILES = $(wildcard include/ast/*.hpp) include/ast.hpp
CPPFILES = $(wildcard src/*.cpp)
OBJS = $(patsubst %.cpp,%.o,$(CPPFILES))
all : $(LINK_TARGET)
$(LINK_TARGET) : src/lexer.yy.o src/parser.tab.o $(OBJS)
	$(CC) $(CPPFLAGS) $^ -o $@
src/%.o: src/%.cpp $(HPPFILES)
	$(CC) $(CPPFLAGS) -c -o $@ $<
src/parser.tab.cpp src/parser.tab.hpp: src/parser.y
	yacc -v -d src/parser.y -o src/parser.tab.cpp
	mkdir -p bin;
src/lexer.yy.cpp : src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp src/lexer.flex
makeobj:
	$(CC) $(CPPFLAGS) src/$(CPPALLTEST) -o bin/testout
lexer: src/lexer.yy.cpp
parser: src/parser.tab.cpp src/parser.tab.hpp
bin/compiler: src/c_compiler.output


.PHONY: clean
clean :
	rm -rf bin/*
	rm -f src/*.tab.hpp
	rm -f src/*.tab.cpp
	rm -f src/*.yy.cpp
	rm -f src/*.output
	rm -f src/*.o
