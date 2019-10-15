# DeadlockAvoidance 

//Almicke Navarro 
//CST221 
//October 7, 2019 
//This is my own work. 

//Link to GitHub: https://github.com/MickeyNavarro/DeadlockAvoidance

Description of the Program: There are two processes called Producer and Consumer. The Producer will produce items  to a buffer whereas the Consumer will consume items from the buffer(shared resource). The buffer will have a mutex, which is a lock that only allows access when it is called to be unlocked, and a monitor, which is a data type that only allows one process to acces the buffer at a time. When the Producer is called, the mutex will be unlocked and the monitor will be set to full. The Producer will produce items until the buffer is full. Once the buffer is full, the producer will go to sleep. During this, the Consumer will try to access the buffer, however, it cannot due to the monitor being in use. Instead of the prcoess failing and ending in a deadlock, a timer will be started to tell the Consumer to wait and try again. When the timer is finished (100 ticks), the Producer will be finished and the monitor will be set to full (meaning the buffer is full of products). The Consumer will then be able to access the buffer and consume the items.

Analysis Q's: After analyzing the activity log produced by your program, assess how efficient was the use of a timer to solve deadlock situations. Is the solution scalable to multiple processes and threads? What are the limitations, if any? If you identified problems with this strategy, suggest a different approach and explain why it would be better. If the timer proves to be a successful approach, just state that and no further alternatives need to be explored.

Analysis Answers: Timers are a very efficient tool when there is a deadlock. The timer allows certain process to wait for their turn before running. I think the solution is scalable to multiple process and threads. Some limitations would be that the timer may not contain the right amount of set time to allow the producer to run. The process may run longer than expected and so the timer may not be correct. A better approach may be just calling the next process within the other process to make sure that the first process is done. However, not every program will be that simple. I think there are a multitude of ways to a good solution, but it all depends on the actual program and how the solution is coded. 
