#include <stdlib.h>
#include <string.h>
#include "Ingredient.h"
#include "Utils.h"

Ingredient *create_ingredient(char *name, int time_taken_out) {
    Ingredient *new_ingredient = malloc(sizeof(Ingredient));

    validate_malloc(new_ingredient);

    strcpy(new_ingredient->name, name);
    new_ingredient->time_taken_out = time_taken_out;

    return new_ingredient;
}

char is_unfrozen(Ingredient *ingredient, int time) {
    return (time - ingredient->time_taken_out) >= TIME_TO_UNFROZEN;
}

char should_be_stored(Ingredient *ingredient, int time) {
    return (time - ingredient->time_taken_out) > TIME_TO_STORE;
}




