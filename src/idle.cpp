/*
 * Idle.cpp
 *
 *  Created on: Aug 30, 2019
 *      Author: OS1
 */

#include "idle.h"
#include "pcb.h"
#include "thread.h"
#include <iostream.h>

Idle::Idle(): Thread(256, 1) {


}

void Idle::run(){
	//cout<<"idle run\t";
	int i=0;
	while(1){
		i++;
		i--;
	}
}

void Idle::start(){

#ifndef BCC_BLOCK_IGNORE
	lock();
#endif

    //cout<<"idle start\t";

	myPCB->createStack();
	myPCB->status=PCB::READY;


#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif


}

