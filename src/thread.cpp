/*
 * Thread.cpp
 *
 *  Created on: Aug 30, 2019
 *      Author: OS1
 */

#include "thread.h"
#include "pcb.h"
#include "timer.h"
#include "list.h"
#include <iostream.h>

void Thread::start(){
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
	myPCB->start();
#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif

}

void Thread::waitToComplete(){
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
	myPCB->waitToComplete();
#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif
}


Thread::~Thread() {
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
	waitToComplete();
	PCB::allCreatedPCBs->removeSpecific(this->getId(),0);
	delete myPCB;
#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif
}

ID Thread::getId(){
	return myPCB->getId();
}

ID Thread::getRunningId(){
	return PCB::getRunningId();
}

Thread* Thread::getThreadById(ID id){
	return PCB::getThreadById(id);
}


Thread::Thread(StackSize stackSize, Time timeSlice){
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
    //cout<<"thread\t";
	myPCB=new PCB(this, stackSize, timeSlice);

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif
}

void dispatch(){
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
 Timer::change_context_in_demand=1;
 Timer::timer();

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif
}













