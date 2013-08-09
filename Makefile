all: container_test

container_test: container
	$(CXX) -Wall -O2 -o container_test.o -c container_test.cpp
	$(CXX) -Wall -O2 -o container_test container_test.o container.o

container:
	$(CXX) -Wall -O2 -o container.o -c container.cpp

clean:
	rm -rf container.o container_test.o container_test container_test.exe
