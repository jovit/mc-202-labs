#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"
#include "Heap.h"

int find_next_occurrence(int *array, int size, int start, int value) {
    int i;

    for (i = start; i < size; i++) {
        if (array[i] == value) {
            break;
        }
    }

    return i;
}

void add_to_cache(char *cache, int key) {
    cache[key] = 1;
}

char contain_in_cache(char *cache, int key) {
    return cache[key];
}

void remove_from_cache(char *cache, int key) {
    cache[key] = 0;
}

int main(void) {
    int cache_size, number_of_elements, number_of_accesses;
    int i;
    int value_read;
    int *accesses;
    char *cache;
    HeapNode node;
    Heap *priority_queue;
    int cache_switch_count = 0;
    int values_in_cache = 0;

    scanf("%d %d %d", &cache_size, &number_of_elements, &number_of_accesses);

    cache = malloc(sizeof(char) * number_of_elements);

    for (i = 0; i < number_of_elements; i++) {
        cache[i] = 0;
    }

    priority_queue = create_heap(cache_size);

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
            if (!contain_in_cache(cache, accesses[i])){
                if (values_in_cache < cache_size) {
                    values_in_cache++;
                    add_to_cache(cache, accesses[i]);
                    node.key = find_next_occurrence(accesses, number_of_accesses, i+1, accesses[i]);
                    node.value = accesses[i];
                    insert(priority_queue, node);
                } else {
                    remove_from_cache(cache, remove_max(priority_queue).value);
                    add_to_cache(cache, accesses[i]);
                    node.key = find_next_occurrence(accesses, number_of_accesses, i+1, accesses[i]);
                    node.value = accesses[i];
                    insert(priority_queue, node);
                }

                cache_switch_count++;
            } else {
                set_priority(priority_queue, accesses[i], find_next_occurrence(accesses, number_of_accesses, i+1, accesses[i]));
            }
        }
    }

    printf("%d", cache_switch_count);

    free(accesses);
    free_heap(priority_queue);
    free(cache);

    return 0;
}