/*
 * List.cpp
 *
 *  Created on: Aug 30, 2019
 *      Author: OS1
 */

#include "list.h"
#include "pcb.h"
#include "schedule.h"
#include <iostream.h>

List::List() {
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
	//cout<<"lista\t ";
	first=last=0;

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif


}

List::~List() {
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif

	Elem* curr=first;
	while(curr){
		first=first->next;
		delete curr;
		curr=first;
	}
first=last=0;

#ifndef BCC_BLOCK_IGNORE
    unlock();
#endif

}

void List::addToEnd(PCB* pcb){
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif

	if(first)
		last=last->next=new Elem(pcb);
	else
		first=last=new Elem(pcb);
#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif
}


void List::addToSleepList(PCB* pcb){
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
   // cout<<"add to sleep"<<endl;
	Elem* temp=new Elem(pcb);
	Elem* curr=first;
	Elem* prev=0;
	if (first == 0){
			first = last = temp;
			return;
		};

	while(curr && (curr->elem->maxTime >= 0)){
		if(pcb->maxTime>=curr->elem->maxTime){
			pcb->maxTime -= curr->elem->maxTime;
			prev=curr;
			curr=curr->next;
		}else
			break;
	} //ubacujemo novi element ispred curra

	if(curr==first){        //ubacivanje na pocetak
		temp->next=first;
		first=temp;
	}else if (curr==0){    //dodavanje na kraj moramo da azuriramo pokazivac last
		last->next=temp;
		last=temp;

	}else {
		temp->next=curr; //dodavanje izmedju
		prev->next=temp;


	}

	if(temp->next && (temp->next->elem->maxTime>0))
		temp->next->elem->maxTime -= pcb->maxTime; //azuriranje elementa iza novog ako postoji

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif
}


PCB* List::get(ID id){ //samo pronalazimo element sa trazenim idjem

#ifndef BCC_BLOCK_IGNORE
	lock();
#endif


	Elem* curr=first;

	while(curr){
		if(curr->elem->id==id) return curr->elem;

	curr=curr->next;
	}



#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif

	return 0;

}

PCB* List::removeFirst(){
	if(first==0) return 0;

#ifndef BCC_BLOCK_IGNORE
	lock();
#endif

	Elem* curr=first;
	first=first->next;
	if(first==0) last=0;
	PCB* ret=curr->elem;
	delete curr;

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif

	return ret;
}

void List::removeSpecific(ID id, int flag){ //ako je flag 0 onda uklanjamo konkretan element iz obicne liste ako je 1 uklanjamo i iz sleep liste na semaforu
if(first==0) return;

#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
    //cout<<"removespeciific from blocked"<<endl;
	Elem* curr=first;
	Elem* prev=0;

	while(curr){
		if(id==curr->elem->id) break;
		prev=curr;
		curr=curr->next;

	}

	if(curr==0) return; // nije pronadjen element
	if(curr==first){
		first=first->next;
		if(first==0) last=0;
	}else if (curr==last){
		last=prev;
		last->next=0;

	} else {
		prev->next=curr->next;
	}

	if(curr->next && flag)
		curr->next->elem->maxTime += curr->elem->maxTime;
	delete curr;

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif


}



void List::unblockAll(){
	PCB* pcb;
	while(first){
		pcb= removeFirst();
		pcb->status=PCB::READY;
		Scheduler::put(pcb);
	}
}



















