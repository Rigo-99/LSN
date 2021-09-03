rm results/out*

cp input_1.solid input_1.dat
./es07_1.exe
mv results/output.epot.0 results/output.epot.solid.NVT
mv results/output.pres.0 results/output.pres.solid.NVT
mv results/output.gave.0 results/output.gave.solid.NVT
mv results/output.gofr.0 results/output.gofr.solid.NVT


cp input_1.liquid input_1.dat
./es07_1.exe
mv results/output.epot.0 results/output.epot.liquid.NVT
mv results/output.pres.0 results/output.pres.liquid.NVT
mv results/output.gave.0 results/output.gave.liquid.NVT
mv results/output.gofr.0 results/output.gofr.liquid.NVT


cp input_1.gas input_1.dat
./es07_1.exe
mv results/output.epot.0 results/output.epot.gas.NVT
mv results/output.pres.0 results/output.pres.gas.NVT
mv results/output.gave.0 results/output.gave.gas.NVT
mv results/output.gofr.0 results/output.gofr.gas.NVT



################################################################

cp input_2.solid input_2.dat
./es07_2.exe 6 300 0 0
./es07_2.exe 0 1 1 200
mv results/output_epot_blocchi.dat results/output.epot.solid.MD
mv results/output_etot_blocchi.dat results/output.etot.solid.MD
mv results/output_ekin_blocchi.dat results/output.ekin.solid.MD
mv results/output_temp_blocchi.dat results/output.temp.solid.MD
mv results/output_gave.dat results/output.gave.solid.MD
mv results/output_gofr.dat results/output.gofr.solid.MD


cp input_2.liquid input_2.dat
./es07_2.exe 6 300 0 0
./es07_2.exe 0 1 1 200
mv results/output_epot_blocchi.dat results/output.epot.liquid.MD
mv results/output_etot_blocchi.dat results/output.etot.liquid.MD
mv results/output_ekin_blocchi.dat results/output.ekin.liquid.MD
mv results/output_temp_blocchi.dat results/output.temp.liquid.MD
mv results/output_gave.dat results/output.gave.liquid.MD
mv results/output_gofr.dat results/output.gofr.liquid.MD


cp input_2.gas input_2.dat
./es07_2.exe 6 300 0 0
./es07_2.exe 0 1 1 200
mv results/output_epot_blocchi.dat results/output.epot.gas.MD
mv results/output_etot_blocchi.dat results/output.etot.gas.MD
mv results/output_ekin_blocchi.dat results/output.ekin.gas.MD
mv results/output_temp_blocchi.dat results/output.temp.gas.MD
mv results/output_gave.dat results/output.gave.gas.MD
mv results/output_gofr.dat results/output.gofr.gas.MD
