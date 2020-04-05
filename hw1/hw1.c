#include "hw1.h"

#define INSERT_OBJECT_SIZE (48)

void Init(){
	int i;
	Object* pObject;

	for (i = 0; i < INSERT_OBJECT_SIZE; i++) {
		pObject = (Object*)malloc(sizeof(Object));
		pObject->objnum = OBJ_INVALID;
		InsertObjectIntoObjFreeList(pObject);
	}


	for (i = 0; i < HASH_TBL_SIZE; i++) {
		pHashTableEnt[i].elmtCount = 0;
	}

}

void InsertObjectToTail(Object* pObj, int ObjNum){
	pObj->objnum = ObjNum;
	int index = ObjNum % HASH_TBL_SIZE;

	if (pHashTableEnt[index].elmtCount == 0) {
		pHashTableEnt[index].pHead = pObj;
		pHashTableEnt[index].pTail = pObj;
	}
	else {
		Object* pPrev = pHashTableEnt[index].pTail;
		pPrev->phNext = pObj;
		pObj->phPrev = pPrev;
		pHashTableEnt[index].pTail = pObj;
	}

	pHashTableEnt[index].pTail->phNext = NULL;

	pHashTableEnt[index].elmtCount++;

}

void InsertObjectToHead(Object* pObj, int objNum){
	pObj->objnum = objNum;
	int index = objNum % HASH_TBL_SIZE;

	if (pHashTableEnt[index].elmtCount == 0) {
		pHashTableEnt[index].pTail = pObj;
		pHashTableEnt[index].pHead = pObj;
	}
	else {
		Object* pNext = pHashTableEnt[index].pHead;
		pNext->phPrev = pObj;
		pObj->phNext = pNext;
		pHashTableEnt[index].pHead = pObj;
	}


	pHashTableEnt[index].pHead->phPrev = NULL;

	pHashTableEnt[index].elmtCount++;
}

Object* GetObjectByNum(int objnum){    
	int index = objnum % HASH_TBL_SIZE;

	Object* target = pHashTableEnt[index].pHead;
	int i;
	for (i = 0; i < pHashTableEnt[index].elmtCount; i++) {
		if (target->objnum == objnum)
			return target;
		target = target->phNext;
	}

	return NULL;
}

Object* GetObjectFromObjFreeList(){
	Object* target = pFreeListTail;

	if (pFreeListHead == pFreeListTail)
		pFreeListTail = NULL;
	else
		pFreeListTail = target->phPrev;
	

	return target;
}

BOOL DeleteObject(Object* pObj){
	int index = pObj->objnum % HASH_TBL_SIZE;

	if (pObj->objnum == pHashTableEnt[index].pHead->objnum) {
		Object* pNext = pObj->phNext;
		pHashTableEnt[index].pHead = pNext;
	}
	else if (pObj->objnum == pHashTableEnt[index].pTail->objnum) {
		Object* pPrev = pObj->phPrev;
		pHashTableEnt[index].pTail = pPrev;
	}
	else {
		Object* pNext = pObj->phNext;
		Object* pPrev = pObj->phPrev;
		pPrev->phNext = pNext;
		pNext->phPrev = pPrev;
	}

	
	pHashTableEnt[index].elmtCount--;

	
	return 1;
}

void InsertObjectIntoObjFreeList(Object* pObj){
	pObj = (Object*)malloc(sizeof(Object));
	pObj->objnum = OBJ_INVALID;

	if (pFreeListTail == NULL) {
		pFreeListHead = pObj;
		pFreeListTail = pObj;
	}
	else {
		Object* pHead = pFreeListHead;
		pHead->phPrev = pObj;
		pFreeListHead = pObj;
	}
}

