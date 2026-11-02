# Task 12 – Re-evaluate and Adapt the Design

## Introduction

The original smart hospital design used a hybrid operating-system architecture, with an RTOS for bedside monitors, mobile operating systems for nurses' tablets, general-purpose operating systems for doctors' workstations and Linux Server OS for central database and MRI processing services.

The new requirements introduce two major changes:

1. Remote monitoring devices in patients' homes send readings over the internet.
2. Patient records are moved to a cloud service shared with partner hospitals.

These changes introduce additional requirements for internet communication, remote device security, cloud availability, data privacy and distributed data management.

**Decision: MODIFY the original design.**

The existing hybrid architecture is suitable as a foundation, but it must be extended to support secure home monitoring and cloud-based patient records.

## A. Impact Analysis

The changed requirements affect the operating-system types, services and protection mechanisms in the original design.

### 1. Operating-System Impact

| Environment | Original Design | Impact of Changed Requirement |
|---|---|---|
| Hospital bedside monitors | RTOS | Retain the RTOS to provide predictable alarm handling and local monitoring. |
| Home monitoring devices | Not included | Introduce an embedded OS or RTOS depending on device capabilities and response-time requirements. |
| Nurses' tablets | Android / iOS | Retain the mobile OS and add secure access to remote monitoring information. |
| Doctors' workstations | Linux / Windows | Retain the general-purpose OS with secure access to cloud-hosted patient records. |
| Central patient-record database | Linux Server OS | Modify the architecture to use a cloud-hosted database service with backup, replication and access control. |
| Inter-hospital communication | Secure distributed network services | Extend it to support cloud-based record sharing and remote device communication. |

### 2. OS Services and Protection Mechanisms Affected

**Process and resource management:**
- Home monitoring devices must efficiently manage sensor readings, communication and background tasks.
- Critical monitoring tasks should receive appropriate scheduling priority.
- Cloud servers must support multiple hospitals and concurrent users.

**Memory management:**
- Home devices may have limited memory and processing capacity, so lightweight operating systems and efficient memory usage are important.
- Cloud services must allocate memory and computing resources according to workload requirements.

**Network and I/O management:**
- Home devices must collect sensor readings and transmit them securely over the internet.
- Network failures must not prevent local devices from collecting and temporarily storing readings.
- Cloud services must manage incoming data from multiple devices and hospitals.

**Security and protection:**
- Each home device should have a unique identity and secure authentication.
- Data should be encrypted during transmission and storage.
- Role-based access control should restrict access to patient records.
- Audit logs should record access and modifications.
- Secure updates should prevent unauthorised software changes to remote devices.

## B. Evaluation of the Original Design

The original design provides a good foundation, but it cannot be used without modifications because it was primarily designed around hospital-based systems.

### 1. Response Time

The original RTOS-based bedside monitoring system is suitable for time-critical alarm handling.

However, home monitoring introduces internet communication delays. Network congestion, routing delays and connectivity failures can affect how quickly readings reach the hospital.

Therefore, critical local alerts should be processed on the monitoring device itself rather than depending entirely on a cloud server.

### 2. Reliability

The original hospital architecture included local services and redundant database arrangements.

Moving records to the cloud can improve availability, scalability and backup capabilities. However, internet outages, cloud service failures and connectivity problems can interrupt access to remote readings and patient records.

Local buffering and reliable cloud synchronisation are necessary to reduce this risk.

### 3. Security

The original design already included authentication, role-based access control, encryption and audit logging.

However, internet-connected home devices increase the attack surface. Devices may be exposed to unauthorised access, insecure communication and compromised software.

Additional device authentication, secure communication, protected updates and continuous monitoring are required.

### Overall Evaluation

The original design can support the new requirements after modification. Its hybrid architecture remains appropriate, but cloud integration, remote device protection and distributed data management must be introduced.

## C. Adaptation of the Original Design

The revised architecture retains the original hospital systems and adds secure home monitoring devices and cloud-hosted patient records.

### 1. Revised Operating-System Plan

| Environment | Revised Recommendation | Purpose |
|---|---|---|
| Hospital bedside monitors | RTOS | Maintain predictable local alarm handling. |
| Home monitoring devices | Embedded OS / RTOS | Collect sensor readings, perform local processing and support secure communication. |
| Nurses' tablets | Android / iOS | Display patient readings and alerts securely. |
| Doctors' workstations | Linux / Windows | Access cloud-hosted patient records and clinical applications. |
| Cloud patient-record service | Cloud-hosted Linux-based services and managed database | Store, manage and share patient records across hospitals. |
| MRI processing server | Multiprocessor Linux Server OS | Continue supporting computationally intensive processing. |
| Hospital and cloud communication | Secure distributed-system architecture | Transfer monitoring data and patient records reliably. |

### 2. Revised Architecture and Data Flow

The revised system follows this data flow:

1. Home monitoring devices collect readings from patients using sensors.
2. The embedded OS or RTOS performs local processing and checks for critical conditions.
3. Readings are transmitted through an authenticated and encrypted internet connection.
4. The cloud service receives, stores and manages the readings.
5. Authorised doctors and nurses access the information through their workstations and tablets.
6. Patient records are shared with partner hospitals through secure cloud services.

Critical alerts should be generated locally whenever possible. Cloud-based alerts can provide additional monitoring and coordination, but should not be the only mechanism for urgent response.

### 3. Additional Reliability and Security Measures

- **Local buffering:** Store readings temporarily when internet connectivity is unavailable.
- **Secure synchronisation:** Upload stored readings when connectivity is restored.
- **Device authentication:** Give every remote monitoring device a unique identity.
- **Encryption:** Protect data both in transit and at rest.
- **Access control:** Allow only authorised healthcare professionals to access patient information.
- **Cloud backup and replication:** Maintain copies of important records to improve recovery and availability.
- **Monitoring and logging:** Detect suspicious activity, device failures and communication problems.
- **Secure updates:** Apply authenticated software and firmware updates to remote devices.

## D. Evidence-Based Defence

The decision to modify the original architecture is supported by the earlier analysis and practical measurements.

### 1. Evidence from Task 10

The file-copy experiment demonstrated the effect of buffer size on system-call overhead.

| Buffer Size | Total Read and Write Calls |
|---:|---:|
| 1 byte | 131,077 |
| 512 bytes | 261 |
| 4096 bytes | 37 |

The results show that larger buffers significantly reduce the number of system calls. This supports the use of suitable buffering when transferring batches of monitoring readings and other non-time-critical data.

However, buffering must be designed carefully for medical monitoring because excessive batching can delay the delivery of important readings.

### 2. Process and Thread Measurements

| Measurement | Average Elapsed Time |
|---|---:|
| 1,000 processes | 0.202371 seconds |
| 1,000 threads | 0.123565 seconds |

The thread benchmark was approximately 39% faster than the process benchmark in the tested environment.

This supports the general observation that threads can be useful when services need to perform concurrent operations while sharing resources. Cloud applications can use concurrent processing to handle requests from multiple devices and hospitals.

These measurements do not directly measure cloud performance or internet latency. They provide evidence about the behaviour of the tested Linux environment only.

### 3. Trade-offs of the Revised Design

| Design Choice | Advantage | Trade-off |
|---|---|---|
| Embedded OS / RTOS on home devices | Supports local processing and predictable task execution | Requires suitable hardware and device-level testing. |
| Cloud-hosted records | Supports access and sharing across hospitals | Depends on network connectivity and cloud service availability. |
| Local data buffering | Prevents temporary connectivity loss from immediately losing readings | Requires local storage and later synchronisation. |
| Encryption and authentication | Protects sensitive patient information | Adds processing and administration overhead. |
| Database replication | Improves availability and recovery | Requires synchronisation and consistency management. |
| Distributed architecture | Supports expansion across multiple hospitals | Introduces network, coordination and security complexity. |

### 4. Final Defence

Completely redesigning the system would be unnecessary because the original hybrid architecture already provides appropriate operating systems for the hospital's different environments.

Retaining the original design without changes would also be insufficient because it does not fully address remote internet-connected devices or cloud-based patient records.

Therefore, modifying the original design is the most balanced decision.

The revised architecture retains dedicated RTOS-based monitoring, introduces embedded operating systems for home devices and extends the hospital's services into a secure cloud-based distributed system.

This approach balances response time, reliability, security, scalability and resource usage while supporting the new requirements.

## Conclusion

The addition of home monitoring devices and cloud-hosted patient records requires an extension of the original hospital architecture.

The hybrid operating-system design remains suitable, but it must be modified to include secure remote devices, local data buffering, encrypted communication, cloud storage, replication and distributed access control.

Critical monitoring operations should continue locally to avoid depending entirely on internet connectivity. Cloud services should provide shared patient records and coordination across the three hospitals.

**The final decision is to MODIFY the original design**, as it preserves the strengths of the existing architecture while adapting it to remote healthcare monitoring and cloud-based hospital services.