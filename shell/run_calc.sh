for i in `seq 0 20`;do
    ncell=`expr 600 + ${i} \* 60`
    # ncell should be 60 * N (N:integer)
    ./calc_elec 3 ${ncell}
done
