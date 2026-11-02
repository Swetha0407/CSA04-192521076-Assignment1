# Task 10 – Measure and Compare

## Objective

To measure and compare the behaviour of system calls, CPU time, process creation and thread creation in Linux. The experiments use `strace` and `/usr/bin/time` to observe system-call counts, execution time and memory usage.

## Environment

- Operating System: Ubuntu on WSL
- Compiler: GCC
- Programming Language: C
- Tools: `strace`, `/usr/bin/time`
- Number of processes tested: 1,000
- Number of threads tested: 1,000

## 1. System Call Comparison Using `strace`

The file-copy program was executed using different buffer sizes to observe how buffer size affects the number of `read()` and `write()` system calls.

**Commands:**

```bash
strace -c -e trace=read,write ./copy_compare input.dat output_1.dat 1

strace -c -e trace=read,write ./copy_compare input.dat output_512.dat 512

strace -c -e trace=read,write ./copy_compare input.dat output_4096.dat 4096
```

### Results

| Buffer Size | Read Calls | Write Calls | Total Calls | Time |
|---:|---:|---:|---:|---:|
| 1 byte | 65,538 | 65,539 | 131,077 | 7.505311 s |
| 512 bytes | 130 | 131 | 261 | 0.011994 s |
| 4096 bytes | 18 | 19 | 37 | 0.002676 s |

### Observation

As the buffer size increases, the number of system calls decreases significantly. A 1-byte buffer requires many read and write operations, whereas a 4096-byte buffer completes the same 65,536-byte copy using far fewer calls.

This demonstrates that larger buffers reduce system-call overhead and improve file-copy performance. The counts shown include the traced read and write calls made during program execution, not just the data-transfer calls.

**Evidence – System Call Comparison**

![System call comparison using strace](../Evidence/Task10/1.system_call_comparison.png)

## 2. CPU Time Measurement

The `/usr/bin/time -v` command was used to measure the user-mode time, kernel-mode time and total elapsed time of the file-copy program.

**Command:**

```bash
/usr/bin/time -v ./copy_compare input.dat output_time.dat 4096
```

### Results

| Measurement | Result |
|---|---:|
| User time | 0.00 seconds |
| System time | 0.00 seconds |
| CPU utilization | 14% |
| Elapsed wall-clock time | 0.01 seconds |
| Maximum resident set size | 1,792 KB |
| Exit status | 0 |

### Observation

User time represents the time spent executing instructions in user mode, while system time represents the time spent executing kernel operations. Both values were displayed as 0.00 seconds because the file-copy operation was very short and the timer rounded the results.

The program completed successfully with an elapsed time of approximately 0.01 seconds.

**Evidence – CPU Time Measurement**

![CPU time measurement using time](../Evidence/Task10/2.cpu_time_measurement.png)

## 3. Process Creation Benchmark

A C program using `fork()` was executed to create 1,000 processes. The parent process waited for the child processes to finish using `waitpid()`.

**Command:**

```bash
/usr/bin/time -v ./process_benchmark
```

### Results

The benchmark was executed three times.

| Run | Program Elapsed Time | User CPU Time | System CPU Time | Maximum RSS |
|---:|---:|---:|---:|---:|
| 1 | 0.177490 s | 0.19 s | 0.18 s | 1,792 KB |
| 2 | 0.224971 s | 0.21 s | 0.24 s | 1,792 KB |
| 3 | 0.204651 s | 0.20 s | 0.21 s | 1,792 KB |
| **Average** | **0.202371 s** | **0.20 s** | **0.21 s** | — |

### Observation

The program successfully created 1,000 processes. The average measured elapsed time was approximately 0.202 seconds.

Process creation involves creating a separate process with its own virtual address space and process-related resources. Linux uses copy-on-write during `fork()`, which avoids immediately copying all the parent's memory pages.

**Evidence – Process Benchmark**

![Process creation benchmark](../Evidence/Task10/3.process_benchmark.png)

## 4. Thread Creation Benchmark

A C program using `pthread_create()` was executed to create 1,000 threads. The main thread waited for all worker threads to finish using `pthread_join()`.

**Command:**

```bash
/usr/bin/time -v ./thread_benchmark
```

### Results

The benchmark was executed three times.

| Run | Program Elapsed Time | User CPU Time | System CPU Time | Maximum RSS |
|---:|---:|---:|---:|---:|
| 1 | 0.142828 s | 0.00 s | 0.13 s | 9,216 KB |
| 2 | 0.110978 s | 0.00 s | 0.11 s | 9,472 KB |
| 3 | 0.116890 s | 0.00 s | 0.11 s | 9,344 KB |
| **Average** | **0.123565 s** | **0.00 s** | **0.12 s** | — |

### Observation

The program successfully created 1,000 threads. The average measured elapsed time was approximately 0.124 seconds.

Threads share the same process address space and resources, but each thread has its own stack, registers and thread-local storage. This generally makes thread creation less expensive than creating separate processes.

**Evidence – Thread Benchmark**

![Thread creation benchmark](../Evidence/Task10/4.thread_benchmark.png)

## 5. Process and Thread Comparison

| Parameter | Processes | Threads |
|---|---|---|
| Creation mechanism | `fork()` | `pthread_create()` |
| Address space | Separate virtual address spaces | Shared address space |
| Memory sharing | Copy-on-write after `fork()` | Shares code, data and heap |
| Stack | Separate process stack | Separate stack per thread |
| Communication | Requires inter-process communication mechanisms | Can communicate through shared memory |
| Creation overhead | Generally higher | Generally lower |
| Measured average elapsed time | 0.202371 s | 0.123565 s |

### Analysis

In this experiment, creating 1,000 threads took approximately 0.124 seconds, while creating 1,000 processes took approximately 0.202 seconds.

The thread benchmark was approximately 39% faster than the process benchmark in this particular test.

The measured maximum resident set size was 1,792 KB for the process benchmark and 9,472 KB for the thread benchmark. These values represent the peak memory reported for each complete benchmark command. They should not be interpreted as the memory required by an individual process or thread because memory accounting, thread stacks, runtime overhead and the execution environment affect the measurement.

## 6. Complexity and Design Evaluation

Both benchmarks perform 1,000 creation operations. Therefore, the number of creation operations grows linearly with the number of processes or threads, giving an \(O(n)\) number of creation operations for \(n\) workers.

However, their resource requirements differ:

- **Processes:** Each process has its own virtual address space and process-related resources. Copy-on-write reduces the need to immediately duplicate memory during `fork()`.
- **Threads:** Threads share the process address space, code, global data and heap. Each thread still requires its own stack and thread-specific execution state.

Threads are generally suitable when tasks need frequent communication and shared data. Processes provide stronger isolation because each has a separate address space.

## 7. Comparison with Earlier Judgements

The measurements support the expectation that larger file-copy buffers reduce system-call overhead. The 4096-byte buffer required only 37 traced calls compared with 131,077 calls for the 1-byte buffer.

The process and thread benchmarks also support the expectation that threads can be created faster than processes for a simple workload. In this experiment, the thread benchmark completed approximately 39% faster.

The results are specific to this WSL environment and this benchmark implementation. Actual performance can vary with system load, hardware, kernel implementation and workload.

## Conclusion

The experiments demonstrated how buffer size affects system-call frequency and file-copy performance. They also provided practical measurements of user-mode time, kernel-mode time, process creation and thread creation.

The results showed that larger buffers reduce system-call overhead and that threads were faster to create than processes in the tested workload. The comparison also highlighted the differences in memory sharing, resource management and isolation between processes and threads.