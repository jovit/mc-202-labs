#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"

long hash(char str[49]) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

int main(void) {
    int number_of_words, number_of_rounds, number_of_participants;
    int i, j;
    long *hashed_text;
    long *current_phrase;
    int number_of_words_in_phrase;
    HashTable *hash_table;
    char word_read[49];

    scanf("%d", &number_of_words);

    hash_table = create_hash_table(number_of_words * 2);

    hashed_text = malloc(sizeof(long) * number_of_words);

    for (i = 0; i < number_of_words; i++) {
        scanf("%s", word_read);
        hashed_text[i] = hash(word_read);
        add_to_hash_table(hash_table, i, hashed_text[i]);
    }

    scanf("%d %d", &number_of_rounds, &number_of_participants);

    for (i = 0; i < number_of_rounds; i++) {
        scanf("%d", &number_of_words_in_phrase);
        for (j = 0; j < number_of_words_in_phrase; j++) {
            scanf("%s", word_read);
            current_phrase[i] = hash(word_read);
        }
    }

    free_hash_table(hash_table);

}