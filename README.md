# PHILOSOPHERS
## Table of Contents
- [About](#about)
- [Usage](#usage)
- [Compilation](#compilation)
- [Key Concepts Learned](#key-concepts-learned)
- [Skills Developed](#skills-developed)
- [Technical Implementation](#technical-implementation)
- [The Dining Philosophers Problem](#the-dining-philosophers-problem)
- [42 School Standards](#42-school-standards)
- [Related Articles](#-related-articles)
- [Contact](#contact)

## About
This repository contains my implementation of the **philosophers** project at 42 School.
Philosophers is a classic concurrent programming project that simulates the famous "Dining Philosophers Problem" using threads and mutexes.
The project introduces fundamental concepts of multithreading, synchronization, and concurrent programming while avoiding deadlocks and race conditions.

**The Challenge:**
Multiple philosophers sit around a circular table with bowls of spaghetti. There are as many forks as philosophers, placed between each pair.
To eat, a philosopher needs both forks adjacent to them. The challenge is to coordinate their actions without causing deadlocks or starvation.


## Usage
The program simulates the dining philosophers problem with customizable parameters:

```bash
# Basic usage
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

# Examples
./philo 5 800 200 200
./philo 4 310 200 100
./philo 5 800 200 200 7
```

**Arguments:**
- `number_of_philosophers`: Number of philosophers (and forks) around the table
- `time_to_die`: Time in milliseconds before a philosopher dies from starvation
- `time_to_eat`: Time in milliseconds a philosopher spends eating
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat` (optional): Program stops when all philosophers have eaten at least this many times

**Output Format:**
```bash
[timestamp_in_ms] [philosopher_id] has taken a fork
[timestamp_in_ms] [philosopher_id] is eating
[timestamp_in_ms] [philosopher_id] is sleeping
[timestamp_in_ms] [philosopher_id] is thinking
[timestamp_in_ms] [philosopher_id] died
```


## Compilation
The project follows standard 42 compilation practices:

```bash
# Compile with Makefile
make

# Clean object files
make clean

# Clean everything
make fclean

# Recompile
make re
```

**Compilation flags:** `-Wall -Wextra -Werror -pthread`


## Key Concepts Learned

### Multithreading Fundamentals
- **POSIX Threads (pthreads)**: Creating and managing multiple threads of execution
- **Thread Lifecycle**: Understanding thread creation, execution, and termination
- **Concurrent Execution**: Managing simultaneous operations in shared memory space
- **Thread Synchronization**: Coordinating thread actions to prevent conflicts

### Synchronization Mechanisms
- **Mutexes (Mutual Exclusion)**: Protecting shared resources from concurrent access
- **Deadlock Prevention**: Implementing strategies to avoid circular waiting conditions
- **Race Condition Handling**: Ensuring thread-safe operations on shared data
- **Critical Sections**: Identifying and protecting code sections that access shared resources

### Time Management
- **Precise Timing**: Using `gettimeofday()` for accurate timestamp calculations
- **Thread Timing**: Implementing `usleep()` for controlled delays
- **Starvation Detection**: Monitoring time since last meal to detect philosopher death
- **Real-time Simulation**: Maintaining accurate timing in concurrent environment

## Skills Developed

- **Concurrent Programming**: Mastery of multithreaded application development
- **Synchronization Design**: Implementing thread-safe algorithms and data structures
- **Deadlock Prevention**: Understanding and applying deadlock avoidance strategies
- **Resource Management**: Efficient allocation and sharing of limited resources (forks)
- **Performance Optimization**: Minimizing thread contention and maximizing throughput
- **Debugging Multithreaded Code**: Identifying and resolving thread-related issues
- **System Programming**: Working with POSIX threads and system timing functions
- **Algorithm Design**: Solving complex synchronization problems elegantly


## Technical Implementation

### Core Architecture

**Main Data in Structures:**
```c
typedef struct s_data
{
	long		      	nb_phil;
	long		      	time_die;
	long		      	time_eat;
	long		      	time_sleep;
	long		      	mandatory_meals;
	long	      		start_time;
	unsigned int    end_simulation;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	time_eat_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	end_mutex;
	t_phil			    *s_phil;
	pthread_t		    monitoring;
}				        	t_data;

typedef struct s_phil
{
	int				      id;
	pthread_t	      th_id;
	long			      last_meal;
	unsigned int    total_meal;
	int				      full;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	t_data			    *s_data;
}					        t_phil;
```

**Main Components:**
1. **Initialization**: Setup philosophers, forks (mutexes), and shared data
2. **Thread Creation**: Spawn one thread per philosopher
3. **Philosopher Routine**: Eternal loop of thinking, eating, sleeping
4. **Monitoring Thread**: Checks for death conditions and meal completion
5. **Cleanup**: Proper destruction of mutexes and thread joining

### Deadlock Prevention Strategy

**Approach Used:** Resource hierarchy solution
- Philosophers with even IDs pick up left fork first, then right fork
- Philosophers with odd IDs pick up right fork first, then left fork
- This breaks the circular wait condition that causes deadlocks

### Critical Timing Functions
- **get_current_time()**: Returns current time in milliseconds
- **ft_usleep()**: Precise sleeping function for timing control
- **time_since_last_meal()**: Calculates elapsed time since philosopher's last meal
- **print_status()**: Thread-safe status printing with mutex protection


## The Dining Philosophers Problem

### Problem Description
The Dining Philosophers Problem is a classic synchronization problem in computer science that illustrates the challenges of coordinating access to shared resources in concurrent systems.

**Scenario:**
- N philosophers sit around a circular table
- Each philosopher alternates between thinking, eating, and sleeping
- There are N forks placed between philosophers
- A philosopher needs both adjacent forks to eat
- Deadlock can occur when each philosopher holds one fork and waits for another

**Challenges to Solve:**
- **Deadlock**: All philosophers holding one fork and waiting for another
- **Race Conditions**: Multiple threads accessing shared resources simultaneously
- **Starvation**: A philosopher never getting both forks and eventually dying
- **Data Races**: Unsynchronized access to shared variables

### Solution Approach
Using mutexes to represent each fork, philosophers must acquire mutexes for both needed forks before eating. The implementation includes:

- Mutex-protected fork access
- Ordered fork acquisition to prevent deadlocks
- Death monitoring in separate thread
- Thread-safe status reporting
- Precise timing for all operations


## 42 School Standards

### Norm Requirements
- ✅ Maximum 25 lines per function
- ✅ Maximum 5 functions per file
- ✅ Proper indentation and formatting
- ✅ No forbidden functions usage
- ✅ Compilation without warnings

### Coding Standards
- ✅ No data races (tested with thread sanitizer)
- ✅ No memory leaks (checked with valgrind)
- ✅ Proper mutex initialization and destruction
- ✅ Thread-safe operations on all shared data
- ✅ Accurate timing and death detection
- ✅ Clean program termination and resource cleanup

### Authorized Functions
- `memset`, `printf`, `malloc`, `free`, `write`
- `usleep`, `gettimeofday`
- `pthread_create`, `pthread_detach`, `pthread_join`
- `pthread_mutex_init`, `pthread_mutex_destroy`
- `pthread_mutex_lock`, `pthread_mutex_unlock`

### Performance Requirements
- ✅ No philosopher should die (unless intended)
- ✅ Philosophers should not starve
- ✅ Simulation should run smoothly without delays
- ✅ Death should be detected within 10ms of occurrence
- ✅ Program should handle edge cases (1 philosopher, etc.)


## 📝 Related Articles

Blog posts documenting the learning process and context behind this project:

- 📝 [42 Piscine and Common Core: What I Learned](https://arthurbernard.dev/en/blog/42-piscine-and-core-curriculum) — Reflections on 42 School's selection process and 2-year curriculum

---
## Contact
- **GitHub**: [@TuroTheReal](https://github.com/TuroTheReal)
- **Email**: arthurbernard.dev@gmail.com
- **LinkedIn**: [Arthur Bernard](https://www.linkedin.com/in/arthurbernard92/)

---
<p align="center">
  <img src="https://img.shields.io/badge/Made%20with-C-blue.svg"/>
  <img src="https://img.shields.io/badge/Threads-POSIX-green.svg"/>
</p>
