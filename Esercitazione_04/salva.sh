#!/bin/bash

cp output_ekin.dat results/output_ekin_$1.dat
cp output_epot.dat results/output_epot_$1.dat
cp output_etot.dat results/output_etot_$1.dat
cp output_temp.dat results/output_temp_$1.dat

cp output_ekin_blocchi.dat results/output_ekin_blocchi_$1.dat
cp output_epot_blocchi.dat results/output_epot_blocchi_$1.dat
cp output_etot_blocchi.dat results/output_etot_blocchi_$1.dat
cp output_temp_blocchi.dat results/output_temp_blocchi_$1.dat

echo "Ricordati di fare ./clean.sh"
