# Pipes in Linux

## 1. Introduction
A **pipe** is a unidirectional communication mechanism between processes. It allows one process to **send data** to another process in a **First-In-First-Out (FIFO)** manner. Pipes are widely used in Linux and Unix for **inter-process communication (IPC)**.

### Key Features:
- Unidirectional (one-way) data flow.
- Works mainly between **parent and child processes**.
- Temporary buffer in kernel memory holds data until read.
- Supports **stream of bytes**, not structured messages.

---

## 2. Real-Time Usage
Pipes are commonly used in:
- **Parent → Child process communication** in programs.
- **Shell commands piping**:  
  ```bash
  ls | grep ".c"

# Message Queues in Linux

## 1. Introduction
A **message queue** is an **Inter-Process Communication (IPC)** mechanism that allows processes to **exchange structured messages** in a **First-In-First-Out (FIFO)** manner. Unlike pipes, message queues can be used between **unrelated processes** and allow **message prioritization** using message types.

### Key Features:
- Structured messages with **message type** and **data**.
- Supports communication between **any processes**.
- Can be **blocking or non-blocking**.
- Useful in **real-time systems**, **logging**, and **event-driven applications**.

---

## 2. Real-Time Usage
Message queues are commonly used in:
- **Parent ↔ Child or unrelated processes communication**.
- **Real-time systems** to send events between tasks.
- **Embedded Linux applications** where structured messages are required.
- Example: Sending a command from a control process to a sensor process.

---

## 3. How Message Queues Work
Linux provides **System V message queues** with these system calls:

| Function | Purpose |
|----------|---------|
| `msgget()` | Create or access a message queue |
| `msgsnd()` | Send a message to the queue |
| `msgrcv()` | Receive a message from the queue |
| `msgctl()` | Control operations (delete, status) |

**Message structure:**

struct message {
    long msg_type;       // Message type (must be > 0)
    char msg_text[100];  // Message content
};

# Notifications in Linux

## 1. Introduction
A **notification** is a way for the operating system or one process to **inform another process that an event has occurred**.  
In Linux, the most common mechanism for notifications is **signals**.

### Key Features:
- Asynchronous notification from **kernel or another process**.
- Does not carry data like pipes or queues; mainly an **event trigger**.
- Can be handled by **signal handlers** registered in the program.
- Commonly used in **process control**, **interrupt handling**, and **timers**.

---

## 2. Real-Time Usage
Notifications (signals) are commonly used in:
- **User interrupts**: Ctrl+C (`SIGINT`) stops a program.
- **Child process termination**: `SIGCHLD`.
- **Illegal memory access**: `SIGSEGV`.
- **Timers or alarms**: `SIGALRM`.
- Embedded Linux applications for **event-driven tasks**.

Example:
kill -SIGINT <pid>

# Mailboxes in Embedded/RTOS Systems

## 1. Introduction
A **mailbox** is an **Inter-Process Communication (IPC)** mechanism used in **embedded systems and RTOS** to send **messages or data between tasks**.  
It is similar to a **message queue**, but usually:
- Contains **fixed-size messages**.
- Provides **task synchronization** along with communication.
- Often **blocking**, so a task waits if mailbox is empty or full.

### Key Features:
- Provides **structured communication** between tasks.
- Helps in **event-driven task synchronization**.
- Widely used in **embedded and real-time systems** (FreeRTOS, uC/OS).
- Can be **blocking or non-blocking**.

---

## 2. Real-Time Usage
Mailboxes are used in:
- **Task-to-task communication** in RTOS.
- Synchronizing **producer and consumer tasks**.
- Sending **control commands, sensor data, or status messages**.
- Example:  
  A sensor task writes data to a mailbox, a processing task reads from it.

---

## 3. How Mailboxes Work
Typical mailbox API in RTOS:

| Function        | Purpose                          |
|-----------------|---------------------------------|
| `mbox_create()` | Create a mailbox                 |
| `mbox_send()`   | Send a message to the mailbox    |
| `mbox_receive()`| Receive a message from the mailbox |
| `mbox_delete()` | Delete the mailbox               |

- If mailbox is **full**, sender may block.  
- If mailbox is **empty**, receiver may block.  
- Synchronization is done using **mutexes and condition variables** in software simulations.

---

## 4. Implementation Example (Simulated Mailbox in Linux using pthread)

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZE 100

// Mailbox structure
typedef struct {
    char message[MSG_SIZE];
    int full; // 0 = empty, 1 = full
    pthread_mutex_t lock;
    pthread_cond_t cond;
} Mailbox;

Mailbox mbox;

// Sender thread
void* sender(void* arg) {
    char* msg = (char*)arg;
    pthread_mutex_lock(&mbox.lock);
    
    while(mbox.full) {
        pthread_cond_wait(&mbox.cond, &mbox.lock); // Wait if mailbox full
    }
    
    strcpy(mbox.message, msg);
    mbox.full = 1;
    printf("Message sent: %s\n", msg);
    
    pthread_cond_signal(&mbox.cond); // Notify receiver
    pthread_mutex_unlock(&mbox.lock);
    
    return NULL;
}

// Receiver thread
void* receiver(void* arg) {
    pthread_mutex_lock(&mbox.lock);
    
    while(!mbox.full) {
        pthread_cond_wait(&mbox.cond, &mbox.lock); // Wait if mailbox empty
    }
    
    printf("Message received: %s\n", mbox.message);
    mbox.full = 0;
    
    pthread_cond_signal(&mbox.cond); // Notify sender
    pthread_mutex_unlock(&mbox.lock);
    
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&mbox.lock, NULL);
    pthread_cond_init(&mbox.cond, NULL);
    mbox.full = 0;

    pthread_create(&t1, NULL, sender, "Hello from Mailbox!");
    sleep(1); // Ensure sender runs first
    pthread_create(&t2, NULL, receiver, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mbox.lock);
    pthread_cond_destroy(&mbox.cond);
    '
    return 0;
}
