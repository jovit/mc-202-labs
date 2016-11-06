#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"
#include "Heap.h"
#include "Queue.h"

// gets the next position given an positions queue
int find_next_occurrence(Queue *positions, int i, int number_of_accesses) {
    int next_position;

    // if the element doesn't appear in the access anymore
    if (is_queue_empty(positions)) {
        next_position = number_of_accesses;
    } else {
        next_position = dequeue(positions); // get next position
        if (next_position == i) { // if it's the same position of the current, find the next one
            next_position = find_next_occurrence(positions, i, number_of_accesses);
        }
    }

    return next_position;
}

// adds a key to the cache
void add_to_cache(char *cache, int key) {
    cache[key] = 1;
}

// checks if a key is in the cache
char contain_in_cache(char *cache, int key) {
    return cache[key];
}

// removes a key from the cache
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
    Heap *priority_queue; // priority queue with the next positions of the elements in the cache
    Queue **elements_positions; // array of queues of the positions that the element appears
    int cache_switch_count = 0;
    int values_in_cache = 0;

    scanf("%d %d %d", &cache_size, &number_of_elements, &number_of_accesses);

    cache = malloc(sizeof(char) * number_of_elements);
    validate_malloc(cache);

    elements_positions = malloc(sizeof(Queue*) * number_of_elements);
    validate_malloc(elements_positions);

    for (i = 0; i < number_of_elements; i++) {
        cache[i] = 0; // initiates the cache as empty
        elements_positions[i] = create_queue(); // creates queues
        validate_malloc(elements_positions[i]);
    }

    priority_queue = create_heap(cache_size);

    accesses = malloc(sizeof(int) * number_of_accesses);
    validate_malloc(accesses);

    for (i = 0;  i <  number_of_accesses; i++) {
        scanf(" %d", &value_read);
        accesses[i] = value_read; // read all accesses
        queue(elements_positions[value_read], i); // add the position to the queue
    }

    if (cache_size > number_of_accesses) {
        printf("%d", cache_size);
    } else {
        for (i = 0; i < number_of_accesses; i++) {
            if (!contain_in_cache(cache, accesses[i])) { // if the element is not in the cache
                if (values_in_cache < cache_size) { // if the cache is not full
                    values_in_cache++;
                    add_to_cache(cache, accesses[i]);
                    node.key = find_next_occurrence(elements_positions[accesses[i]], i, number_of_accesses);
                    node.value = accesses[i];
                    insert(priority_queue, node);
                } else { // if the cache is full
                    remove_from_cache(cache, remove_max(priority_queue).value); // remove the element with max priority from the cache
                    add_to_cache(cache, accesses[i]); // add the current element to the cache
                    // find the next occurrence of the current element and set as priority of the node
                    node.key = find_next_occurrence(elements_positions[accesses[i]], i, number_of_accesses);
                    node.value = accesses[i];
                    // add the node to the priority queue
                    insert(priority_queue, node);
                }

                cache_switch_count++;
            } else { // if the element is in the cache
                // update it's priority with its next occurrence in the accesses
                set_priority(priority_queue, accesses[i], find_next_occurrence(elements_positions[accesses[i]], i, number_of_accesses));
            }
        }
    }

    printf("%d", cache_switch_count);

    free(accesses);
    free_heap(priority_queue);
    free(cache);
    for (i = 0;  i <  number_of_elements; i++) {
        free_queue(elements_positions[i]);
    }
    free(elements_positions);

    return 0;
}