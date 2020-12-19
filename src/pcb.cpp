/*
 * Pcb.cpp
 *
 *  Created on: Aug 30, 2019
 *      Author: OS1
 */

#include "pcb.h"

#include "list.h"
#include <dos.h>
#include "schedule.h"
#include "timer.h"
#include <iostream.h>

PCB* PCB::running=0;
ID PCB::posId=0;
List* PCB::allCreatedPCBs=new List();

const int PCB::CREATED=0;
const int PCB::READY=1;
const int PCB::RUNNING=2;
const int PCB::BLOCKED=3;
const int PCB::FINISHED=4;

void PCB::start(){

	lock();

    //cout<<"start\t ";
	status=PCB::READY;
	createStack();
	Scheduler::put(this);


	unlock();

}


void PCB::waitToComplete(){
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif

	if(this != PCB::running && this != Timer::idle->myPCB && this != Timer::main->myPCB && status != PCB::FINISHED)
{
		PCB::running->status=PCB::BLOCKED;
		waitingForMe->addToEnd(PCB::running);
		dispatch();

	}

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif
}

PCB::PCB(Thread* myThread, StackSize stackSize, Time timeSlice) {
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
   // cout<<"pcb\t ";
    id=++posId;
    this->myThread=myThread;
    this->stackSize=stackSize;
    this->timeSlice=timeSlice;

    this->stackSize /= sizeof(unsigned);
    status=PCB::CREATED;
    unblockedBySignal=0;
    waitingForMe= new List();
    maxTime=0;
    stack=0;
    ss=sp=bp=0;
    allCreatedPCBs->addToEnd(this);

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif

}

PCB::~PCB() {
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
    myThread=0;
	delete stack;
	delete waitingForMe;

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif
}


ID PCB::getId(){
	return id;
}

ID PCB::getRunningId(){
	return PCB::running->id;
}

Thread* PCB::getThreadById(ID id){
	PCB* ret=allCreatedPCBs->get(id);
	if (ret) return ret->myThread;
	return 0;

}


void PCB::createStack(){
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
    //cout<<"STACK!!!\t";
	stack=new unsigned[stackSize];
	stack[stackSize-1]=0x200;
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-2]=FP_SEG(PCB::wrapper);
	stack[stackSize-3]=FP_OFF(PCB::wrapper);
	this->sp=FP_OFF(stack+stackSize-12);
	this->ss=FP_SEG(stack+stackSize-12);
	this->bp=sp;


#endif


#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif

}



void PCB::wrapper(){
	//cout<<"wrapper\t";
	running->myThread->run();
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif

	running->status=FINISHED;
	running->waitingForMe->unblockAll();

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif
	dispatch();
}








