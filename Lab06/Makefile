CC=g++

exec:
	${CC} part1.cpp -O3 -o part1
	${CC} part2_1_a.cpp -O3 -o part2_1_a -pthread
	${CC} part2_1_a.cpp -O3 -o part2_1_b -pthread
	${CC} part2_2.cpp -O3 -o part2_2
	${CC} part2_3.cpp -o part2_3

test:
	(./runall.sh 2>&1) | tee log

part1: exec
	time ./part1 inputs_ppm/sample_pp3_5mb.ppm output_ppm/output_part1_5mb.ppm
	time ./part1 inputs_ppm/sample_pp3_8mb.ppm output_ppm/output_part1_8mb.ppm
	time ./part1 inputs_ppm/sample_pp3_25mb.ppm output_ppm/output_part1_25mb.ppm
	time ./part1 inputs_ppm/sample_pp3_73mb.ppm output_ppm/output_part1_73mb.ppm
	make clean

part2_1a: exec
	time ./part2_1_a inputs_ppm/sample_pp3_5mb.ppm output_ppm/output_part2_1a_5mb.ppm
	time ./part2_1_a inputs_ppm/sample_pp3_8mb.ppm output_ppm/output_part2_1a_8mb.ppm
	time ./part2_1_a inputs_ppm/sample_pp3_25mb.ppm output_ppm/output_part2_1a_25mb.ppm
	time ./part2_1_a inputs_ppm/sample_pp3_73mb.ppm output_ppm/output_part2_1a_73mb.ppm
	make clean

part2_1b: exec
	time ./part2_1_b inputs_ppm/sample_pp3_5mb.ppm output_ppm/output_part2_1b_5mb.ppm
	time ./part2_1_b inputs_ppm/sample_pp3_8mb.ppm output_ppm/output_part2_1b_8mb.ppm
	time ./part2_1_b inputs_ppm/sample_pp3_25mb.ppm output_ppm/output_part2_1b_25mb.ppm
	time ./part2_1_b inputs_ppm/sample_pp3_73mb.ppm output_ppm/output_part2_1b_73mb.ppm
	make clean

part2_2: exec
	time ./part2_2 inputs_ppm/sample_pp3_5mb.ppm output_ppm/output_part2_2_5mb.ppm
	time ./part2_2 inputs_ppm/sample_pp3_8mb.ppm output_ppm/output_part2_2_8mb.ppm
	time ./part2_2 inputs_ppm/sample_pp3_25mb.ppm output_ppm/output_part2_2_25mb.ppm
	time ./part2_2 inputs_ppm/sample_pp3_73mb.ppm output_ppm/output_part2_2_73mb.ppm
	make clean

part2_3: exec
	time ./part2_3 inputs_ppm/sample_pp3_5mb.ppm output_ppm/output_part2_3_5mb.ppm
	time ./part2_3 inputs_ppm/sample_pp3_8mb.ppm output_ppm/output_part2_3_8mb.ppm
	time ./part2_3 inputs_ppm/sample_pp3_25mb.ppm output_ppm/output_part2_3_25mb.ppm
	time ./part2_3 inputs_ppm/sample_pp3_73mb.ppm output_ppm/output_part2_3_73mb.ppm
	make clean

clean:
	rm part1 part2_1_a part2_1_b part2_2 part2_3