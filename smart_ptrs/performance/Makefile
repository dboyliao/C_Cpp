N=100000;

all:
	@make with_new
	@make with_make
	time ./with_new $(N);
	time ./with_make $(N);

with_new: with_new.cpp
	@g++ -o with_new with_new.cpp -std=c++11 -Wall;

with_make: with_make.cpp
	@g++ -o with_make with_make.cpp -std=c++11 -Wall;

clean:
	rm -f with_new with_make;
