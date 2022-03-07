.PHONY: clean

CXXFLAGS += \
	-std=c++11 \
	-Iinclude \
	-pedantic-errors \
	-Wall \
	-Wextra \
	-Weffc++

test: main.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -o build/$@ $^

run: test
	build/$<

clean:
	$(RM) build/test
