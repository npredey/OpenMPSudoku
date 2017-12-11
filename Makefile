default:
	g++ -fopenmp -I. -g -o parallel parallel.cpp my_timer.cpp 

clean:
	rm -rf parallel *.o *~ *.*~
