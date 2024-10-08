all:
	g++ -Wall -Werror -Wextra salaryHandler.cpp main.cpp -o ./start.out

rebuild: clean all
	./start.out
clean:
	rm -rf *.o
	clear
