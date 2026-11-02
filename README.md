# CSA04-192521076-Assignment1

# Evaluate and Justify the Operating-System Design of a Smart Hospital

**Operating Systems Assignment – ITA0305**

## Student Details

| Detail | Information |
|---|---|
| Name | Swetha |
| Register Number | 192521076 |
| Subject | Operating Systems |
| Assignment | Evaluate and Justify the Operating-System Design of a Smart Hospital |
| Total Tasks | 12 |

## Project Overview

This repository contains the solutions for a 12-task Operating Systems assignment based on designing and evaluating an operating-system architecture for a smart hospital.

The hospital scenario includes bedside patient monitors, nurses' tablets, doctors' workstations, a central patient-record database, an MRI processing server and communication between partner hospitals.

The assignment progresses from analysing operating-system requirements to recommending a complete architecture and adapting it for remote patient monitoring and cloud-based records.

## Development Environment

| Component | Details |
|---|---|
| Operating System | Ubuntu on Windows Subsystem for Linux (WSL) |
| Programming Language | C |
| Compiler | GCC 15.2.0 |
| Version Control | Git 2.53.0 |
| System Architecture | x86-64 |
| Tools | GCC, Git, `strace`, `/usr/bin/time` |

To check the installed Ubuntu release:

```bash
lsb_release -ds
```

To verify the compiler and Git versions:

```bash
gcc --version
git --version
```

## Task Index

| Task | Topic | Description |
|---|---|---|
| Task 1 | Requirements Analysis | Identifies and evaluates the requirements of each hospital computing environment. |
| Task 2 | Types of Operating Systems | Examines different operating-system types and selects suitable systems for hospital environments. |
| Task 3 | Operating-System Structures | Compares OS structures and evaluates their suitability for different workloads. |
| Task 4 | Operating-System Services | Analyses essential OS services and justifies which services are required in each environment. |
| Task 5 | System Calls | Explores system calls and demonstrates how user programs interact with the operating-system kernel. |
| Task 6 | Cost of System Calls | Implements a C file-copy program and analyses the cost of system-call operations. |
| Task 7 | Process Control | Demonstrates process creation and control using C programming. |
| Task 8 | CPU States and Protection | Examines CPU execution states, privilege levels and protection mechanisms. |
| Task 9 | Memory Hierarchy and I/O | Analyses memory hierarchy and input/output management in operating systems. |
| Task 10 | Measure and Compare | Measures system-call frequency, CPU time, process creation and thread creation using Linux tools. |
| Task 11 | OS Recommendation and Justification | Recommends and defends a complete operating-system architecture for the smart hospital. |
| Task 12 | Re-evaluate and Adapt the Design | Adapts the original architecture for remote home monitoring and cloud-hosted patient records. |

## Repository Structure

```text
CSA04-192521076-Assignment1/
│
├── README.md
│
├── Task1/
├── Task2/
├── Task3/
├── Task4/
├── Task5/
├── Task6/
├── Task7/
├── Task8/
├── Task9/
│
├── Task10/
│   ├── Task10_Measurement_and_Performance_Analysis.md
│   ├── copy_compare.c
│   ├── process_benchmark.c
│   └── thread_benchmark.c
│
├── Task11/
│   └── hospital_architecture.md
│
├── Task12/
│   └── remote_monitoring_cloud_adaptation.md
│
└── Evidence/
    ├── Task1/
    ├── Task2/
    ├── Task3/
    ├── Task4/
    ├── Task5/
    ├── Task6/
    ├── Task7/
    ├── Task8/
    ├── Task9/
    └── Task10/
```

Each task folder contains its corresponding solution, programs or documentation. The `Evidence` directory contains screenshots and supporting practical evidence.

## Compilation and Execution

The C programs were compiled using GCC in the Ubuntu WSL environment.

### General Compilation

```bash
gcc -Wall -Wextra -O2 program.c -o program
```

For programs using POSIX threads:

```bash
gcc -Wall -Wextra -O2 program.c -o program -pthread
```

### Example: Task 10

Navigate to the Task 10 directory:

```bash
cd Task10
```

Compile the three programs:

```bash
gcc -Wall -Wextra -O2 copy_compare.c -o copy_compare

gcc -Wall -Wextra -O2 process_benchmark.c -o process_benchmark

gcc -Wall -Wextra -O2 thread_benchmark.c -o thread_benchmark -pthread
```

Run the file-copy program:

```bash
./copy_compare input.dat output.dat 4096
```

Run the process benchmark:

```bash
./process_benchmark
```

Run the thread benchmark:

```bash
./thread_benchmark
```

### Performance Measurement

System calls were analysed using:

```bash
strace -c -e trace=read,write ./copy_compare input.dat output.dat 4096
```

Execution time and resource usage were measured using:

```bash
/usr/bin/time -v ./copy_compare input.dat output.dat 4096
```

## Important Experimental Results – Task 10

The following measurements were obtained during practical execution in the WSL environment.

### System Call Comparison

| Buffer Size | Total Read and Write Calls |
|---:|---:|
| 1 byte | 131,077 |
| 512 bytes | 261 |
| 4096 bytes | 37 |

The experiment demonstrated that increasing the buffer size significantly reduces the number of system calls required for file copying.

### Process and Thread Comparison

| Operation | Average Elapsed Time |
|---|---:|
| Creation of 1,000 processes | 0.202371 seconds |
| Creation of 1,000 threads | 0.123565 seconds |

The thread benchmark was approximately 39% faster than the process benchmark in the tested environment.

These measurements are specific to the tested environment and benchmark implementations.

## Final Design Recommendation

The final hospital architecture follows a hybrid operating-system approach:

- **RTOS:** For bedside monitoring and time-critical alarm handling.
- **Embedded OS / RTOS:** For remote home monitoring devices.
- **Android / iOS:** For nurses' mobile devices.
- **Linux / Windows:** For doctors' workstations.
- **Linux Server OS:** For database and MRI processing services.
- **Cloud-based distributed services:** For secure patient-record sharing across partner hospitals.

The final design retains local processing for critical monitoring operations while extending the architecture to support secure remote monitoring, cloud storage, replication and distributed access.

## Conclusion

This assignment applies operating-system concepts to a practical smart hospital scenario. It covers operating-system requirements, structures, services, system calls, process management, memory management, I/O, performance measurements and architecture evaluation.

The final recommendation balances real-time performance, protection, reliability, scalability and resource utilisation. The adapted design also considers the additional requirements introduced by remote patient monitoring and cloud-based healthcare services.