#!/bin/bash

./clean.sh

cp input.1 input.dat

./es04_1.exe 0 1 0 0
./salva.sh 1
./clean.sh

./es04_1.exe 9 500 0 0
./salva.sh 2
./clean.sh
./q_save.sh

./w_load.sh
./es04_1.exe 0 1 1 100
./salva.sh 3
./clean.sh

cp input.2 input.dat

./w_load.sh
./es04_1.exe 1 1 1 0
./salva.sh 4
./clean.sh

./w_load.sh
./es04_1.exe 9 500 1 0
./salva.sh 5
./clean.sh


rm results/*_blocchi_1.dat
rm results/*_blocchi_2.dat
rm results/*_blocchi_4.dat
rm results/*_blocchi_5.dat


cp input.solid.eq input.dat
./es04_1.exe 20 300 0 0
./salva.sh 10
./q_save.sh
./clean.sh

cp input.solid input.dat
./w_load.sh
./es04_1.exe 0 1 1 300
./salva.sh 11
./clean.sh

cp input.liquid.eq input.dat
./es04_1.exe 40 400 0 0
./salva.sh 20
./q_save.sh
./clean.sh

cp input.liquid input.dat
./w_load.sh
./es04_1.exe 0 1 1 800
./salva.sh 21
./clean.sh

cp input.gas.eq input.dat
./es04_1.exe 50 500 0 0
./salva.sh 30
./q_save.sh
./clean.sh

cp input.gas input.dat
./w_load.sh
./es04_1.exe 0 1 1 5000
./salva.sh 31
./clean.sh
