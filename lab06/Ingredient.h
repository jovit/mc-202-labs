#ifndef INGREDIENT_H
#define INGREDIENT_H

#define INGREDIENT_NAME_MAX_SIZE 100

#define TIME_TO_UNFROZEN 2
#define TIME_TO_STORE 5

typedef struct Ingredient {
    char name[INGREDIENT_NAME_MAX_SIZE];
    int time_taken_out;
} Ingredient;

Ingredient *create_ingredient(char *name, int time_taken_out);
char is_unfrozen(Ingredient *ingredient, int time);
char should_be_stored(Ingredient *ingredient, int time);

#endif
