# Task 11 – Recommend and Defend the Operating-System Plan

## 1. Introduction

The smart hospital requires different operating-system capabilities because its environments have different workloads and performance requirements. Bedside monitors require predictable response times, while workstations, database servers and MRI systems require multitasking, security and efficient resource management.

Therefore, a **hybrid operating-system architecture** is recommended instead of using the same operating system throughout the hospital.

## 2. Recommended Operating-System Plan

| Environment | Recommended OS | OS Type and Structure | Justification |
|---|---|---|---|
| Bedside patient monitors | Real-Time Operating System (RTOS) | Real-time, typically using a modular or microkernel-based design | Provides predictable scheduling and fast response to critical patient alarms. |
| Nurses' tablets | Android / iOS | Mobile operating system | Supports wireless communication, touch interfaces, mobility and power management. |
| Doctors' workstations | Linux / Windows | General-purpose operating system with a modular or hybrid kernel | Supports multitasking, graphical applications and access to electronic health records. |
| Central patient-record database | Linux Server OS | Multi-user, multitasking server OS with a modular monolithic kernel | Provides stability, networking, access control, database services and server management. |
| MRI processing server | Linux Server OS | Multiprocessor operating system supporting symmetric multiprocessing (SMP) | Supports parallel processing and efficient utilisation of multiple processors. |
| Inter-hospital communication | Linux-based network services | Distributed-system architecture | Supports secure communication and patient-record exchange between hospitals. |

The final choice of RTOS, mobile platform and server distribution should be based on hardware compatibility, vendor support, security updates and clinical certification requirements.

## 3. OS Services, Protection and I/O Methods

### Process Management

- The RTOS should use priority-based scheduling so that critical alarm-handling tasks receive priority.
- Workstations and servers should support multitasking to execute multiple applications simultaneously.
- Multiprocessor scheduling should be used by the MRI server to distribute processing tasks across available CPU cores.

### Memory Management

- Memory protection should prevent one process from accessing another process's memory.
- Virtual memory can be used by general-purpose operating systems to manage available memory efficiently.
- Critical monitor software should use predictable memory allocation and avoid unnecessary dynamic allocation during time-sensitive operations.

### Security and Protection

- User authentication should be required before accessing hospital systems.
- Role-based access control should ensure that nurses, doctors and administrators have appropriate permissions.
- Encryption should protect patient information during storage and transmission.
- Audit logs should record access to sensitive patient records.
- Process isolation and memory protection should reduce the impact of application failures.

### I/O Management

- Interrupt-driven I/O should be used for time-sensitive events from bedside monitoring devices.
- Device drivers should manage communication with monitors, MRI equipment, printers and other peripherals.
- Buffered I/O should be used for bulk file transfers and database operations where appropriate.
- Network I/O should use secure communication protocols for transferring patient information between departments and hospitals.

## 4. Limitations and Risks

| Risk / Limitation | Possible Impact | Mitigation |
|---|---|---|
| RTOS implementation complexity | Requires specialised development and testing | Use validated RTOS platforms and thorough testing. |
| Network failure | Interrupts communication between hospital systems | Provide redundant network connections and local operation. |
| Database failure | Patient records may become temporarily unavailable | Use database replication, backups and failover mechanisms. |
| Cybersecurity threats | Patient data may be exposed or modified | Apply encryption, access control, security updates and monitoring. |
| Multiple operating systems | Increases maintenance and compatibility requirements | Establish standard configurations and centralised management. |
| Hardware failure | Can interrupt critical services | Use redundant hardware and disaster-recovery procedures. |

## 5. Suitability for a Three-Hospital Group

The proposed architecture remains suitable when the hospital expands into a group of three hospitals.

Each hospital can maintain its own local bedside monitoring, clinical workstations and essential services. The hospitals can communicate through secure networks and share patient records using controlled data exchange.

The following measures are required:

1. **Database replication:** Maintain replicated patient records so that information remains available if one database server fails.
2. **Secure communication:** Use encrypted connections between hospitals to protect patient information.
3. **Access management:** Apply consistent authentication and role-based access policies across all locations.
4. **Fault tolerance:** Maintain local services so that a network failure does not completely stop hospital operations.
5. **Backup and recovery:** Maintain regular backups and disaster-recovery arrangements.
6. **Scalability:** Add computing, storage and network resources as the number of users and patient records increases.

With these measures, the proposed hybrid architecture can support the expansion from one hospital to a three-hospital group.

## 6. Alternative: Virtualising the Entire System on Two Large Servers

An alternative is to run the hospital's operating systems as virtual machines (VMs) on two large physical servers using a hypervisor.

Each VM would run an appropriate guest operating system. For example, separate VMs could host database services, application servers and administrative systems. In theory, monitor-related workloads could also run in VMs, but this introduces additional timing and reliability concerns.

### Evaluation of Virtualisation

| Factor | Effect of Virtualisation |
|---|---|
| Monitor response time | Hypervisor scheduling and virtual I/O can introduce additional latency and unpredictable delays. This may affect the strict 10 ms alarm-response requirement. |
| Memory usage | Each VM requires memory for its guest OS, applications and virtual devices, increasing memory overhead. |
| Processor usage | Hypervisor operations, VM scheduling and virtual device handling consume CPU resources. |
| Reliability | Failure of one physical server can affect multiple VMs running on it. |
| Scalability | VMs can be created, resized and migrated more easily than separate physical systems. |
| Cost | Server consolidation can reduce hardware and maintenance costs. |

### Advantages

- Reduces the number of physical machines required.
- Allows multiple operating systems to run on the same hardware.
- Simplifies deployment, management and resource allocation.
- Supports VM backup, migration and recovery.
- Improves hardware utilisation when workloads do not continuously require all available resources.

### Disadvantages

- Virtualisation introduces CPU, memory and I/O overhead.
- Resource contention between VMs can affect performance.
- Hypervisor failure can affect multiple hospital services.
- Two physical servers can still represent a single point of failure if redundancy and failover are not properly configured.
- Strict real-time deadlines are harder to guarantee without specialised real-time virtualisation and hardware configuration.

### Recommendation for the Virtualised Alternative

A fully virtualised design on only two large servers is not recommended for all hospital environments. Bedside monitors should preferably remain on dedicated physical devices running a suitable RTOS to provide predictable response times.

Virtualisation can be used for non-real-time services such as application servers, administrative systems, database replicas and supporting services. The two hosts should be configured for redundancy, with sufficient reserved CPU and memory resources.

## 7. Evidence from Previous Analysis and Measurements

The recommendation is supported by the practical measurements performed in Task 10.

### System Call Measurements

| Buffer Size | Total Read and Write Calls |
|---:|---:|
| 1 byte | 131,077 |
| 512 bytes | 261 |
| 4096 bytes | 37 |

The experiment demonstrated that increasing the buffer size significantly reduces system-call frequency. This supports the use of appropriate buffering for bulk data transfer and non-time-critical I/O operations.

### Process and Thread Creation Measurements

| Measurement | Average Elapsed Time |
|---|---:|
| Creation of 1,000 processes | 0.202371 seconds |
| Creation of 1,000 threads | 0.123565 seconds |

The thread benchmark was approximately 39% faster than the process benchmark in the tested environment. This supports the observation that threads can have lower creation overhead when tasks need to share resources.

These results are specific to the tested WSL environment and benchmark programs. They do not directly measure RTOS response time, hospital network latency or virtualisation overhead. Therefore, the 10 ms monitor deadline must be validated separately through real-time testing under worst-case operating conditions.

## 8. Final Recommendation

A hybrid operating-system architecture is the most appropriate solution for the smart hospital.

- RTOS should be used for bedside monitors to handle deadline-sensitive patient alarms.
- Mobile operating systems should support nurses' tablets.
- General-purpose operating systems should be used for doctors' workstations.
- Linux Server OS should support central patient-record databases and MRI processing.
- Secure distributed services should connect the three hospitals and support patient-record sharing.

Virtualisation should be adopted selectively for non-real-time workloads rather than replacing every dedicated system. Critical monitor devices should remain on suitable dedicated hardware, while redundant virtualised servers can improve resource utilisation for supporting hospital services.

This plan balances **real-time performance, security, reliability, scalability and resource efficiency**, making it suitable for the current hospital and its planned expansion into a three-hospital group.