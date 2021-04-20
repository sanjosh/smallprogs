
for i in {0..1000}
do
    eval "array=({0..${i}})"
    for j in "${array[@]}"
    do
        #echo $i $j
        ./a.out $j $i
    done
done

