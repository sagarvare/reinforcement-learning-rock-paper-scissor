all:
	g++ main.cpp helper.cpp
run:
	./a.out
clean:
	rm -f *.out
	rm -f *.txt
	rm -f *.dat
