/*
 * List.h
 *
 *  Created on: Aug 30, 2019
 *      Author: OS1
 */

#ifndef ANAVANOS_LIST_H_
#define ANAVANOS_LIST_H_

#include "pcb.h"
#include "thread.h"

typedef int ID;


class PCB;

class List {
public:
	struct Elem{
		public:
			PCB* elem;
			Elem* next;
			Elem(PCB* el) : elem(el), next(0){}
			~Elem(){elem=0; next=0;}
		};

	Elem* first;
	Elem* last;

	List();
    virtual ~List();
    void addToEnd(PCB* pcb);
    void addToSleepList(PCB* pcb);
    PCB* get(ID id);
    PCB* removeFirst();
    void removeSpecific(ID id, int flag);
    void unblockAll();


};

#endif /* ANAVANOS_LIST_H_ */
