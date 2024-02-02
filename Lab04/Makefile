CC=clang++

build1: SJF.cpp
	${CC} -o sjf SJF.cpp utils.cpp

build2: RR.cpp
	${CC} -o rr RR.cpp utils.cpp

testbuild1: clear1 build1
	./sjf tests/process1.dat

testbuild2:
	./rr tests/process1.dat

build: build1 build2

clear1:
	rm sjf

clear2:
	rm rr
