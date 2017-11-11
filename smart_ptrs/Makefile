all:
	@make shared_basic weak_basic

shared_basic: thing.cpp shared_basic.cpp
	g++ -o $@ $^ -std=c++11 -Wall

weak_basic: thing.cpp weak_basic.cpp
	g++ -o $@ $^ -std=c++11 -Wall

unique_basic: thing.cpp unique_basic.cpp
	g++ -o $@ $^ -std=c++11 -Wall

.PHONY: clean
clean:
	rm -f shared_basic weak_basic unique_basic
