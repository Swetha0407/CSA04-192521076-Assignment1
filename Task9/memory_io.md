# Task 9 – Evaluate the Memory Hierarchy and I/O Systems

## 1. Aim

To evaluate how data moves through different levels of the memory hierarchy and how I/O systems transfer data between devices and memory. The task also examines suitable storage locations for MRI images, patient records, and bedside monitor readings, along with the advantages of caching and DMA.

## 2. Memory Hierarchy

A computer uses different levels of memory and storage to balance speed, capacity, and cost. Faster memory generally has smaller capacity, while slower storage provides larger capacity.

| Memory Level | Typical Access Time | Typical Capacity |
|---|---|---|
| CPU Registers | Less than 1 ns | Bytes to a few KB |
| CPU Cache (L1/L2/L3) | Approximately 0.5–20 ns | KB to tens of MB |
| Main Memory (RAM) | Approximately 50–100 ns | GBs |
| SSD | Approximately 50–200 µs | Hundreds of GB to several TB |
| Hard Disk (HDD) | Approximately 5–15 ms | TBs |
| Network Storage | Approximately 0.1–10 ms or more | GBs to PBs |

*Note: These are representative approximate values. Actual access times and capacities depend on hardware, storage technology, network conditions, and workload.*

### Importance of the Memory Hierarchy

- **Registers:** Store values currently being processed by the CPU.
- **Cache:** Stores frequently accessed instructions and data to reduce access time.
- **RAM:** Holds currently running programs and active data.
- **SSD:** Provides fast, persistent storage for applications and files.
- **HDD:** Provides high-capacity storage at a relatively lower cost.
- **Network Storage:** Allows multiple systems to access shared data and supports centralized storage.

The hierarchy ensures that frequently accessed data can be kept closer to the CPU, while larger amounts of data are stored in higher-capacity storage.

## 3. Storage Placement for Hospital Data

Different types of hospital data have different performance and storage requirements.

### 3.1 MRI Images

MRI images are large and require substantial storage capacity.

- Active images are temporarily stored in RAM during processing.
- Original images and processed results are stored on high-capacity SSD storage for faster access.
- Older images can be archived on HDD or network storage.
- Backups should be maintained to prevent data loss.

**Justification:** MRI images require large storage capacity, and SSDs provide faster access for active imaging workloads.

### 3.2 Patient Records

Patient records require reliable storage and frequent access.

- Frequently accessed records and database indexes can be cached in RAM.
- Persistent records should be stored on reliable SSD-backed database storage.
- Replicated storage and backups should be maintained for availability and recovery.

**Justification:** Keeping frequently accessed records and indexes in memory reduces repeated storage access and improves response time for doctors.

### 3.3 Bedside Monitor Readings

Bedside monitors generate readings that may require immediate processing.

- The latest readings and alarm-related state should be maintained in RAM.
- Important readings and event logs should be stored persistently.
- SSD-backed storage or a suitable database can maintain historical readings.

**Justification:** Keeping current readings in RAM supports fast processing, while persistent storage maintains important patient-monitoring history.

## 4. I/O Methods

Three common methods are used to transfer data between the CPU, memory, and I/O devices.

### 4.1 Programmed I/O

In programmed I/O, the CPU continuously checks the status of an I/O device and performs the data transfer itself.

- The CPU repeatedly checks whether the device is ready.
- The CPU handles the transfer of data.
- CPU time may be wasted while waiting for the device.

**Example:** A CPU repeatedly checks whether an I/O device has data available.

### 4.2 Interrupt-Driven I/O

In interrupt-driven I/O, the device notifies the CPU when it requires attention.

- The CPU starts or enables an I/O operation.
- The device generates an interrupt when attention is required or data is ready.
- The CPU executes an interrupt handler to service the device.
- Continuous polling is avoided, but frequent interrupts create processing overhead.

**Example:** A device generates an interrupt when a data transfer event occurs.

### 4.3 Direct Memory Access (DMA)

Direct Memory Access allows data to be transferred directly between an I/O device and main memory without requiring the CPU to handle every word.

- The CPU configures the DMA controller with the source, destination, and transfer size.
- The DMA controller transfers data directly into main memory.
- The CPU can perform other tasks while the transfer takes place.
- An interrupt is normally generated when the transfer completes or requires attention.

**Example:** An MRI scanner transfers a large image directly into RAM using DMA.

### Comparison of I/O Methods

| Factor | Programmed I/O | Interrupt-Driven I/O | DMA |
|---|---|---|---|
| CPU involvement | Very high | Moderate | Low |
| Data transfer | CPU handles transfer | CPU services device interrupts | DMA controller handles transfer |
| CPU waiting | Repeated status checking | No continuous polling required | CPU can perform other tasks |
| Overhead | Repeated checking and transfer work | Interrupt-handling overhead | Setup and completion handling |
| Suitable usage | Simple or low-volume I/O | Event-driven device communication | Large data transfers |

### Recommended I/O Method for the MRI Scanner

DMA is the most suitable method for transferring large MRI images because it avoids requiring the CPU to handle every word of the transfer.

It reduces CPU overhead and allows the processor to perform other hospital operations while the image is transferred.

## 5. Effect of Caching on Patient-Record Lookup

Caching improves the speed of frequently accessed patient-record lookups by keeping commonly requested data in faster memory.

### Without Caching

1. A doctor requests a patient record.
2. The database retrieves the required data from persistent storage.
3. Storage access takes longer than accessing RAM.
4. The requested record is returned to the doctor.

### With Caching

1. Frequently accessed records and database indexes are maintained in RAM.
2. When a doctor requests cached information, the database retrieves it directly from memory.
3. The lookup is faster than retrieving the same information from persistent storage.

### Example Calculation

Assume:

- RAM access time = 80 ns.
- SSD access time = 100 µs.

Convert SSD access time into nanoseconds:

\[
100\ \mu s = 100,000\ ns
\]

Speed ratio:

\[
\text{Speed Ratio}=\frac{100,000}{80}
\]

\[
=1250
\]

In this illustrative comparison, RAM access is approximately 1,250 times faster than SSD access.

**Evaluation:** Caching reduces repeated storage access, improves database response time, and helps serve multiple doctors efficiently. Actual lookup performance also depends on cache hit rate, indexing, query execution, and database workload.

## 6. Alternative Concept – Interrupt-Driven I/O Instead of DMA

The assignment considers an MRI scanner transferring a 500 MB image using one interrupt per word instead of DMA.

This would generate a very large number of interrupts and significantly increase CPU overhead.

### 6.1 Calculate the Number of Interrupts

Assumptions:

- Image size = 500 MB.
- Word size = 4 bytes (32 bits).
- One interrupt is generated for every word.

Convert the image size into bytes:

\[
500 \times 1024 \times 1024
=524,288,000\text{ bytes}
\]

Calculate the number of words:

\[
\text{Number of words}
=\frac{524,288,000}{4}
\]

\[
=131,072,000
\]

Therefore, the CPU would need to handle approximately **131.07 million interrupts**.

### 6.2 Calculate CPU Time

Assume each interrupt requires approximately 5 microseconds of CPU handling time.

Calculate the total CPU handling time:

$$
T = \text{Number of Interrupts} \times \text{Time per Interrupt}
$$

Substitute the values:

$$
T = 131,072,000 \times 5\ \mu s
$$

$$
T = 655,360,000\ \mu s
$$

Convert microseconds into seconds:

$$
T = \frac{655,360,000}{1,000,000}
$$

$$
T = 655.36\ \text{seconds}
$$

Convert into hours:

$$
T = \frac{655.36}{3600}
$$

$$
T \approx 0.182\ \text{hours}
$$

This is approximately 10.92 minutes of cumulative CPU interrupt-handling time under the assumed cost.

### 6.3 Interrupt-Driven I/O vs DMA

| Factor | One Interrupt Per Word | DMA |
|---|---|---|
| Interrupt count | 131,072,000 | Usually one or a small number per transfer or batch |
| CPU involvement | Very high | Low |
| Transfer handling | CPU handles individual words | DMA transfers data directly to RAM |
| CPU availability | Reduced by interrupt handling | Available for other tasks |
| Efficiency | Inefficient for large transfers | Efficient for large transfers |
| Suitability | Not recommended for large MRI images | Recommended |

### 6.4 Memory Buffer Requirements

Both methods require memory to store the incoming MRI image. The main difference is how the data is transferred into that memory.

**Interrupt-Driven I/O:**

- Requires a destination buffer to hold the incoming image.
- The CPU handles individual words and places them into the buffer.
- Repeated interrupt handling increases CPU overhead.

**DMA:**

- Requires a destination buffer in RAM.
- The DMA controller transfers data directly into the allocated buffer.
- Large transfers can use multiple smaller buffers or a ring-buffer arrangement.
- The CPU is notified when a transfer completes or requires attention.

For a 500 MB image, a full-image destination buffer requires approximately 500 MiB of RAM, excluding additional application and operating-system overhead.

DMA does not eliminate the need for a destination buffer. It reduces CPU involvement in filling that buffer.

**Evaluation:** DMA is clearly more efficient for the MRI scanner because handling one interrupt per word would generate an enormous number of interrupts and consume substantial CPU time.

## 7. Final Data Placement and I/O Recommendation

| Hospital Component | Storage Recommendation | I/O Recommendation | Reason |
|---|---|---|---|
| MRI Scanner | RAM buffers, SSD for active images, HDD/network storage for archives | DMA | Efficient transfer of large image data |
| Patient-Record Database | RAM/cache for frequently accessed records, SSD for persistent records, replicated backups | Interrupt-driven or DMA-based I/O as appropriate for the devices | Faster lookup and reliable persistent storage |
| Bedside Monitors | RAM for current readings and alarm state, persistent storage for important logs | Interrupt-driven I/O where supported | Timely event notification and reduced unnecessary polling |

The overall strategy is to keep frequently accessed and time-critical information in faster memory, use persistent storage for long-term data, and use DMA for large data transfers.

## 8. Conclusion

This task evaluated the memory hierarchy and I/O systems in the smart hospital environment.

The analysis showed that registers, cache, and RAM provide fast access to active data, while SSDs, HDDs, and network storage provide increasing storage capacity for persistent and historical information.

MRI images should use RAM buffers and SSD storage for active processing, patient records should use RAM caching and reliable SSD-backed storage, and bedside monitor readings should remain readily available in memory for rapid processing.

The comparison of programmed I/O, interrupt-driven I/O, and DMA showed that DMA is the most suitable method for large MRI image transfers. The calculation demonstrated that transferring a 500 MB image using one interrupt per word would generate approximately 131 million interrupts under the given assumptions.

Therefore, an appropriate memory hierarchy, effective caching, and DMA-based large data transfers are essential for achieving efficient performance in the smart hospital system.