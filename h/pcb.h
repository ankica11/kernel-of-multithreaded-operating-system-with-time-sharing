/*
 * Pcb.h
 *
 *  Created on: Aug 30, 2019
 *      Author: OS1
 */

#ifndef ANAVANOS_PCB_H_
#define ANAVANOS_PCB_H_

#include "list.h"
#include "thread.h"
#include <stdio.h>

class List;


class PCB {
public:
	void start();
	void waitToComplete();
	PCB(Thread* myThread, StackSize stackSize, Time timeSlice);
   ~PCB();
   void createStack();
   static void wrapper();
   static ID getRunningId();
   ID getId();
   static Thread* getThreadById(ID id);

   static int const CREATED, READY, RUNNING, BLOCKED, FINISHED;
   static PCB* running;
   static List* allCreatedPCBs;
   static ID posId;

   Thread* myThread;
   ID id;

   unsigned* stack;
   unsigned int sp;
   unsigned int ss;
   unsigned int bp;
   StackSize stackSize;

   Time timeSlice;
   volatile int status;
   List* waitingForMe;
   int unblockedBySignal;//1-by signal 0-by timer
   Time maxTime; //max vreme cekanja na semaforu


};

#endif /* ANAVANOS_PCB_H_ */
