#include <stdio.h>
#include <HashTable.h>
#include "HashTable.h"

#define WORD_MAX_SIZE 51

unsigned long hash(char str[WORD_MAX_SIZE]) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

int main(void) {
    int number_of_distinct_words, weight, number_of_phrases;
    int number_of_words_in_phrase;
    int i, j;
    HashTable *hashTable;
    char word_read[WORD_MAX_SIZE];

    scanf("%d %d %d", &number_of_distinct_words, &weight, &number_of_phrases);

    hashTable = create_hash_table(number_of_distinct_words * 2);

    for (i = 0; i < number_of_phrases; i++) {
        scanf("%d", &number_of_words_in_phrase);

        for (j = 0; j < number_of_words_in_phrase; j++) {
            scanf(" %s", word_read);
        }
    }

    return 0;
}