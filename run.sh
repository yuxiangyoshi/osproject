for NTH in 1 2 4 8 16
do
	echo $NTH processes cpu
	time ./processes/clientProcesses localhost 8888 $NTH cpu
	echo " "
done

for NTH in 1 2 4 8 16
do
	echo $NTH processes balanced
	time ./processes/clientProcesses localhost 8888 $NTH balanced
	echo " "
done

for NTH in 1 2 4 8 16
do
	echo $NTH processes io
	time ./processes/clientProcesses localhost 8888 $NTH io
	echo " "
done

for NTH in 2 4 8 16
do
	echo $NTH threads cpu
	time ./threads/clientThreads localhost 8888 $NTH cpu
	echo " "
done

for NTH in 2 4 8 16
do
	echo $NTH threads balanced
	time ./threads/clientThreads localhost 8888 $NTH balanced
	echo " "
done

for NTH in 2 4 8 16
do
	echo $NTH threads io
	time ./threads/clientThreads localhost 8888 $NTH io
	echo " "
done