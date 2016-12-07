#include <stdio.h>
#include "HashTable.h"


unsigned long hash(char str[WORD_MAX_SIZE]) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

int main(void) {
    int number_of_distinct_words, weight, number_of_phrases;
    int number_of_words_in_phrase, number_of_phrases_to_generate;
    int i, j;
    unsigned long previous_hash = 0;
    unsigned long start, finish;
    HashTable *hash_table;
    char word_read[WORD_MAX_SIZE];

    scanf("%d %d %d", &number_of_distinct_words, &weight, &number_of_phrases);

    hash_table = create_hash_table(number_of_distinct_words);

    for (i = 0; i < number_of_phrases; i++) {
        scanf("%d", &number_of_words_in_phrase);
        previous_hash = 0;
        for (j = 0; j < number_of_words_in_phrase; j++) {
            scanf(" %s", word_read);
            add_to_hash_table(hash_table, hash(word_read), word_read);

            if (previous_hash) {
                add_connection(hash_table, previous_hash, hash(word_read));
            }

            previous_hash = hash(word_read);
        }
    }

    scanf("%d", &number_of_phrases_to_generate);

    for (i = 0; i < number_of_phrases_to_generate; i++) {
        scanf(" %s", word_read);
        start = hash(word_read);

        scanf(" %s", word_read);
        finish = hash(word_read);

        print_smallest_path(hash_table, start, finish, weight);

        if (i < number_of_phrases_to_generate - 1) {
            printf("\n");
        }
    }



    free_hash_table(hash_table);

    return 0;
}