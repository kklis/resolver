CXXFLAGS = -Wall -O2

all: resolver_test

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: resolver_test
	./resolver_test

resolver_test: resolver.o

clean:
	rm -rf resolver.o resolver_test.o resolver_test
