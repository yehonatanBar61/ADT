#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"
#include "book.h"



typedef struct AdptArray_ {
    int sizeArray;
    PElement* pElemArr;
    //pointers for functions of the ADT
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
} AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc){
    PAdptArray newParray = (PAdptArray) malloc(sizeof(AdptArray));
    // Check for allocation failure
    if (newParray == NULL) 
        return NULL;
    newParray->sizeArray = 0;
    newParray->pElemArr = NULL;
    newParray->copyFunc = copyFunc;
    newParray->delFunc = delFunc;
    newParray->printFunc = printFunc;
    return newParray;
}

void DeleteAdptArray(PAdptArray arryP){
    if (arryP == NULL) 
        return;
    for (int i = 0; i < arryP->sizeArray; ++i) {
        if (arryP->pElemArr[i] != NULL) 
            arryP->delFunc(arryP->pElemArr[i]);     
        else
            free(arryP->pElemArr[i]);
        
    }
    free(arryP->pElemArr);
    free(arryP);
}

Result SetAdptArrayAt(PAdptArray Parray, int index, PElement PnewElement) {
    if (Parray == NULL || index < 0)  
        return FAIL;
    if (index >= Parray->sizeArray){
        Parray->pElemArr = (PElement*) realloc(Parray->pElemArr, (index+1)*sizeof(PnewElement));
        // Check for allocation failure
        if (Parray->pElemArr == NULL)
            return FAIL;
        for (int i = Parray->sizeArray; i < index + 1; i++) {
            Parray->pElemArr[i] = NULL;
        }
        Parray->sizeArray = index + 1; 
    }
    // If an element already exists at the index, delete it using delFunc
    if (Parray->pElemArr[index] != NULL) 
        Parray->delFunc(Parray->pElemArr[index]);
    // Copy the new element using copyFunc and set it at the given index
    Parray->pElemArr[index] = Parray->copyFunc(PnewElement);
    return SUCCESS;
}


PElement GetAdptArrayAt(PAdptArray Parray, int index){
    if (Parray == NULL || Parray->sizeArray <= index ||Parray->pElemArr[index] == NULL || index < 0) {
        return NULL;
    }
    return Parray->copyFunc(Parray->pElemArr[index]);
}

int GetAdptArraySize(PAdptArray Parray) {
    if (Parray == NULL)
        return -1;
    return  Parray->sizeArray;
}

void PrintDB(PAdptArray Parray){
    if (Parray == NULL)
        return;
    for (int i = 0; i < Parray->sizeArray; i++) {
        if (Parray->pElemArr[i] != NULL)
            Parray->printFunc(Parray->pElemArr[i]);    
    }
}
