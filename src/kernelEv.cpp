/*
 * KernelEv.cpp
 *
 *  Created on: Sep 2, 2019
 *      Author: OS1
 */

#include "kernelEv.h"
#include "event.h"
#include "Schedule.h"
#include "IVTEntry.h"
#include "pcb.h"
#include "thread.h"


KernelEv::KernelEv(IVTNo ivtNo) {

	waitingForEventFlag=0;
	ivtEnt=ivtNo;
	owner=PCB::running;
	IVTEntry::IVTable[ivtEnt]->myKernelEv=this;


}

KernelEv::~KernelEv() {
IVTEntry::IVTable[ivtEnt]->myKernelEv=0;
}

void KernelEv::wait(){
	if(PCB::running != owner) return;
	owner->status = PCB::BLOCKED;
	waitingForEventFlag = 1;
	dispatch();
}


void KernelEv::signal(){
	if(waitingForEventFlag){

		owner->status=PCB::READY;
		Scheduler::put(owner);
		waitingForEventFlag = 0;
	}

}
