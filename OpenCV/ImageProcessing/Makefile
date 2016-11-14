CXX_FLAGS=`pkg-config --libs --cflags opencv`

%:%.cpp
	g++ $(CXX_FLAGS) $< -o $@

.PHONY: clean

clean:
	ls | grep -v *.cpp | grep -v Makefile | grep -v *.jpg | grep -v *.png | xargs rm -rf 
