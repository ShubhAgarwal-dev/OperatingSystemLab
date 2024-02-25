CC=g++

exec:
	${CC} part1.cpp -o part1
	${CC} part2_1_a.cpp -o part2 -pthread
	${CC} part2_2.cpp -o part2_2
	${CC} part2_3.cpp -o part2_3

test:
	${CC} part2_2.cpp -o part1 -pthread && time ./part1 inputs_ppm/sample_pp3_5mb.ppm output_ppm/sample5_22