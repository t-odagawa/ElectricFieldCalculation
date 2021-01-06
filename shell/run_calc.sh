for i in `seq 0 20`;do
    for z in `seq 0 29`;do
	ncell=`expr 600 + ${i} \* 60`
	# ncell should be 60 * N (N:integer)
	bsub -q s ./calc_elec 3 ${ncell} ${z}
    done
done
