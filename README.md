# engnfinal
class project
team members: Zhi Li Helena Liu YunXing Su

##Overview:
This project is aimed at providing a convenient PDE solver for the sake of demonstrating different PDE algorithms.
Five different algorithms are implemented both in 1D and 2D. Users could specify the solver algorithm and time step, space step,
total time through QT's graphical user input interface.

##Build and Running instructions:

All the build steps are executed automatically by the bash script "run.sh". To run this code, simply submit the job in CCV using  `sbatch run.sh` under visual mode settings, eg. x11 or VNC. We recommend using VNC. 

After the batch script passes queue, the QT interface should appear. Then, you can input the desired parameters through QT's interface. The program will automatically generate the output files. The output files include raw data in `.dat` files and animations in `.gif` files. The 1D data and visualization files are located in 
`/directory/output/1Doutput`
and the 2D data and visualization files are located in 
`/directory/output/2Doutput`
The `.gif` files can be opened with an image viewer such as a web browser. On VNC, they may be opened with `viewnior <filename.gif>`. If the `.gif` files do not open within VNC, they may be downloaded and opened locally with your web browser. 

##Manual Build Instructions: 
In case the bash script doesn't work in VNC, the build steps are :
1. Go to the main directory, `FEM-A` (if the name is not modified) and load requisite modules
    `module load gcc cmake mpich qt'
    `module unload gnuplot`
2. Generate the makefile 
    `cmake CMakeLists.txt`
3. Compile the C++ codes to get the executable called `main`
    `make`
4. Go to the folder `FEM-A/QT` and compile the project:
    `qmake -project`
    `qmake `
    `make`
5. Run the QT interface with `./QT`. Two `.txt` files named `num_threads.txt` and `parameters.txt` will be generated.
6. Return to the main folder (`FEM-A`) and run the main program executable:
    `cd ..`
    `./main`
7. QT will open, and you may select the options on its interface. It is not recommended to run QT on the login node of CCV, but for it should work for most cases.
8. Output files (raw data and animated videos) will be available in `FEM-A/output/` which can be viewed as described in the regular build instructions.
 
