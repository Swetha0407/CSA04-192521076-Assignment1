# Task 1 – Evaluate the Requirements of Each Computing Environment

## 1. Introduction

A smart hospital consists of multiple computing environments that work together to provide patient care, manage medical information and support hospital operations. These environments include bedside patient monitors, nurses' handheld tablets, doctors' desktop workstations, a central patient-record database, an MRI imaging server and communication systems connecting partner hospitals.

Each environment has different operating-system requirements depending on its workload, hardware capabilities and importance to hospital operations. For example, a bedside monitor must generate an alarm within 10 milliseconds, whereas an MRI server must process large volumes of image data efficiently.

The major requirements considered in this evaluation are response time, reliability, throughput, battery efficiency and security.

## 2. Ranked Requirements

The following table ranks the importance of each requirement for the different computing environments. Rank 1 indicates the highest priority.

| Environment | Response Time | Reliability | Throughput | Battery Efficiency | Security |
|---|---:|---:|---:|---:|---:|
| Bedside Monitors | 1 | 2 | 4 | 5 | 3 |
| Nurses' Tablets | 3 | 2 | 4 | 1 | 5 |
| Doctors' Workstations | 3 | 2 | 4 | N/A | 1 |
| Patient Database | 3 | 1 | 4 | N/A | 2 |
| MRI Imaging Server | 3 | 2 | 1 | N/A | 4 |
| Partner-Hospital Network | 3 | 2 | 4 | N/A | 1 |

*Note: These rankings represent the proposed design priorities. Security remains essential in every environment, even where it is not ranked first.*

### 2.1 Bedside Patient Monitors

- **Response Time (Priority 1):** The monitors must process sensor readings and generate alarms within 10 milliseconds when abnormal conditions are detected. Delayed alarms could prevent medical staff from responding to emergencies on time.
- **Reliability (Priority 2):** Monitoring must continue without unexpected interruptions because even a short failure could result in important patient readings being missed.
- **Security (Priority 3):** Patient readings must be protected from unauthorized access or modification.
- **Throughput (Priority 4):** The monitor processes a continuous stream of sensor data, but predictable processing is more important than handling a large volume of unrelated tasks.
- **Battery Efficiency (Priority 5):** Power consumption should be minimized, particularly for portable monitors, without affecting critical monitoring operations.

A Real-Time Operating System (RTOS) is a suitable choice because it supports predictable task scheduling and prioritization. Critical alarm-processing tasks can receive higher priority than routine activities such as data logging.

### 2.2 Nurses' Handheld Tablets

- **Battery Efficiency (Priority 1):** Tablets should operate throughout nurses' shifts without frequent charging.
- **Reliability (Priority 2):** Nurses must be able to access and update patient information consistently.
- **Response Time (Priority 3):** Applications should respond quickly when retrieving records or receiving notifications.
- **Throughput (Priority 4):** The device mainly handles interactive applications, wireless communication and moderate data transfers.
- **Security (Priority 5):** Authentication and access control are necessary to protect confidential patient information.

A mobile operating system is appropriate because it provides power management, wireless connectivity, application management and a touch-based interface. Security remains mandatory even though battery efficiency is the primary design priority.

### 2.3 Doctors' Desktop Workstations

- **Security (Priority 1):** Workstations provide access to confidential medical records, reports and patient histories. Unauthorized access must be prevented.
- **Reliability (Priority 2):** Doctors require consistent access to medical applications during diagnosis and treatment.
- **Response Time (Priority 3):** Applications should retrieve records and display reports without unnecessary delays.
- **Throughput (Priority 4):** The system should support multiple applications and simultaneous data transfers.
- **Battery Efficiency:** Not a major requirement because desktop workstations generally use a continuous power supply.

A general-purpose desktop operating system is suitable because it supports multitasking, user authentication, file management, networking and a graphical user interface. Role-based permissions can restrict access according to the responsibilities of individual hospital staff.

### 2.4 Central Patient-Record Database

- **Reliability (Priority 1):** The database must remain continuously available because doctors and nurses depend on it for patient information.
- **Security (Priority 2):** Patient records must be protected against unauthorized access, modification and data loss.
- **Response Time (Priority 3):** Records should be retrieved quickly when requested by hospital applications.
- **Throughput (Priority 4):** The server must handle multiple read and write requests from different departments.
- **Battery Efficiency:** Not applicable because the server operates using a continuous power supply.

A server operating system should provide efficient process scheduling, memory management, storage management and network communication. Backup and recovery mechanisms are also necessary to reduce downtime. Since the assignment requires the database to remain available, a clustered architecture can be evaluated as a fault-tolerance solution in the following tasks.

### 2.5 MRI Imaging Server

- **Throughput (Priority 1):** MRI image processing involves large datasets and computationally intensive operations. The server must process these workloads efficiently.
- **Reliability (Priority 2):** Medical images must be processed and stored correctly without data corruption.
- **Response Time (Priority 3):** Doctors should receive processed images without excessive waiting.
- **Security (Priority 4):** Imaging data contains confidential patient information and must be protected.
- **Battery Efficiency:** Not applicable to a continuously powered imaging server.

A multiprocessor-capable operating system is suitable because processing tasks can be distributed across multiple CPUs. Parallel execution can improve processing throughput, while efficient memory and I/O management support the handling of large imaging datasets.

### 2.6 Communication with Partner Hospitals

- **Security (Priority 1):** Patient information exchanged between hospitals must be protected through authentication and encryption.
- **Reliability (Priority 2):** Communication should remain available so authorized hospitals can exchange medical records.
- **Response Time (Priority 3):** Records should be transferred without unnecessary delays.
- **Throughput (Priority 4):** The network must support multiple communication requests and data transfers.
- **Battery Efficiency:** Not a major requirement for the hospital communication infrastructure.

The operating system and network infrastructure must support secure communication, access control and reliable data transfer. Communication failures should be detected and handled without compromising patient information.

## 3. Conflicts Between Requirements

Different operating-system requirements can compete with one another. The design must balance these conflicts according to the importance of each hospital environment.

- **Response Time vs Throughput:** Giving priority to an emergency alarm may delay routine tasks such as logging sensor readings. In bedside monitors, meeting the alarm deadline is more important than maximizing overall throughput.
- **Battery Efficiency vs Performance:** Reducing processor activity can improve tablet battery life, but excessive power-saving measures may delay notifications or application responses.
- **Security vs Response Time:** Authentication and encryption introduce additional processing overhead. However, these mechanisms cannot be removed because patient information must remain protected.
- **Reliability vs Cost:** Backup servers, redundant storage and failover mechanisms improve availability but increase hardware costs and maintenance effort.

The operating system must balance these requirements without compromising critical patient-care operations.

## 4. Patient Safety-Critical Requirements

Patient safety is the most important consideration in the hospital's operating-system design.

The bedside monitoring system has a strict timing requirement: an abnormal reading must trigger an alarm within 10 milliseconds. Meeting the average response time is not sufficient; the system must also be evaluated under worst-case conditions to determine whether the deadline can consistently be satisfied.

The database server is equally important to overall hospital operations because its failure could prevent medical staff from retrieving essential patient records.

The following requirements are therefore critical:

- **Deadline compliance:** Bedside monitors must satisfy the 10 ms alarm requirement.
- **Continuous operation:** Patient monitoring should not be interrupted by unnecessary system failures.
- **Data integrity:** Medical records must remain accurate and consistent.
- **Availability:** Essential patient information must remain accessible.
- **Protection:** Only authorized personnel should access or modify patient information.

A failure in any of these areas could affect medical decisions and patient care. Therefore, reliability and security must be considered throughout the design rather than treated as optional features.

## 5. Evolution of Operating Systems

Operating systems have evolved to support changing computing requirements.

| OS Type | Characteristics | Hospital Relevance |
|---|---|---|
| Batch OS | Executes groups of jobs without continuous user interaction. | Useful for scheduled report generation, but unsuitable for emergency alarms. |
| Time-Sharing OS | Allows multiple users and processes to share computing resources. | Useful for interactive hospital applications and shared systems. |
| Personal Computer OS | Provides graphical interfaces, file management and application support. | Suitable for doctors' desktop workstations. |
| Mobile OS | Supports portability, wireless communication and power management. | Suitable for nurses' handheld tablets. |

This evolution demonstrates why different computing environments require different operating-system capabilities. A system designed for batch processing cannot automatically satisfy the timing requirements of a real-time monitoring device.

## 6. Alternative Evaluation: One General-Purpose OS Everywhere

One alternative is to install the same general-purpose operating system on all hospital devices.

This approach could simplify software installation, maintenance and administration. However, it may not satisfy the specialized requirements of every environment.

| Factor | Single General-Purpose OS | Specialized OS Design |
|---|---|---|
| Alarm Response | No automatic guarantee of a 10 ms deadline. | RTOS supports predictable scheduling. |
| Memory Usage | May introduce unnecessary overhead on embedded devices. | Can be selected according to device resources. |
| Performance | Designed for general workloads. | Optimized for specific workloads. |
| Administration | Easier to standardize and maintain. | Requires managing multiple platforms. |
| Flexibility | Less suitable for specialized hardware requirements. | Better suited to different environments. |

**Worst-case alarm delay:** A general-purpose OS may schedule background tasks, handle interrupts or execute other processes before the alarm task. This can introduce unpredictable delays. An RTOS is designed to provide more predictable scheduling, although the complete monitor system must still be tested to prove that it meets the 10 ms deadline.

**Memory requirements:** A full general-purpose OS may consume unnecessary memory on small bedside devices. A lightweight RTOS can reduce operating-system overhead, while servers can use larger operating systems designed for their workloads.

**Administration effort:** A single OS reduces the number of platforms administrators need to maintain. However, specialized operating systems provide better control over performance and resource usage. The additional maintenance effort is justified by the different requirements and patient-safety implications.

## 7. Conclusion

A smart hospital cannot efficiently depend on one general-purpose operating system for every computing environment. Bedside monitors prioritize predictable response time, database servers prioritize reliability, MRI servers prioritize throughput, and handheld tablets prioritize battery efficiency.

A combination of real-time, mobile, desktop and server operating-system approaches provides a better balance of performance, reliability, security and resource utilization.

The recommended design should be validated through testing, particularly for the 10 ms alarm deadline and database availability. This ensures that the operating-system choices support both hospital operations and patient safety.