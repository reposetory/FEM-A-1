# engnfinal
class project
team members: Zhi Li Helena Liu YunXing Su

Overview:
This project aimed at providing a convenient PDE solver for the sake of demonstrating different PDE algorithms.
Five different algorithms are implemented both in 1D and 2D. Users could specify the solver algorithm and time step, space step,
total time through QT input interface.

Build and Running instructions:

All the build steps are summarized in the bash script "run.sh". So simply submit the job in CCV using  "sbatch run.sh" with x11 or VNC.
Then input the desired parameters through QT interface.

In case bash script doesn't work in VNC. The build steps are :
(1) generate the makefile for c++ codes with "cmake CMakeLists.txt"
(2) compile the c++ codes with "make". A executable program named main is generated
(3) go to folder "QT", compile QT project with
    qmake -project
    qmake
    make
(4) run QT interface with "./QT" two txt file named num_threads and parameters will be generated
(5) go back to the main folder and run the main program with "./main"
