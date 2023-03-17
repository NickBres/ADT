//
// Created by Nikita Breslavsky on 13/03/2023.
//
#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>


struct AdptArray_ {
    PElement *array;
    int size;
    COPY_FUNC copy;
    DEL_FUNC delete;
    PRINT_FUNC print;
};

PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete, PRINT_FUNC print) {
    PAdptArray pAdptArray = (PAdptArray) malloc(sizeof(struct AdptArray_));
    if (pAdptArray == NULL) return NULL;
    pAdptArray->array = NULL;
    pAdptArray->size = 0;
    pAdptArray->copy = copy;
    pAdptArray->delete = delete;
    pAdptArray->print = print;
    return pAdptArray;
};

void DeleteAdptArray(PAdptArray pAdptArray) {
    if (pAdptArray == NULL) return;
    for (int i = 0; i < pAdptArray->size; i++) {
        if (pAdptArray->array[i] != NULL) pAdptArray->delete(pAdptArray->array[i]);
        pAdptArray->array[i] = NULL;
    }
    free(pAdptArray->array);
    free(pAdptArray);
    pAdptArray = NULL;
};

Result SetAdptArrayAt(PAdptArray pAdptArray, int index, PElement pElement) {
    if (pAdptArray == NULL || index < 0) return FAIL;
    if (index >= pAdptArray->size) {
        pAdptArray->array = (PElement *) realloc(pAdptArray->array, (index + 1) * sizeof(PElement));
        if (pAdptArray->array == NULL) return FAIL;
        for (int i = pAdptArray->size; i < index + 1; i++) { // initialize the new elements to NULL
            pAdptArray->array[i] = NULL;
        }
        pAdptArray->size = index + 1;
    }
    if (pAdptArray->array[index] != NULL) pAdptArray->delete(pAdptArray->array[index]);
    pAdptArray->array[index] = pAdptArray->copy(pElement);
    return SUCCESS;
};

PElement GetAdptArrayAt(PAdptArray pAdptArray, int index) {
    if (pAdptArray == NULL || index < 0 || index >= pAdptArray->size || pAdptArray->array[index] == NULL) return NULL;
    return pAdptArray->copy(pAdptArray->array[index]);
};

int GetAdptArraySize(PAdptArray pAdptArray) {
    if (pAdptArray == NULL) return -1;
    return pAdptArray->size;
};

void PrintDB(PAdptArray pAdptArray) {
    if (pAdptArray == NULL) return;
    for (int i = 0; i < pAdptArray->size; i++) {
        if (pAdptArray->array[i] != NULL) pAdptArray->print(pAdptArray->array[i]);
    }
};
