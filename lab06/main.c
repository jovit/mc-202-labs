#include <stdio.h>
#include "Ingredient.h"
#include "OrderList.h"

int main(void) {
    int current_time;
    char ingredient_read[INGREDIENT_NAME_MAX_SIZE];
    char char_read;
    OrderList *order_list;
    IngredientList *ingredient_list;
    int last_time = 0;
    int current_ticket = 1;

    order_list = create_order_list();
    // while hasn't finished reading values
    while (scanf("%d%c", &current_time, &char_read) != EOF) {
        ingredient_list = create_ingredient_list();
        while (char_read !='\n') {
            scanf("%s", ingredient_read);
            scanf("%c", &char_read);
            add_to_ingredient_list(ingredient_list, create_ingredient(ingredient_read, 0));
        }
        add_to_order_list(order_list, current_ticket, ingredient_list);
        current_ticket++;
    }

    free_order_list(order_list);

    return 0;
}