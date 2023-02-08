/**
*
* @Name : hash_fixed.c
*
**/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_fixed.h"

unsigned HashIndex(const char* key) {
    unsigned sum = 0;
    for (size_t i = 0; i < strlen(key); i++){
        sum += key[i];
    }
    return sum % MAP_MAX;
}

HashMap* HashInit() {
    HashMap *map = malloc(sizeof(HashMap));
    if(map == NULL){
        perror("malloc error");
        exit(1);
    }
    memset(map->data, 0, sizeof(map->data));
    return map;
}

void HashAdd(HashMap *map,PairValue *value) {
    unsigned idx = HashIndex(value->KeyName);
    
    value->Next = map->data[idx];
    map->data[idx] = value;
}

PairValue* HashFind(HashMap *map, const char* key) {
    unsigned idx = HashIndex(key);
    
    for( PairValue* val = map->data[idx]; val != NULL; val = val->Next ) {
        if (strcmp(val->KeyName, key) == 0) // i replaced strcpy with strcmp
            return val;
    }
    
    return NULL; 
}

void HashDelete(HashMap *map, const char* key) {
    unsigned idx = HashIndex(key);
    
    PairValue* prev = NULL;
    for( PairValue* val = map->data[idx]; val != NULL; prev = val, val = val->Next ) {
        if (strcmp(val->KeyName, key) == 0) { // i replaced strcpy with strcmp
            if (prev)
                prev->Next = val->Next;
            else
                map->data[idx] = val->Next;
            break;
        }
    }
}

void HashDump(HashMap *map) {
    for( unsigned i = 0; i < MAP_MAX; i++ ) {
        for( PairValue* val = map->data[i]; val != NULL; val = val->Next ) {
            printf("KeyName: %s, ValueCount: %d\
