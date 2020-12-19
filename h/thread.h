/*
 * Thread.h
 *
 *  Created on: Aug 30, 2019
 *      Author: OS1
 */

#ifndef ANAVANOS_THREAD_H_
#define ANAVANOS_THREAD_H_

#include <dos.h>

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default=2*55ms
typedef int ID;

class PCB; // Kernel's implementation of a user's thread

class Thread {
public:
	void start();
	void waitToComplete();
	virtual ~Thread();

	ID getId();
	static ID getRunningId();
	static Thread* getThreadById(ID id);

protected:
	friend class PCB;
	Thread(StackSize stackSize=defaultStackSize, Time timeSlice=defaultTimeSlice);
	virtual void run(){};
    friend class Idle;
    friend class Timer;

private:
	PCB* myPCB;

};

void dispatch();

#define lock() {asm pushf; asm cli;}


#define unlock() asm { popf; }
#endif /* ANAVANOS_THREAD_H_ */
