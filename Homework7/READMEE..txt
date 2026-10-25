This project implements two CPU scheduling algorithms: First Come First Served (FCFS) and Shortest Job First (SJF).
The program asks the user to enter the arrival time and burst time for each process. It calculates waiting time, turnaround time, and response time. It also displays a Gantt chart and the average times for both algorithms.
FCFS runs processes in arrival order. SJF chooses the shortest available process. Both algorithms are non-preemptive.

How to Compile
 gcc hardhomeworkscheduling.c -o hardhomeworkscheduling

How to Run
 ./hardhomeworkscheduling