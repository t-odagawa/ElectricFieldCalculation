mergefilename=./data/electric_field_3_$1.txt
if [ -f "${mergefilename}" ];then
    rm -f ${mergefilename}
fi
touch ${mergefilename}

for i in `seq 0 29`;do
    filename=./data/electric_field_3_$1_${i}.txt
    cat ${filename} >> ${mergefilename}
    rm -f ${filename}
done
