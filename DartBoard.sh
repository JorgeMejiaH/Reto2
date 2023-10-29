echo "Thread test in progress..."
echo "Size;Threads;Time" > DartBoardOMP.csv

for i in {1..10}; do
    echo "Running iteration $i"
    for t in 2 4 8 16 32; do
        export OMP_NUM_THREADS=$t
        for j in 100000 1000000 10000000 100000000 1000000000 10000000000; do
            result=$(./DartBoardOMP $j)
            echo "$j;$t;$result" >> DartBoardOMP.csv
        done
    done
done

echo "" >> 'DartBoardOMP.csv'
echo "done"