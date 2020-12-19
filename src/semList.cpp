/*
 * SemList.cpp
 *
 *  Created on: Sep 1, 2019
 *      Author: OS1
 */

#include "semList.h"
#include <iostream.h>;

SemList::SemList() {
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
	    //cout<<"creating sem list"<<endl;
		first=last=0;

#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif


}

SemList::~SemList() {
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif

	Elem* curr=first;
	while(first){
		first=first->next;
		delete curr;
  		curr=first;
	}
#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif


}


void SemList::addToEnd(KernelSem* ksem){
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
	//cout<<"add to end sem"<<endl;
	if(first) last=last->next=new Elem(ksem);
	else
		first=last=new Elem(ksem);
#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif

}

void SemList::removeSpecific(KernelSem* ksem){
	if(first==0) return;
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
	Elem* curr=first;
	Elem* prev=0;

while(curr){
	if(curr->elem==ksem) break;
	prev=curr;
	curr=curr->next;


}

if(curr==first){
	first=first->next;
	if (first==0) last=0;
}else if(curr==last){
	last=prev;
	last->next=0;

}else{
	prev->next=curr->next;
}

delete curr;
}

void SemList::updateGlobalSemList(){ //metodu poziva prekidna rutina tajmera
#ifndef BCC_BLOCK_IGNORE
	lock();
#endif
	//cout<<"update global sem list\t"<<endl;
	if (first==0) return;
	Elem* curr=first;

	while(curr){
		if(curr->elem)
			curr->elem->updateSleepList();

		curr=curr->next;
	}
#ifndef BCC_BLOCK_IGNORE
	unlock();
#endif
}









