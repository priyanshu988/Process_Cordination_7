# Problems on Process Coordination

## QUESTION 1 - LIFE ON A CHIP

### Execution :
- Compile : 
```
gcc Q1.c
```
- Run : 
```
./a.out <No of H atoms> <No of O atoms> <No of sites> <Threshold Energy(in Units)>
```

### Implementation details :
- pthread_t is used to create a thread for each of the operable sites, which in turn creates 3 threads : 2 for hydrogen atoms and and 1 for oxygen atom.
- pthread_mutex_t is used to lock and unlock critical section, providing functionality of signal() and wait() in order to ensure mutual exclusion.
	
### Functions created :
- update_Oxygen() - Called by oxygen atom thread to update the count of oxygen atoms when they participate in molecule formation.
- update_Hydrogen() - Called by hydrogen atom thread to update the count of hydrogen atoms when they participate in molecule formation.
- reaction() - This function creates hydrogen and oxygen threads and joins these threads when all atom threads required for a reaction is available. Determines the site number on which reaction will be performed and performs reaction in sleep(3) time.

***
	  		
## QUESTION 2 - GHAC OLD BRIDGE TRIP

### Execution :
- Compile: 
```
gcc Q2.c
```
- Run: 
```
./a.out <#of geeks> <#of non-geeks> <#of singers>
```

### Implementation Details : 
- Thread Implementation : 
  - pthread : to create thread for each geek, non-geek and singer

### Functions created: 
- GeekArrives(): If constraints to cross the bridge are satisfied, updates the count of geeks and calls crossed_bridge().
- NonGeekArrives(): If constraints to cross the bridge are satisfied, updates the count of non geeks and calls crossed_bridge().
- SingerArrives() : If constraints to cross the bridge are satisfied, updates the count of singers and calls crossed_bridge().

***	
	
## QUESTION 3 - COURSES ALLOCATION ALOGORITHM

### Execution :
- Compile: 
```
g++ Q3.cpp -lpthread
```
- Run: 
```
./a.out <#of students> <#of courses>
```
 
### Implementation : 
- Data structures used : 
	- bitmap - to ensure the ratio of student category
	- vector - to store the courses for each knowledge stream
	- array - to store preference list and allocation list

- Thread Implementation : 
	- pthreads to create thread for each student.

### Functions :
- studentAllocation() : allocates courses to students, if given constraints are satisfied.
- printToFile() : Writes information about the remaining seats of every stream is into the allocation.txt
	 
*** 


