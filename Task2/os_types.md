# Task 2 – Judge the Type of Operating System for Each Environment

## 1. Introduction

A smart hospital contains different computing environments, and each environment has different processing and availability requirements. A single operating-system type may not be suitable for every device.

The hospital requires real-time responses from bedside monitors, battery efficiency from nurses' tablets, interactive applications for doctors, high availability for the patient database, parallel processing for MRI images and communication between partner hospitals.

Therefore, the operating-system type must be selected according to the purpose and requirements of each environment.

## 2. Comparison of Operating-System Types

| OS Type | Description | Suitable Application |
|---|---|---|
| Mainframe OS | Supports large-scale transaction processing and many users. | Centralized enterprise processing. |
| Desktop OS | Designed for interactive personal-computer use. | Doctors' workstations. |
| Multiprocessor OS | Manages a system containing multiple processors or cores. | MRI imaging and database workloads. |
| Distributed OS / System | Coordinates multiple networked computers and allows resource sharing. | Communication between hospitals. |
| Clustered System | Connects multiple independent servers to provide availability and failover. | Patient-record database. |
| Hard Real-Time OS | Must complete critical tasks within specified deadlines. | Bedside patient monitors. |
| Soft Real-Time OS | Deadlines are important, but occasional delays reduce performance rather than causing immediate system failure. | Non-critical imaging or multimedia tasks. |
| Handheld OS | Designed for portable devices with limited battery and hardware resources. | Nurses' tablets. |

## 3. Recommended OS Type for Each Hospital Environment

| Hospital Environment | Recommended OS Type | Justification |
|---|---|---|
| Bedside Patient Monitors | Hard Real-Time OS | Must process abnormal readings and raise alarms within 10 milliseconds. |
| Nurses' Tablets | Handheld OS | Requires battery efficiency, portability, wireless communication and a touch interface. |
| Doctors' Workstations | Desktop OS | Supports interactive clinical applications, multitasking and user management. |
| Patient-Record Database | Clustered System | Provides failover and improves availability when one server fails. |
| MRI Imaging Server | Multiprocessor OS using SMP | Supports parallel processing of computationally intensive MRI workloads. |
| Partner-Hospital Link | Distributed System | Allows multiple hospitals to communicate and share patient records over a network. |

A multiprocessor system and a clustered system are different. A multiprocessor system contains multiple processors within one computer, whereas a cluster consists of multiple independent computers connected through a network. A database server can also use multiple processors internally while being part of a cluster.

## 4. Symmetric vs Asymmetric Multiprocessing for the MRI Server

Multiprocessing allows multiple processors to execute tasks within the same computer system.

### Symmetric Multiprocessing (SMP)

In SMP, all processors have equal responsibilities and share the main memory. The operating system distributes processes and threads among the available processors.

- All processors can execute operating-system and application tasks.
- Workloads can be distributed across multiple processors.
- It provides flexible processor utilization.
- It is suitable for parallel workloads such as MRI image processing.

### Asymmetric Multiprocessing (AMP)

In AMP, processors have assigned responsibilities. One processor may control the system while other processors execute specific tasks.

- Processors may have dedicated responsibilities.
- Task allocation is more controlled.
- It can be useful for fixed processing pipelines.
- It requires careful assignment and coordination of tasks.

### Comparison

| Factor | SMP | AMP |
|---|---|---|
| Processor roles | Equal responsibilities | Assigned responsibilities |
| Task allocation | Managed by the operating system | Based on predefined assignments |
| Load balancing | Generally easier | Depends on task assignment |
| Management | More flexible | Requires more coordination |
| MRI suitability | Suitable for general parallel processing | Useful for dedicated processing stages |

### Recommended Approach: SMP

SMP is recommended for the MRI imaging server because MRI processing involves computationally intensive tasks that can be divided among multiple processors. The operating system can distribute these tasks without requiring each task to be manually assigned to a particular processor.

AMP may be useful when the imaging system contains fixed processing stages that require dedicated processors. However, SMP provides more flexible processor utilization for a general-purpose imaging server.

## 5. Clustered Database Server with Failover

The patient-record database must remain highly available because doctors and nurses depend on it to access patient information.

A clustered database system uses multiple independent servers connected through a network. If the active server fails, another server can take over its responsibilities.

### Working of Failover

1. The active server handles database requests.
2. A standby server monitors the active server's health.
3. If the active server fails, the standby server detects the failure.
4. The standby server takes over the database service.
5. Applications reconnect to the available server.

A clustered system reduces dependence on a single machine. However, failover may take