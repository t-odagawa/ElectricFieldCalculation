filename=./data/electric_field_3_$1.txt
if [ -f "${filename}" ];then
    rm -f ${filename}
fi
touch ${filename}
for i in `seq 0 29`;do
    cat data/electric_field_3_$1_${i}.txt >> ${filename}
done
