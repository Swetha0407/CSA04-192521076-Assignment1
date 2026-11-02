# Task 4 – Evaluate the Operating-System Services

## 1. Introduction

An operating system provides services that allow application programs and users to interact with computer hardware. These services include program execution, input/output operations, file management, communication, error detection, resource allocation, and security.

In a smart hospital, every computing environment has different requirements. A bedside patient monitor needs fast and predictable operation, while a central database server requires strong security, storage management, communication, and reliability. Therefore, the operating system services should be selected according to the purpose of each device.

## 2. Evaluation of Operating-System Services

| OS Service | Purpose | Importance in a Smart Hospital |
|---|---|---|
| User Interface | Allows users to interact with the system. | Required on tablets and workstations; a simple interface is sufficient for monitors. |
| Program Execution | Loads and runs application programs. | Essential for all environments. |
| I/O Operations | Manages communication with input and output devices. | Critical for patient monitors, MRI equipment, and workstations. |
| File-System Management | Organizes, stores, and retrieves files. | Essential for databases, imaging servers, and devices that store logs or configuration data. |
| Communication | Enables data exchange between systems. | Required for sharing patient records and transmitting monitoring data. |
| Error Detection | Detects hardware and software errors. | Important for all systems, especially patient monitors and database servers. |
| Resource Allocation | Distributes CPU time, memory, and I/O resources. | Important for systems handling multiple applications or large workloads. |
| Accounting and Monitoring | Records resource usage and system activity. | Useful for server monitoring, auditing, and performance management. |
| Protection and Security | Prevents unauthorized access to system resources and data. | Essential for protecting confidential patient information. |

## 3. Services Required by Each Hospital Environment

### 3.1 Bedside Patient Monitors

Bedside monitors continuously receive patient readings and generate alarms when abnormal conditions are detected. Since alarms must be generated within 10 milliseconds, the operating system should minimize unnecessary background activities.

**Required services:**
- Program execution to run monitoring and alarm applications.
- I/O operations to receive readings from sensors.
- Error detection to identify sensor or device failures.
- Resource allocation to ensure predictable CPU and memory usage.
- Communication to transmit readings to the hospital system.
- Protection to prevent unauthorized modification of monitoring software.

**Services that can be reduced or removed:**
- Complex graphical user interfaces and desktop environments.
- Unnecessary background applications and services.
- Printing services and general-purpose multimedia services.
- Unnecessary network protocols and file-management features.

A small interface can still be retained to display readings and alarms. Basic file storage may also be needed for configuration and event logs. Therefore, the goal is to remove unnecessary services rather than remove every service that is not directly involved in monitoring.

**Evaluation:** A minimal set of services reduces resource usage and unnecessary background activity. However, removing services alone does not guarantee that the 10-millisecond alarm deadline will be met. The complete sensor-to-alarm path must be tested.

### 3.2 Nurses' Handheld Tablets

Nurses use tablets to access patient records, update information, and communicate with other hospital systems.

**Required services:**
- User interface for easy interaction.
- Program execution for hospital applications.
- File-system management for locally stored application data.
- Communication for accessing the hospital network.
- I/O operations for touchscreens, cameras, and other peripherals.
- Protection and security for patient information.
- Resource allocation and error detection.

**Evaluation:** A handheld operating system should provide the necessary hospital functions without running unnecessary desktop services. Background activity should be controlled to reduce memory consumption and battery usage.

### 3.3 Doctors' Desktop Workstations

Doctors use desktop workstations to access patient records, view reports, review medical images, and run hospital applications.

**Required services:**
- User interface for interaction with applications.
- Program execution for medical software.
- File-system management for reports and temporary files.
- I/O operations for keyboards, displays, printers, and other devices.
- Communication to access central databases.
- Resource allocation for multiple running applications.
- Error detection, accounting, and security services.

**Evaluation:** Desktop workstations require a wider range of services than bedside monitors because they support multiple applications and user interactions. Security and access control are particularly important because doctors may access confidential patient records.

### 3.4 Central Patient-Record Database Server

The database server stores and manages patient records for the hospital. It must remain available and protect sensitive information.

**Required services:**
- Program execution to run database-management software.
- File-system management for persistent storage.
- I/O operations for storage devices.
- Communication for handling requests from hospital systems and partner hospitals.
- Resource allocation for database processes and concurrent requests.
- Error detection and logging to identify failures.
- Accounting and monitoring to track performance and resource usage.
- Protection and security to control access to patient records.

**Evaluation:** The database server needs a comprehensive set of operating-system services. Removing essential