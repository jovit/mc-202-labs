#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "Utils.h"
#include "TreeAVL.h"
#include "IntList.h"

long hash(char str[49]) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

long get_next_word(long *phrase, long *text, int phrase_size, int text_size, int first_index) {
    char phrase_matches = 1;
    int i;

    for (i = first_index; i < first_index + phrase_size; i++) {
        if (i == text_size) {
            phrase_matches = 0;
            break;
        }

        if (phrase[i-first_index] != text[i]) {
            phrase_matches = 0;
            break;
        }
    }

    if (i == text_size) {
        phrase_matches = 0;
    }

    if (phrase_matches) {
        return text[i];
    } else {
        return 0;
    }
}

int main(void) {
    int number_of_words, number_of_rounds, number_of_participants;
    int i, j;
    int total_occurrence_count;
    long *hashed_text;
    long *current_phrase;
    long next_word;
    int number_of_words_in_phrase;
    int *players_total_score;
    int *current_round_score;
    char someone_made_points;
    TreeAVL *current_word_occurrences;
    IntList *current_indexes;
    IntListNode *current_index;
    HashTable *hash_table;
    char word_read[49];

    scanf("%d", &number_of_words);

    hash_table = create_hash_table(number_of_words * 2);

    hashed_text = malloc(sizeof(long) * number_of_words);
    validate_malloc(hashed_text);

    for (i = 0; i < number_of_words; i++) {
        scanf("%s", word_read);
        hashed_text[i] = hash(word_read);
        add_to_hash_table(hash_table, i, hashed_text[i]);
    }

    scanf("%d %d", &number_of_rounds, &number_of_participants);

    players_total_score = malloc(sizeof(int) * number_of_participants);
    validate_malloc(players_total_score);

    for (i = 0; i < number_of_participants; i++) {
        players_total_score[i] = 0;
    }

    current_round_score = malloc(sizeof(int) * number_of_participants);
    validate_malloc(current_round_score);

    for (i = 0; i < number_of_rounds; i++) {
        scanf("%d", &number_of_words_in_phrase);

        current_phrase = malloc(sizeof(long) * number_of_words_in_phrase);
        validate_malloc(current_phrase);
        current_word_occurrences = create_tree();

        for (j = 0; j < number_of_words_in_phrase; j++) {
            scanf("%s", word_read);
            current_phrase[j] = hash(word_read);
        }

        current_indexes = get_key(hash_table, current_phrase[0]);
        current_index = current_indexes->root;

        while (current_index != NULL) {
            next_word = get_next_word(current_phrase, hashed_text, number_of_words_in_phrase, number_of_words, current_index->value);

            if (next_word) {
                insert_to_tree(current_word_occurrences, next_word);
            }

            current_index = current_index->next;
        }

        someone_made_points = 0;

        for (j = 0; j < number_of_participants; j++) {
            scanf("%s", word_read);
            current_round_score[j] = get_count(current_word_occurrences, hash(word_read)) * 100;
            if (current_round_score[j] > 0) {
                someone_made_points = 1;
            }
        }

        if (someone_made_points) {
            total_occurrence_count = get_total_count(current_word_occurrences);
            for (j = 0; j < number_of_participants; j++) {
                if (current_round_score[j] == 0) {
                    current_round_score[j] -= total_occurrence_count * 10;
                }

                players_total_score[j] += current_round_score[j];

                if (players_total_score[j] < 0) {
                    players_total_score[j] = 0;
                }
            }
        }

        printf("Rodada %d: ", i + 1);

        for (j = 0; j < number_of_participants-1; j++) {
            printf("%4d ", players_total_score[j]);
        }
        printf("%4d\n", players_total_score[number_of_participants-1]);

        free(current_phrase);
        free_tree(current_word_occurrences);
    }

    free_hash_table(hash_table);
    free(hashed_text);
    free(players_total_score);
    free(current_round_score);
}