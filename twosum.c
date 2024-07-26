//using two pointer method

#include <stdio.h>
#include <stdlib.h>

// Function to find the indices of the two numbers that add up to the target
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }
return NULL;
}



//Using hash map
#include <stdio.h>
#include <stdlib.h>

// Define a structure for the hash table entries
typedef struct {
    int key;
    int value;
} HashEntry;

// Define a structure for the hash table
typedef struct {
    HashEntry* entries;
    int size;
} HashTable;

// Function to create a hash table
HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->entries = (HashEntry*)malloc(size * sizeof(HashEntry));
    table->size = size;
    for (int i = 0; i < size; i++) {
        table->entries[i].key = -1;  // Use -1 to indicate an empty slot
    }
    return table;
}

// Hash function to get the index for a key
int hash(int key, int size) {
    return abs(key) % size;
}

// Function to insert a key-value pair into the hash table
void insert(HashTable* table, int key, int value) {
    int index = hash(key, table->size);
    while (table->entries[index].key != -1) {
        index = (index + 1) % table->size;
    }
    table->entries[index].key = key;
    table->entries[index].value = value;
}

// Function to search for a key in the hash table
int search(HashTable* table, int key) {
    int index = hash(key, table->size);
    while (table->entries[index].key != -1) {
        if (table->entries[index].key == key) {
            return table->entries[index].value;
        }
        index = (index + 1) % table->size;
    }
    return -1;  // Return -1 if the key is not found
}

// Function to find the indices of the two numbers that add up to the target
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashTable* table = createHashTable(numsSize);
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int complementIndex = search(table, complement);
        if (complementIndex != -1) {
            result[0] = complementIndex;
            result[1] = i;
            free(table->entries);
            free(table);
            return result;
        }
        insert(table, nums[i], i);
    }

    free(table->entries);
    free(table);
    return NULL;  // This line should never be reached if there is exactly one solution
}
