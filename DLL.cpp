/*
 * Name: Haritima Manchanda
 * Windows PC : MinGW
 */
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;


DLL::DLL(){  // constructor - initializes an empty list
	last = NULL;
	first = NULL;
	numSongs = 0;
}

DLL::DLL(string t, string l, int m, int s){  // constructor, initializes a list with one new node with data x
	DNode *n = new DNode (t,l,m,s);
	first = n;
	last = n;
	numSongs=1;
}

void DLL::push(string t, string a, int m, int s){

	if(first == NULL){
		DNode *newNode = new DNode;
		newNode->song->title = t;
		newNode->song->artist = a;
		newNode->song->min = m;
		newNode->song->sec = s;
		first = newNode;
		last = newNode;
		newNode->next = NULL;
		newNode->prev = NULL;
		numSongs++;
	}
	else{
		DNode *newNode = new DNode;
		newNode->song->title = t;
		newNode->song->artist = a;
		newNode->song->min = m;
		newNode->song->sec = s;
		last->next = newNode;
		newNode->prev = last;
		newNode->next = NULL;
		last = newNode;
		numSongs++;
	}
}

void DLL::printList(){

	DNode *temp = first;
	while(temp != NULL){
		temp->song->printSong();
		temp = temp->next;
	}
	cout<<endl;
}

int DLL::remove(string t){

	DNode *temp;

	for(temp = first; temp != NULL; temp = temp->next){
		if(temp->song->title == t){

			if(temp->prev == NULL){
				// that is, first Node is to be removed
				first = temp->next;
				temp->next->prev = NULL;
				cout<<"Removing: "<<temp->song->title<<", "<<temp->song->artist<<"....."<<temp->song->min<<":"<<temp->song->sec<<endl;
			}
			else if(temp->next == NULL){
				// that is, last node is to be removed
				Song *song = pop();
				cout<<"Removing: "<<song->title<<", "<<song->artist<<"....."<<song->min<<":"<<song->sec<<endl;
			}
			else{
				temp->next->prev = temp->prev;
				temp->prev->next = temp->next;
				cout<<"Removing: "<<temp->song->title<<", "<<temp->song->artist<<"....."<<temp->song->min<<":"<<temp->song->sec<<endl;
			}
			numSongs--;
			delete temp;
			return 1;
		}
	}

	return 0;
}

Song* DLL::pop(){
	DNode *temp = last;
	temp->prev->next = NULL;
	last = temp->prev;
	Song *song = new Song(temp->song->title, temp->song->artist, temp->song->min, temp->song->sec);
	delete temp;
	return song;
}

void DLL::moveUp(string t){

	DNode *temp;

	for(temp = first; temp != NULL; temp = temp->next){

		if(temp->song->title == t){

			if(temp->prev == NULL){
				// that is, if first node is to be moved up
				first = temp->next;
				temp->next->prev = NULL;
				last->next = temp;
				temp->prev = last;
				temp->next = NULL;
				last = temp;
			}
			else if(temp->next == NULL){
				//that is, if last node is to be moved up
				DNode *temp1;
				temp1 = temp->prev->prev;
				temp1->next = temp;
				temp->prev->next = NULL;
				temp->prev->prev = temp;
				temp->next = temp->prev;
				temp->prev = temp1;
				last = temp->next;
			}
			else if(temp->prev == first){
				// Node 1 is the first Node and Node 2 is its adjacent node

				DNode *temp3 = temp->next;
				temp->next = first;
				first->next = temp3;
				first->prev = temp;
				temp->prev = NULL;
				first = temp;
			}
			else{
				// that is, if any node in between is to be moved up.
				DNode *temp1;
				temp1 = temp->prev->prev;
				temp1->next = temp;
				temp->prev->prev = temp;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp->next = temp->prev;
				temp->prev = temp1;

			}
		}
	}
}

void DLL::moveDown(string t){

	DNode *temp;

	for(temp = first; temp != NULL; temp = temp->next){

		if(temp->song->title == t){

			if(temp->prev == NULL){
				// that is, if first node is to be moved down
				DNode *temp2;
				temp2 = temp->next->next;
				first = temp->next;
				temp2->prev = temp;
				temp->next->prev = NULL;
				temp->next->next = temp;
				temp->prev = temp->next;
				temp->next = temp2;
			}
			else if(temp->next == NULL){
				// that is, if last node is to be moved down
				temp->prev->next = NULL;
				last = temp->prev;
				temp->next = first;
				temp->prev = NULL;
				first->prev = temp;
				first = temp;
			}
			else if(temp->next == last){
				DNode *temp3 = temp->prev;
				temp3->next = last;
				last->prev = temp3;
				last->next = temp;
				temp->prev = last;
				temp->next = NULL;
				last = temp;
			}
			else{
				//that is, if any node in between is to be moved down
				DNode *temp1 = temp->next->next;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				temp->next->next = temp;
				temp1->prev = temp;
				temp->prev = temp->next;
				temp->next = temp1;
			}
		}
	}
}

void DLL::listDuration(int *tm, int *ts){

	DNode *temp = first;

	while(temp != NULL){
		*ts += temp->song->sec;
		*tm += temp->song->min;
		temp = temp->next;
	}
}

void DLL::makeRandom(){

	int count = 0;	// total number of nodes
	int num = 0;	// The number of times the loop would run
	int randomNum1 = 1;
	int randomNum2 = 1;
	DNode *temp = first;

	// Counts the total number of nodes in the list
	while(temp != NULL){
		count++;
		temp = temp->next;
	}

	while(num < count){
			// Generates a number between 1 and count (including count)
			randomNum1 = (rand() % count) + 1;

			randomNum2 = (rand() % count) + 1;

			if(randomNum2 == randomNum1){
				randomNum2 = (rand() % count) + 1;
			}

			else if(randomNum2 < randomNum1){
				int tmp = randomNum2;
				randomNum2 = randomNum1;
				randomNum1 = tmp;
			}

			temp = first;
			DNode *temp2 = first;
			int i = 1, j = 1;

			// Moves the temp pointer to node at "randomNum1" position.
			// Eg - First Node is at 1st position, Second Node is at 2nd position and so on
			while(i != randomNum1 && temp != NULL){
				temp = temp->next;
				i++;
			}

			// Moves the temp2 pointer to node at "randomNum2" position.
			while(j != randomNum2 && temp2 != NULL){
				temp2 = temp2->next;
				j++;
			}

			// Different Cases for swapping nodes.

			if(temp->prev == NULL && temp2->next != NULL && (randomNum2 - randomNum1) > 1){
				// that is, Node 1 is the first node and node 2 is not the last node
				// The nodes are not adjacent

				DNode *temp3;
				temp3 = temp2->next;
				temp3->prev = temp;
				temp2->next = temp->next;
				temp2->prev->next = temp;
				temp->next->prev = temp2;
				temp->next = temp3;
				temp->prev = temp2->prev;
				temp2->prev = NULL;
				first = temp2;
			}

			else if(temp->prev == NULL && temp2->next == NULL && (randomNum2 - randomNum1) > 1){
				// that is, Node 1 is the first node and node 2 is the last node
				// The nodes are not adjacent

				temp2->next = temp->next;
				temp2->prev->next = temp;
				temp->prev = temp2->prev;
				temp2->prev = NULL;
				temp->next->prev = temp2;
				temp->next = NULL;
				first = temp2;
				last = temp;
			}

			else if(temp->prev != NULL && temp2->next != NULL && (randomNum2 - randomNum1) > 1){
				// that is, none of the nodes is either the first node or the last node
				// The nodes are not adjacent

				DNode *temp3 = temp2->next;
				DNode *temp4 = temp->prev;
				temp3->prev = temp;
				temp2->next = temp->next;
				temp->next->prev = temp2;
				temp2->prev->next = temp;
				temp->prev->next = temp2;
				temp->prev = temp2->prev;
				temp2->prev = temp4;
				temp->next = temp3;
			}

			else if(temp->prev != NULL && temp2->next == NULL  && (randomNum2 - randomNum1) > 1){
				// that is, Node 2 is the last node and node 1 is not the first node
				// The nodes are not adjacent

				DNode *temp3 = temp->prev;
				temp2->prev->next = temp;
				temp->prev->next = temp2;
				temp->next->prev = temp2;
				temp->prev = temp2->prev;
				temp2->next = temp->next;
				temp->next = NULL;
				temp2->prev = temp3;
				last = temp;
			}

			 if (temp->prev == NULL && temp2->next == NULL && (randomNum2 - randomNum1) == 1){
				//Node 1 is the first node and node 2 is the last node and these are adjacent nodes

				temp->next = NULL;
				temp->prev = temp2;
				temp2->next = temp;
				temp2->prev = NULL;
				first = temp2;
				last = temp;
			}

			else if(temp->prev != NULL && temp2->next != NULL && (randomNum2 - randomNum1) == 1){
				// In between nodes that are adjacent to each other

				temp->prev->next = temp2;
				temp2->prev = temp->prev;
				temp->next = temp2->next;
				temp2->next->prev = temp;
				temp->prev = temp2;
				temp2->next = temp;
			}

			else if(temp->prev != NULL && temp2->next == NULL && (randomNum2 - randomNum1) == 1){
				//Node 2 is the last node and node 1 is its adjacent node

				DNode *temp3 = temp->prev;
				temp->next = NULL;
				temp->prev = temp2;
				temp2->next = temp;
				temp2->prev = temp3;
				temp3->next = temp2;
				last = temp;
			}
			 num++;
	}
}

DLL::~DLL(){

	DNode *temp = first;
	DNode *temp2 = first->next;

	while(temp != NULL){ // while the list is not empty
		delete temp;
		temp = temp2;
		if(temp!=NULL){
			temp2 = temp2->next;
		}
	}
	first = NULL;
	last = NULL;
	numSongs = 0;
}
