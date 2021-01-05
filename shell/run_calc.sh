for i in `seq 0 10`;do
    ncell=`expr 1000 + ${i} \* 100`
    ./calc_elec 3 ${ncell}
#   echo ${ncell}
done
