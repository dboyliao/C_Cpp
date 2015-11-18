rm -f webserver
gcc -Wall -g webserver.c -o webserver -lpthread `pkg-config --cflags gtk+-2.0` \
`pkg-config --libs gtk+-2.0`
