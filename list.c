#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
	List* list = (List *) malloc(sizeof(List));
	list -> head = NULL;
	list -> current = NULL;
	list -> tail = NULL;
	return list;
}

void * firstList(List * list) {
	if (list == NULL || list -> current == NULL) return NULL;
	list->current = list->head;
  return list->head->data;
}

void * nextList(List * list) {
	if (list == NULL || list -> current == NULL || list -> current -> next == NULL) return NULL;
	list -> current = list -> current -> next;
  return list -> current -> data;
}

void * lastList(List * list) {
	if (list == NULL || list -> current == NULL) return NULL;
	while (list->current->next != NULL) list -> current = list->current->next;
    return list -> current -> data;
}

void * prevList(List * list) {
	if (list == NULL || list -> current == NULL || list -> current -> prev == NULL) return NULL;
	list -> current = list->current->prev;
	return list -> current -> data;
}

void pushFront(List * list, void * data) {
	Node *nuevoNodo = createNode(data);
	
	nuevoNodo->data = data;
	nuevoNodo->prev = NULL;
	nuevoNodo->next = list->head;
	
	if(list->head){
		list->head->prev = nuevoNodo;}
	
	list->head = nuevoNodo;
	
	if(list->tail == NULL){
		list->tail = nuevoNodo;}
}

void pushBack(List * list, void * data) {
	Node *aux = list->head;
	while(aux->next != NULL) aux = aux->next;
  list->current = list->tail;
	if(list->current != NULL) pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
	Node *nuevoNodo = createNode(data);
	nuevoNodo->prev = list->current;
	nuevoNodo->next = list->current->next;
	nuevoNodo->prev->next = nuevoNodo;
	list->tail = nuevoNodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
	Node *left = list->current->prev;
	Node *right = list->current->next;
	
	if(left != NULL) left->next = right;
	else list->head = right;
	if (right != NULL) right->prev = left;
	else (list -> tail = left);

	void *dato = list->current->data;
	free(list->current);
	list->current = NULL;
  return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}