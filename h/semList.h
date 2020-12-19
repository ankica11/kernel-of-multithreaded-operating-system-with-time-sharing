/*
 * SemList.h
 *
 *  Created on: Sep 1, 2019
 *      Author: OS1
 */

#ifndef ANAVANOS_SEMLIST_H_
#define ANAVANOS_SEMLIST_H_

#include "kernSem.h"

class KernelSem;

class SemList {
public:
	struct Elem{
		KernelSem* elem;
		Elem* next;
		Elem(KernelSem* el): elem(el), next(0) {}
		~Elem(){elem=0;next=0;}

	};
	Elem* first;
	Elem* last;

	SemList();
	virtual ~SemList();

	void addToEnd(KernelSem* ksem);
	void removeSpecific(KernelSem* ksem);
	void updateGlobalSemList();
};

#endif /* ANAVANOS_SEMLIST_H_ */
