/*
 * KernSem.cpp
 *
 *  Created on: Sep 1, 2019
 *      Author: OS1
 */

#include "kernSem.h"

#include "list.h"
#include "pcb.h"
#include "semList.h"
#include "schedule.h"
#include <iostream.h>

SemList* KernelSem::allCreatedSemaphores=new SemList();


KernelSem::KernelSem(int init) {
	//cout<<"kern sem constructor"<<endl;
val=init;
blockedList=new List();
sleepList=new List();
KernelSem::allCreatedSemaphores->addToEnd(this);


}

KernelSem::~KernelSem() {
     KernelSem::allCreatedSemaphores->removeSpecific(this);
     this->unblockAllPCBs();
     delete blockedList;
     delete sleepList;
     //mySem=0;

}



int KernelSem::signal(int n){
	int ret=0;

	if(n<0) return n;
	if(n==0){

		if(val++<0){
			PCB* temp=blockedList->removeFirst();
			if(temp->maxTime != 0) sleepList->removeSpecific(temp->id, 1);
			temp->status=PCB::READY;
			temp->unblockedBySignal=1;
			Scheduler::put(temp);
		}
	}else {
		if(val<0)
			while(blockedList->first && n>ret){
				PCB* temp=blockedList->removeFirst();
				ret++;
				if(temp->maxTime != 0 )
					sleepList->removeSpecific(temp->id, 1);
				temp->status=PCB::READY;
				temp->unblockedBySignal=1;
				Scheduler::put(temp);


		}
		val+=n;
	}
	return ret;
}

int KernelSem::wait(Time maxTimeToWait){
	int ret=1;
	//val--;
	if (--val<0){
		//cout<<"wait call"<<endl;
		PCB::running->maxTime=maxTimeToWait;
		if(maxTimeToWait!=0)
			sleepList->addToSleepList(PCB::running);
		PCB::running->status=PCB::BLOCKED;
		blockedList->addToEnd(PCB::running);
		dispatch();
		ret=PCB::running->unblockedBySignal;




	}
	return ret;
}


void KernelSem::updateSleepList(){  //ovu metodu poziva nova prekidna rutina tajmera
	if (sleepList->first == 0) return;
	//cout<<"update sleep list"<<endl;

	List::Elem* curr=sleepList->first;

#ifndef BCC_BLOCK_IGNORE
	lock();
#endif

	curr->elem->maxTime--;

while (curr && curr->elem->maxTime==0){
	curr->elem->status=PCB::READY;
	curr->elem->unblockedBySignal=0;
	val++;
	blockedList->removeSpecific(curr->elem->id, 0);
	Scheduler::put(curr->elem);
	sleepList->first=sleepList->first->next;
	if (sleepList->first == 0)sleepList->last=0;
	delete curr;
	curr=sleepList->first;

}

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif

}

void KernelSem::unblockAllPCBs(){
	PCB* pcb;
		while(blockedList->first){
			pcb = blockedList->removeFirst();
			if(pcb->maxTime != 0) sleepList->removeSpecific(pcb->id, 1);
			pcb->status=PCB::READY;
			Scheduler::put(pcb);
		}
}



















