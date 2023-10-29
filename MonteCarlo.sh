echo "Thread test in progress..."
echo "Size;Threads;Time" > MonteCarloOMP.csv

for i in {1..10}; do
    echo "Running iteration $i"
    for t in 2 4 8 16 32; do
        export OMP_NUM_THREADS=$t
        for j in 100000 1000000 10000000 100000000 1000000000 10000000000; do
            result=$(./MonteCarloOMP $j)
            echo "$j;$t;$result" >> MonteCarloOMP.csv
        done
    done
done

echo "" >> 'MonteCarloOMP.csv'
echo "done"