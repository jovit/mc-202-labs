#include <stdio.h>
#include <stdlib.h>

long hash(char str[49]) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

int main(void) {
    int number_of_words;
    int i;
    long *hashed_text;
    char word_read[49];

    scanf("%d", &number_of_words);

    hashed_text = malloc(sizeof(long) * number_of_words);

    for (i = 0; i < number_of_words; i++) {
        scanf("%s", word_read);
        hashed_text[i] = hash(word_read);
    }
}