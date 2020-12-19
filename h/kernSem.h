/*
 * KernSem.h
 *
 *  Created on: Sep 1, 2019
 *      Author: OS1
 */

#ifndef ANAVANOS_KERNSEM_H_
#define ANAVANOS_KERNSEM_H_

#include "list.h"
#include "semList.h"

class SemList;

class KernelSem {
public:

	KernelSem(int init);
	virtual ~KernelSem();

	int signal(int n);
	int wait(Time maxTimeToWait);

	void updateSleepList();
	void unblockAllPCBs();

   // Semaphore* mySem;

	static SemList* allCreatedSemaphores;
	int val;

	List* blockedList;
    List* sleepList;


};

#endif /* ANAVANOS_KERNSEM_H_ */
