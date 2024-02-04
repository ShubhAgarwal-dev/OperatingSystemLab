CC=clang++

build1: SJF.cpp
	${CC} -o sjf SJF.cpp utils.cpp

build2: RR.cpp
	${CC} -o rr RR.cpp

testbuild1: clear1 build1
	./sjf tests/process1.dat

testbuild2:
	./rr tests/process1.dat

build: build1 build2

run_test_sjf: build1
	./sjf tests/process1.dat > log1_sjf.log
	./sjf tests/process2.dat > log2_sjf.log
	./sjf tests/process3.dat > log3_sjf.log
	
run_test_rr: build2
	./rr tests/process1.dat > log1_rr.log
	./rr tests/process2.dat > log2_rr.log
	./rr tests/process3.dat > log3_rr.log

test: run_test_rr run_test_sjf

clear1:
	rm sjf

clear2:
	rm rr
	
clean:
	rm *.log sjf rr

