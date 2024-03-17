echo "Compiling..."

make clean
make all

echo "Compiled!!!"

for executable in ./fifo ./lru ./random
do
	for file in req1.dat req2.dat req3.dat req4.dat req5.dat
	do
		for page in {1..80}
		do
			echo ${executable} "80" $page "80 ./access/"${file} ">> ./"${executable}_dir"/"${file}".csv";
			# ${executable} 80 ${page} 80 ./access/${file} >> ./${executable}_dir/${file}.csv
		done
	done
done

