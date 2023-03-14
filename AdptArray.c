//
// Created by Nikita Breslavsky on 13/03/2023.
//
#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct AdptArray_ {
    PElement *array;
    int size;
    COPY_FUNC copy;
    DEL_FUNC delete;
    PRINT_FUNC print;
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete, PRINT_FUNC print) {
    PAdptArray newAdptArray = (PAdptArray) malloc(sizeof(AdptArray));
    if (newAdptArray == NULL) {
        return NULL;
    }
    newAdptArray->array = NULL;
    newAdptArray->size = 0;
    newAdptArray->copy = copy;
    newAdptArray->delete = delete;
    newAdptArray->print = print;
    return newAdptArray;
};

void DeleteAdptArray(PAdptArray pAdptArray) {
    if (pAdptArray == NULL) return;
    for (int i = 0; i < pAdptArray->size; i++) {
        if ((pAdptArray->array)[i] != NULL) pAdptArray->delete((pAdptArray->array)[i]);
        (pAdptArray->array)[i] = NULL;
    }
    free(pAdptArray);
    pAdptArray = NULL;
};

Result SetAdptArrayAt(PAdptArray pAdptArray, int index, PElement pElement) {
    if (pAdptArray == NULL) return FAIL;
    if (pAdptArray->size <= index){
        pAdptArray->array = (PElement*) realloc(pAdptArray->array, (index + 1) * sizeof(PElement));
        if (pAdptArray->array == NULL) return FAIL;
    }
    if ((pAdptArray->array)[index] != NULL) pAdptArray->delete((pAdptArray->array)[index]);
    PElement elementCopy = pAdptArray->copy(pElement);
    (pAdptArray->array)[index] = elementCopy;
    return SUCCESS;
};

PElement GetAdptArrayAt(PAdptArray pAdptArray, int index) {
    if (pAdptArray == NULL || pAdptArray->size <= index) return NULL;
    return pAdptArray->copy((pAdptArray->array)[index]);
};

int GetAdptArraySize(PAdptArray pAdptArray) {
    if (pAdptArray == NULL) return -1;
    return pAdptArray->size;
};

void PrintDB(PAdptArray pAdptArray) {
    if (pAdptArray == NULL) return;
    for (int i = 0; i < pAdptArray->size; i++) {
        if ((pAdptArray->array)[i] != NULL) pAdptArray->print((pAdptArray->array)[i]);
    }
};
