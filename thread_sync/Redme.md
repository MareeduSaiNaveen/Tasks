# Synchronization Mechanisms in Linux: Mutex, Binary Semaphore, and Counting Semaphore

## Mutex

### Introduction
A **mutex (mutual exclusion)** is a synchronization mechanism that allows **only one thread** to enter a critical section at a time.  
It ensures **mutual exclusion** and prevents **race conditions** when multiple threads access shared resources.

### Key Features
- Ensures **mutual exclusion** for shared resources
- Tracks **ownership** by the thread that locks it
- Prevents race conditions and maintains data consistency
- Primarily used between **threads of the same process**

### Real-Time Usage
- Protecting **shared variables** in multithreaded programs
- Synchronizing access to **files or hardware resources**
- Ensuring **only one thread modifies data** at a time

### How Mutex Works
1. Thread attempts to **lock** the mutex.
2. If the mutex is **available**, the thread enters the critical section.
3. Other threads are **blocked** until the mutex is unlocked.
4. Thread **unlocks** the mutex after leaving the critical section.
5. Next waiting thread can enter.

### Conceptual Diagram

---

## Binary Semaphore

### Introduction
A **binary semaphore** is a semaphore with **two possible values: 0 or 1**.  
It can enforce **mutual exclusion** like a mutex but **does not track ownership**.

### Key Features
- Value **1** → resource available  
- Value **0** → resource locked  
- Can be used for **signaling between threads**
- Useful for **mutual exclusion** or **thread synchronization**

### Real-Time Usage
- Synchronizing access to **shared resources**
- Signaling events between **threads or processes**
- Embedded and real-time systems for **event-driven tasks**

### How Binary Semaphore Works
1. Thread checks the semaphore value.
2. If value = 1, thread decrements it and enters the critical section.
3. If value = 0, thread waits until released.
4. Thread increments semaphore after leaving critical section.

### Conceptual Diagram

---

## Counting Semaphore

### Introduction
A **counting semaphore** allows **multiple threads** to enter a critical section **simultaneously**, up to a **predefined limit**.

### Key Features
- Value represents **available slots** in the critical section
- Threads decrement semaphore to enter and increment it to leave
- Useful for **limited concurrent access**, e.g., database connections, thread pools
- Can prevent **resource overloading**

### Real-Time Usage
- Limiting number of threads accessing **shared hardware**
- Controlling access to **buffer pools** in producer-consumer systems
- Embedded and real-time systems to allow **controlled parallelism**

### How Counting Semaphore Works
1. Thread checks semaphore value.
2. If value > 0, thread decrements and enters critical section.
3. If value = 0, thread waits for a slot to become available.
4. Thread increments semaphore upon leaving.

### Conceptual Diagram
