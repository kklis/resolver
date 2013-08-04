all:
	$(CXX) -O2 -o container_test container_test.cpp
clean:
	rm -rf container_test
