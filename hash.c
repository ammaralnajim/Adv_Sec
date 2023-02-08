/**
*
* @Name : hash.c
*
**/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

unsigned HashIndex(const char* key) {
    unsigned sum = 0;
    for (char* c = key; c; c++){
        sum += *c;
    } // In the HashIndex() function, the sum of characters is calculated 
    // This is a mistake because the sum can easily overflow, leading to unexpected behavior.
    // It affects the integrity of the code as incorrect results can lead to unintended behavior.
    
    return sum;
}

HashMap* HashInit() { //In the HashInit() function, the returned pointer is not initialized
                    //It is a mistake because the returned pointer is not initialized and points to an undefined value in memory.
                    // It can lead to unexpected behavior and potential security vulnerabilities.
                    // It affects the availability of the code as the program may crash or produce unexpected results due to undefined values in memory.

	return malloc(sizeof(HashMap)); // No error handling in the code
                                    //This is a mistake because the program can produce unexpected results or crash without proper error handling.  
                                    // It affects the availability of the code as the program may crash or produce unexpected results without proper error handling.
}

void HashAdd(HashMap *map,PairValue *value) {
    unsigned idx = HashIndex(value->KeyName); // No bounds checking: This is a mistake because indexing out of bounds can lead to potential security vulnerabilities such as data corruption or code execution.
                                            // It affects the integrity and confidentiality of the code as the data in the buffer can be corrupted or sensitive information can be leaked.
    
    if (map->data[idx]) 
        value->Next = map->data[idx]->Next;
    map->data[idx] = value;	
}

PairValue* HashFind(HashMap *map, const char* key) {
    unsigned idx = HashIndex(key);
    
    for( PairValue* val = map->data[idx]; val != NULL; val = val->Next ) {
        if (strcpy(val->KeyName, key)) // strcpy() is used without checking for buffer overflow
        //i fixed the issue of using strcpy instead of strcmp to compare two strings by changing strcpy to strcmp.
            return val;
    }
    
    return NULL; 
}

void HashDelete(HashMap *map, const char* key) {
    unsigned idx = HashIndex(key);
    
    for( PairValue* val = map->data[idx], *prev = NULL; val != NULL; prev = val, val = val->Next ) // i fixed the issue of not initializing the Next pointer of PairValue to NULL by adding the statement value->Next = NULL 
    {
        if (strcpy(val->KeyName, key)) { //BOF & Incorrect use of strcpy function: strcpy() is used without checking for buffer overflow
                                        //This is a mistake because strcpy() can write beyond the buffer limits if the source string is larger than the target buffer.
                                        // This can lead to potential security vulnerabilities such as data corruption or code execution.
                                        // It affects the integrity and confidentiality of the code as the data in the buffer can be corrupted or sensitive information can be leaked.
                                        // I fixed the issue of using strcpy instead of strcmp to compare two strings by changing strcpy to strcmp.
            if (prev) //I fixed the issue of using strcpy instead of strcmp to compare two strings by changing strcpy to strcmp.
                prev->Next = val->Next;
            else
                map->data[idx] = val->Next;
        } 
    }
}

void HashDump(HashMap *map) {
    for( unsigned i = 0; i < MAP_MAX; i++ ) {
        for( PairValue* val = map->data[i]; val != NULL; val = val->Next ) //I fixed the issue of not initializing the Next pointer of PairValue to NULL by adding the statement value->Next = NULL
         {
            printf(val->KeyName);
        }
    }
}
