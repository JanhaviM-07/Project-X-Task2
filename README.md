# Project-X-Task2

Name: JANHAVI ATUL MAHAJAN<br>
Branch:IT<br>
Mail id: jamahajan_b25@it.vjti.ac.in<br>

  <u><b>Approach:</b></u><br>
To build a CPU task scheduler and memory cache simulator in C++ :

Task Scheduler is to be created so that it schedules task one another and so that it can further that memory location is to be found  in cache if not present then fetch from RAM .If the task is completed before quantum then it moves to next task else that task is moved to end of queue of tasks. Burst time is total time needed by task whereas remaining time is burst time -quantum.
Then all tasks are served at once then the tasks who have remaining time are executed for same quantum. And this process continues but gives every task equal and fair chance to get completed.<br>
I used ifstream and stringstream to read input file line-by-line.In Round Robin Algorithm during each running cycle, the current task requests a memory block using a safe circular wrapping sequence (idx % size)

As per task memory hierarchy has 3 cache levels and RAM L1,L2,L3. Each level is a fixed-size queue - when it's full, the oldest entry gets evicted (FIFO). Then the code searches each memory location in cache if present then its hit, if not found then it is a miss , then it is accessed from RAM and it replaces the last used task or location from cache.

<u><b>Algorithm:</b></u><br>
I have used <b>Round Robin Algorithm</b> to build a task manager. Because its working is like at first it allows all tasks to be attended by cpu according to FIFO queue for a certain period of time for each task called quantum.And hence completes all tasks perfectly and systematically<br>
I didn't choose <b>FCFs Algorithm</b> because it is First Come First serve basis and hence if any important task is to be done and it is among the last tasks then it would get delayed.<br>
Also I didn't approach for <b>SJFs Algorithm</b> because they are Shortest Jobs First and hence shortest jobs are completed first neglecting Large ones.<br>

<b>Explanation:</b><br>

 The no. of cycles task needs to finish is burstTime, and its  list of memory blocks is memReq. memoryRequest(): When a task is running, it grabs its next memory item using idx % memReq.size().  If a task has a long burstTime for eg.5 but only has 3 memory blocks (M1, M2, M3), the modulo operator '%' forces it to loop back and ask for M1 and M2 again instead of crashing out of bounds.class cache: This is a storage shelf. It tracks its size limit is capacity, how slow it is latency, and contains a vector named slots to hold memory blocks.The FIFO Eviction Strategy insert() When a new block arrives, if the cache shelf is full  it executes slots.erase(slots.begin()). This discards  the oldest block on the shelf. The new block is then added cleanly to the back of the line via push_back(block). 
 <br>
In blockAccess() code, whenever an item hits in L2, L3, or is fetched from RAM,  program immediately triggers l1.insert(block). The simulator class controls everything using a Round Robin scheduling queue.It takes the first task out of the queue and pops it off the line. It figures out how long this task is allowed to run during this turn using min(quantum, currTask.remainTime). With a quantum of 3, a task with 5 cycles left gets to run for 3 cycles. A task with only 1 cycle left gets to run for 1 cycle.The task executes its assigned steps. Once its 3-cycle time slice expires, the engine checks if the task is completely finished i.e if remainTime > 0, it means the task still needs more CPU attention. The engine pushes it right back to the end of the ready queue so it waits its turn again.If remainTime == 0, the task is finished.
<br>
<br>
<img width="600" height="400" alt="WhatsApp Image 2026-06-15 at 20 18 48" src="https://github.com/user-attachments/assets/edc02156-11b1-4bdb-a0d4-3d1a13a9523f" />
<br>
<br>

The simulator reads the input text file. And performs these tasks accordingly.Since the simulator clock automatically loops forward by '1' cycle for raw processing time, memory lookup stall delays are adjusted smoothly into the master clock by totalCycles += (penalty - 1).

<b>Performance:</b><br>
According to input file it has less than 32 memory locations and hence after miss the memory gets stored at L1 and L2, L3 remain empty always.<br>

<b>The Time complexity of this solution is:</b>
<br>
loadTask function :  O(L * W), where L is the number of lines in the file and W is the average number of words per line.<br><br>
ispresent function: In the worst-case, it is O(C), where C is the maximum capacity of the cache layer.<br><br>
insert function : The time complexity is O(C), because both ispresent and, in the worst-case, erase(slots.begin()) are linearly dependent on the cache capacity C.<br><br>
roundRobin function: The overall time complexity of the simulation is roughly O(B * M * C), where B is the sum of burst times of all tasks, M is the maximum number of memory requests a task makes, and C is the largest cache capacity. This is due to repetitive continuous cache lookups and displaying operations at every cycle step.
