# sifra

man tcgetattr/tcsetattr

gcc -Wall -g sifra1|2.c -o sifra1|2

valgrind --tool=memcheck --leak-check=yes ./sifra1|2
