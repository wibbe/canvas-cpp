
all: compile

configure:
	mkdir build
	(cd build && cmake ..)
	
compile:
	(cd build && make -j4)
	
run:
	(cd build/bin && ./demo)
	
test:
	(cd build/bin && ./unit_test)
	
clean:
	(cd build && make clean)
	
distclean:
	(rm -rf build)