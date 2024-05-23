# Multithreaded Operating System Kernel with Time Sharing
This project is a kernel for a multithreaded operating system with time-sharing capabilities, developed in C++ as part of the "Operating Systems" course at university.

## Key Features:

- <b>Threads and Context Switching:</b> Implements thread management and context switching, ensuring the processor time is shared among threads. When a thread's time slice expires, its context is saved, and the next thread from the scheduler is set to run.
- <b>Timer Interrupt Routine:</b> Includes a timer interrupt routine that handles context switching, placing the current thread back in the scheduler unless it is blocked or finished.
- <b>Semaphores and Events:</b> Provides synchronization mechanisms like semaphores and events. Semaphore operations include block and signal, while event handling involves registering threads to listen for events and signaling those threads when events occur.
- <b>IVT Table:</b> Uses an Interrupt Vector Table (IVT) to manage interrupts.
- <b>Process Control Block (PCB):</b> Manages the state and context of each thread using PCB structures.
