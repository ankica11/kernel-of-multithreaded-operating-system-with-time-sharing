/*
 * Timer.cpp
 *
 *  Created on: Aug 30, 2019
 *      Author: OS1
 */

#include "timer.h"

#include <dos.h>
#include <stdio.h>
#include <iostream.h>
#include "kernSem.h"
#include "semList.h"
#include "schedule.h"
#include "thread.h"
#include "list.h"
#include "pcb.h"

extern void tick();

volatile int Timer::counter=0;
volatile int Timer::change_context_in_demand=0;
pInterrupt Timer::oldInterruptRoutine=0;
Thread* Timer::main=0;
Idle* Timer::idle=0;



void Timer::inic(){

#ifndef BCC_BLOCK_IGNORE
	lock();
	Timer::oldInterruptRoutine=getvect(0x08);  //kupimo adresu stare prekidne rutine iz ulaza 8
	setvect(0x08, Timer::timer);               //stavljamo u ulaz 8 adresu nase nove prekidne rutine
	setvect(0x60, Timer::oldInterruptRoutine); //staru prekidnu rutinu preusmeravamo u ulaz 60
#endif
    //cout<<"inic start\n";
	//PCB::allCreatedPCBs=new List();
	//KernelSem::allCreatedSemaphores=new SemList();
	main=new Thread(4096,1);//startnu nit kreiramo sa time sliceom 1
	idle=new Idle();
	PCB::running=main->myPCB; //startnu nit stavljamo da bude running pri prvoj promeni konteksta ona ce se vezati za glavni stek
	main->myPCB->status=PCB::RUNNING;
	Timer::counter=main->myPCB->timeSlice;

	idle->start();    //pokrecemo idle nit ali je ne stavljamo u Scheduler
    //cout<<"inic end\n ";
#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif

}

void Timer::restore(){
    //cout<<"restore\t";
	if(PCB::running->myThread != main) return;
#ifndef BCC_BLOCK_IGNORE
	lock();
	setvect(0x08, Timer::oldInterruptRoutine);
#endif

	delete Timer::main;
	delete Timer::idle;
	delete PCB::allCreatedPCBs;
	delete KernelSem::allCreatedSemaphores;

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif

}

volatile unsigned int tsp=0;
volatile unsigned int tss=0;
volatile unsigned int tbp=0;




void interrupt Timer::timer(...){

	if(!change_context_in_demand){

		if(PCB::running)
			if(PCB::running->timeSlice !=0) counter--;
		    KernelSem::allCreatedSemaphores->updateGlobalSemList();


	}


	if(change_context_in_demand || (PCB::running && PCB::running->timeSlice && Timer::counter==0)){



#ifndef BCC_BLOCK_IGNORE
		asm{
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
#endif
		PCB::running->sp=tsp;
		PCB::running->ss=tss;
		PCB::running->bp=tbp;

if(PCB::running->myThread != Timer::idle && PCB::running->status != PCB::FINISHED && PCB::running->status != PCB::BLOCKED ){
	PCB::running->status=PCB::READY;
	Scheduler::put(PCB::running); }

	PCB::running=Scheduler::get();

	if(PCB::running == 0) PCB::running=Timer::idle->myPCB;
	PCB::running->status=PCB::RUNNING;

	tsp=PCB::running->sp;
	tss=PCB::running->ss;
	tbp=PCB::running->bp;

	counter=PCB::running->timeSlice;

#ifndef BCC_BLOCK_IGNORE

	asm{
		mov sp, tsp
		mov ss, tss
		mov bp, tbp
	}
#endif


}

	if(!change_context_in_demand){

		tick();
#ifndef BCC_BLOCK_IGNORE
		    asm int 0x60; //poziv stare prekidne rutine ako je regularan prekid tajmera
#endif
	}

	change_context_in_demand=0;
	}

















