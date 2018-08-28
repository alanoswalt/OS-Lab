#!/bin/sh

F = 'Find /usr/src/ -type d -printf '%d\n' | sort -rn | head -1´
echo "----">> ~/Documents/lab/prueba.txt

echo $F
for i in ´seq 1 $F´;
do
          echo "This is level $i" >> ~/Documents/lab/prueba.txt
          echo ".c source code files level" >> ~/Documents/lab/prueba.txt
          find /usr/src/ -maxdepth $i -type f -name *[.c\] >> ~/Documents/lab/prueba.txt
          
          echo ".h heaer files" >> ~/Documents/tests/dir_tst.txt
          find /usr/src/ -maxdepth $i -type f -name *[.h\] >> ~/Documents/lab/prueba.txt
          echo $i
done
exit 0
