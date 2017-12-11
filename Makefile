default:
	g++ -fopenmp -g -o parallel parallel.cpp 

clean:
	rm -rf parallel *.o *~ *.*~
