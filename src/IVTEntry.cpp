/*
 * IVTEntry.cpp
 *
 *  Created on: Sep 2, 2019
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "thread.h"
#include <dos.h>

typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;

IVTEntry* IVTEntry::IVTable[256];

IVTEntry::IVTEntry(IVTNo num, pInterrupt routine) {
	ivtEnt=num;
	IVTEntry::IVTable[ivtEnt]=this;
	myKernelEv=0;
	oldIntrRoutine=0; //mesto gde premestamo staru prekidnu rutinu iz tog ulaza


	lock();
    #ifndef BCC_BLOCK_IGNORE
	oldIntrRoutine = getvect(ivtEnt);
	setvect(ivtEnt, routine);
    #endif
	unlock();

}

IVTEntry::~IVTEntry() {
	IVTEntry::IVTable[ivtEnt]=0;

	lock();
    #ifndef BCC_BLOCK_IGNORE
	setvect(ivtEnt, oldIntrRoutine);
    #endif
	unlock();


}

void IVTEntry::signal(){
	if(myKernelEv) myKernelEv->signal();
	dispatch();
}

void IVTEntry::oldInterruptRoutine(){   //callOldInterruptRoutine
	oldIntrRoutine();
}

