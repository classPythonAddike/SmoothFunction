build:
	@gcc -o main *.c -lm

run: build
	@./main

graph:
	gnuplot -e "set grid; plot 'normal.dat' with linespoint lw 1 ps 0 pt 5" -p
	gnuplot -e "set grid; plot 'noisy.dat' with  linespoint lw 1 ps 0 pt 5" -p
	gnuplot -e "set grid; plot 'smooth.dat' with  linespoint lw 1 ps 0 pt 5" -p
