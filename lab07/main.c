#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"
#include "Heap.h"
#include "IntList.h"

int find_next_occurrence(int *array, int size, int start, int value) {
    int i;

    for (i = start; i < size; i++) {
        if (array[i] == value) {
            break;
        }
    }

    return i;
}

long hash(int i) {
    return i*2654435761 % 4294967296;
}

int add_to_cache(IntList **cache, int cache_size, int key) {
    long position = hash(key) % cache_size;
    add_to_list(cache[position], key);
}

char contain_in_cache(IntList **cache, int cache_size, int key) {
    long position = hash(key) % cache_size;
    list_contains(cache[position], key);
}

int remove_from_cache(IntList **cache, int cache_size, int key) {
    long position = hash(key) % cache_size;
    remove_from_list(cache[position], key);
}

int main(void) {
    int cache_size, number_of_elements, number_of_accesses;
    int i;
    int value_read;
    int *accesses;
    IntList **cache;
    HeapNode node;
    Heap *priority_queue;
    int cache_switch_count = 0;
    int values_in_cache = 0;

    scanf("%d %d %d", &cache_size, &number_of_elements, &number_of_accesses);

    cache = malloc(sizeof(IntList*) * cache_size);

    for (i = 0; i < cache_size; i++) {
        cache[i] = create_list();
    }

    priority_queue = create_heap(number_of_elements);

    accesses = malloc(sizeof(int)*number_of_accesses);
    validate_malloc(accesses);

    for (i = 0;  i <  number_of_accesses; i++) {
        scanf(" %d", &value_read);
        accesses[i] = value_read;
    }

    if (cache_size > number_of_accesses) {
        printf("%d", cache_size);
    } else {
        for (i = 0; i < number_of_accesses; i++) {
            if (!contain_in_cache(cache, cache_size, accesses[i])){
                if (values_in_cache < cache_size) {
                    values_in_cache++;
                    add_to_cache(cache, cache_size, accesses[i]);
                    node.key = find_next_occurrence(accesses, number_of_accesses, i+1, accesses[i]);
                    node.value = accesses[i];
                    insert(priority_queue, node);
                } else {
                    remove_from_cache(cache, cache_size, remove_max(priority_queue).value);
                    add_to_cache(cache, cache_size, accesses[i]);
                    node.key = find_next_occurrence(accesses, number_of_accesses, i+1, accesses[i]);
                    node.value = accesses[i];
                    insert(priority_queue, node);
                }

                cache_switch_count++;
            }
        }
    }

    printf("%d", cache_switch_count);

    free(accesses);
    free_heap(priority_queue);
    for (i = 0; i < cache_size; i++) {
        free_list(cache[i]);
    }
    free(cache);

    return 0;
}