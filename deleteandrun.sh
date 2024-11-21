echo "argument is $1"
rm ./game;
gcc -Wall -std=c99 ./src/*.c `sdl2-config --libs --cflags` -lm -o game
./game $1;

