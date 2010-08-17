
all: compile

configure:
	mkdir build
	(cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..)
	
compile:
	make -C build
	
run:
	(./build/bin/demo -i examples/logo.png examples/Demo.js)
	
test:
	(cd build/bin && ./unit_test)
	
clean:
	make -C build clean
	
distclean:
	(rm -rf build)