/*
 * KernelEv.h
 *
 *  Created on: Sep 2, 2019
 *      Author: OS1
 */

#ifndef ANAVANOS_KERNELEV_H_
#define ANAVANOS_KERNELEV_H_

#include "event.h"
#include"IVTEntry.h"
#include "pcb.h"
typedef unsigned char IVTNo;

class KernelEv {
public:
	KernelEv(IVTNo ivtNo);
	virtual ~KernelEv();
	void wait();
	void signal();


private:
	int waitingForEventFlag;
	IVTNo ivtEnt;
	PCB* owner;
};

#endif /* ANAVANOS_KERNELEV_H_ */
