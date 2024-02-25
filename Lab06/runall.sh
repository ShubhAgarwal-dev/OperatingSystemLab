#!/bin/bash

echo 'Compiling...'
g++ -pthread ./part1.cpp -o ./transformer
g++ -pthread ./part2_1_a.cpp -o ./transformer_2_1_a
g++ -pthread ./part2_1_b.cpp -o ./transformer_2_1_b
g++ -pthread ./part2_2.cpp -o ./transformer_2_2
g++ -pthread ./part2_3.cpp -o ./transformer_2_3
echo 'Compiled....'
echo '--------------------'

echo "Part1"
echo "5MB"
time ./transformer ./inputs_ppm/sample_pp3_5mb.ppm ./output_ppm/sample_pp3_5mb_verify.ppm
echo ''
echo "8MB"
time ./transformer ./inputs_ppm/sample_pp3_8mb.ppm ./output_ppm/sample_pp3_8mb_verify.ppm
echo ''
echo "25MB"
time ./transformer ./inputs_ppm/sample_pp3_25mb.ppm ./output_ppm/sample_pp3_25mb_verify.ppm
echo ''
echo "73MB"
time ./transformer ./inputs_ppm/sample_pp3_73mb.ppm ./output_ppm/sample_pp3_73mb_verify.ppm
echo '--------------------'

echo "Part2-1-a"
echo "5MB"
time ./transformer_2_1_a ./inputs_ppm/sample_pp3_5mb.ppm ./output_ppm/sample_pp3_5mb.ppm
diff -q ./output_ppm/sample_pp3_5mb.ppm ./output_ppm/sample_pp3_5mb_verify.ppm
echo ''
echo "8MB"
time ./transformer_2_1_a ./inputs_ppm/sample_pp3_8mb.ppm ./output_ppm/sample_pp3_8mb.ppm
diff -q ./output_ppm/sample_pp3_8mb.ppm ./output_ppm/sample_pp3_8mb_verify.ppm
echo ''
echo "25MB"
time ./transformer_2_1_a ./inputs_ppm/sample_pp3_25mb.ppm ./output_ppm/sample_pp3_25mb.ppm
diff -q ./output_ppm/sample_pp3_25mb.ppm ./output_ppm/sample_pp3_25mb_verify.ppm
echo ''
echo "73MB"
time ./transformer_2_1_a ./inputs_ppm/sample_pp3_73mb.ppm ./output_ppm/sample_pp3_73mb.ppm
diff -q ./output_ppm/sample_pp3_73mb.ppm ./output_ppm/sample_pp3_73mb_verify.ppm
echo '--------------------'

echo "Part2-1-b"
echo "5MB"
time ./transformer_2_1_b ./inputs_ppm/sample_pp3_5mb.ppm ./output_ppm/sample_pp3_5mb.ppm
diff -q ./output_ppm/sample_pp3_5mb.ppm ./output_ppm/sample_pp3_5mb_verify.ppm
echo ''
echo "8MB"
time ./transformer_2_1_b ./inputs_ppm/sample_pp3_8mb.ppm ./output_ppm/sample_pp3_8mb.ppm
diff -q ./output_ppm/sample_pp3_8mb.ppm ./output_ppm/sample_pp3_8mb_verify.ppm
echo ''
echo "25MB"
time ./transformer_2_1_b ./inputs_ppm/sample_pp3_25mb.ppm ./output_ppm/sample_pp3_25mb.ppm
diff -q ./output_ppm/sample_pp3_25mb.ppm ./output_ppm/sample_pp3_25mb_verify.ppm
echo ''
echo "73MB"
time ./transformer_2_1_b ./inputs_ppm/sample_pp3_73mb.ppm ./output_ppm/sample_pp3_73mb.ppm
diff -q ./output_ppm/sample_pp3_73mb.ppm ./output_ppm/sample_pp3_73mb_verify.ppm
echo '--------------------'

echo "Part2-2"
echo "5MB"
time ./transformer_2_2 ./inputs_ppm/sample_pp3_5mb.ppm ./output_ppm/sample_pp3_5mb.ppm
diff -q ./output_ppm/sample_pp3_5mb.ppm ./output_ppm/sample_pp3_5mb_verify.ppm
echo ''
echo "8MB"
time ./transformer_2_2 ./inputs_ppm/sample_pp3_8mb.ppm ./output_ppm/sample_pp3_8mb.ppm
diff -q ./output_ppm/sample_pp3_8mb.ppm ./output_ppm/sample_pp3_8mb_verify.ppm
echo ''
echo "25MB"
time ./transformer_2_2 ./inputs_ppm/sample_pp3_25mb.ppm ./output_ppm/sample_pp3_25mb.ppm
diff -q ./output_ppm/sample_pp3_25mb.ppm ./output_ppm/sample_pp3_25mb_verify.ppm
echo ''
echo "73MB"
time ./transformer_2_2 ./inputs_ppm/sample_pp3_73mb.ppm ./output_ppm/sample_pp3_73mb.ppm
diff -q ./output_ppm/sample_pp3_73mb.ppm ./output_ppm/sample_pp3_73mb_verify.ppm
echo '--------------------'

echo "Part2-3"
echo "5MB"
time ./transformer_2_3 ./inputs_ppm/sample_pp3_5mb.ppm ./output_ppm/sample_pp3_5mb.ppm
diff -q ./output_ppm/sample_pp3_5mb.ppm ./output_ppm/sample_pp3_5mb_verify.ppm
echo ''
echo "8MB"
time ./transformer_2_3 ./inputs_ppm/sample_pp3_8mb.ppm ./output_ppm/sample_pp3_8mb.ppm
diff -q ./output_ppm/sample_pp3_8mb.ppm ./output_ppm/sample_pp3_8mb_verify.ppm
echo ''
echo "25MB"
time ./transformer_2_3 ./inputs_ppm/sample_pp3_25mb.ppm ./output_ppm/sample_pp3_25mb.ppm
diff -q ./output_ppm/sample_pp3_25mb.ppm ./output_ppm/sample_pp3_25mb_verify.ppm
echo ''
echo "73MB"
time ./transformer_2_3 ./inputs_ppm/sample_pp3_73mb.ppm ./output_ppm/sample_pp3_73mb.ppm
diff -q ./output_ppm/sample_pp3_73mb.ppm ./output_ppm/sample_pp3_73mb_verify.ppm
echo '--------------------'

rm transformer transformer_2_1_a transformer_2_1_b transformer_2_2 transformer_2_3;