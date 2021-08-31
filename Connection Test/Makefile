FILE := Server
override CXXFLAGS += -lpthread -Wpedantic -Wall -Wextra -Wsign-conversion -Wconversion -std=c++2a -Isrc -IuSockets/src
override LDFLAGS += uSockets/*.o -lz

DESTDIR ?=
prefix ?= /usr/local

.PHONY: examples
examples:
	$(MAKE) -C uSockets; \
	$(CXX) -flto -O3 $(CXXFLAGS) ./Server.cpp -o Server $(LDFLAGS) ; \
	wait

install:
	mkdir -p "$(DESTDIR)$(prefix)/include/uWebSockets"
	cp -r src/* "$(DESTDIR)$(prefix)/include/uWebSockets"

all:
	$(MAKE) examples
	
clean:
	rm -rf $(FILE) 
	rm -rf fuzzing/*.o benchmarks/*.o
