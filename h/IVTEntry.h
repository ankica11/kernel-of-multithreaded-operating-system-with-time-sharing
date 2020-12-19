/*
 * IVTEntry.h
 *
 *  Created on: Sep 2, 2019
 *      Author: OS1
 */

#ifndef ANAVANOS_IVTENTRY_H_
#define ANAVANOS_IVTENTRY_H_

#include "kernelEv.h"

class KernelEv;

typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;


class IVTEntry {
public:
	IVTEntry(IVTNo num, pInterrupt routine);
	virtual ~IVTEntry();
	void signal();
	void oldInterruptRoutine();

	static IVTEntry* IVTable[];

private:
	IVTNo ivtEnt;
	pInterrupt oldIntrRoutine;
	KernelEv* myKernelEv;
	friend class KernelEv;
};

#endif /* ANAVANOS_IVTENTRY_H_ */
