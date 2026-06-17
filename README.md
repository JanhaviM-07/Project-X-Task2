# Project-X-Task2

Name: JANHAVI ATUL MAHAJAN<br>
Branch:IT<br>
Mail id: jamahajan_b25@it.vjti.ac.in<br>


To build a CPU task scheduler and memory cache simulator in C++ :
Task Scheduler is to be created so that it schedules task one another and so that it can further that memory location is to be found  in cache if not present then fetch from RAM .If the task is completed before quantum then it moves to next task else that task is moved to end of queue of tasks. Burst time is total time or rather total cycles needed by task to get completed whereas remaining time is :- burst time-quantum.
Then all tasks are served at once then the tasks who have remaining time are executed for same quantum. And this process continues but gives every task equal and fair chance to get completed.<br>
I used ifstream and stringstream to read input file line-by-line.In Round Robin Algorithm during each running cycle, the current task requests a memory block using a safe circular wrapping sequence (idx % size)
As per task memory hierarchy has 3 cache levels and RAM L1,L2,L3. Each level is a fixed-size queue - when it's full, the oldest entry gets evicted (FIFO). Then the code searches each memory location in cache if present then its hit, if not found then it is a miss , then it is accessed from RAM and it replaces the last used task or location from cache.<br><br>

This repository consists of My solution.cpp code file that has solution for task 2 in C++.<br>
And the Input task2.txt file which is read in code and tasks are performed accordingly..
