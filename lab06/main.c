#include <stdio.h>
#include "Ingredient.h"
#include "OrderList.h"
#include "SplayTree.h"

int main(void) {
    int current_time;
    char can_prepare_pizza;
    int i;
    char ingredient_read[INGREDIENT_NAME_MAX_SIZE];
    OrderList *order_list; // list of orders queued
    OrderList *waiting_to_be_attended; // list of people waiting to be attended
    IngredientList *ingredient_list; // list of ingredients read
    SplayTree *splay_tree;
    int last_time = 0;
    int current_ticket = 1;
    int in_the_oven = 0;
    OrderListNode *current_order_node;
    IngredientListNode *current_ingredient_node;

    // initiate data structs
    order_list = create_order_list();
    waiting_to_be_attended = create_order_list();
    splay_tree = create_splay_tree();


    while (scanf("%d", &current_time) == 1) {
        ingredient_list = create_ingredient_list();
        // read the order
        while (scanf("%*[ ]%[^ \r\n]", ingredient_read) == 1) {
            add_to_ingredient_list(ingredient_list, create_ingredient(ingredient_read, 0));
        }
        // update  the orders from that passed between the last person arriving and the current
        for (i = last_time + 1; i <= (current_time); i++) {
            if (in_the_oven) { // if there's a pizza in the oven, now it's ready
                printf("%d ", in_the_oven);
                in_the_oven = 0;
            }

            // check the queued orders
            for (current_order_node = order_list->first;
                 current_order_node != NULL; current_order_node = current_order_node->next) {
                can_prepare_pizza = 1;
                // check if all ingredients are available
                for (current_ingredient_node = current_order_node->ingredients->first; current_ingredient_node != NULL;
                     current_ingredient_node = current_ingredient_node->next) {
                    if (!check_if_ingredient_is_done(splay_tree, current_ingredient_node->value->name, i)) {
                        can_prepare_pizza = 0;
                        break;
                    }
                }

                if (can_prepare_pizza) {
                    // if a pizza can be prepared, uses the needed ingredients
                    for (current_ingredient_node = current_order_node->ingredients->first;
                         current_ingredient_node != NULL;
                         current_ingredient_node = current_ingredient_node->next) {
                        use_ingredient(splay_tree, current_ingredient_node->value->name, i);
                    }

                    in_the_oven = current_order_node->order; // put pizza in the oven
                    remove_order(order_list, in_the_oven);
                    break;
                }
            }

            if (!in_the_oven) { // if there's no pizza in the oven, attend the next customer
                while (waiting_to_be_attended->first != NULL) { // while there are people waiting
                    can_prepare_pizza = 1;
                    // check if the pizza can be done
                    for (current_ingredient_node = waiting_to_be_attended->first->ingredients->first; current_ingredient_node != NULL;
                         current_ingredient_node = current_ingredient_node->next) {
                        if (!can_use_ingredient(splay_tree, current_ingredient_node->value->name, i)) {
                            can_prepare_pizza = 0;
                        }
                    }

                    if (can_prepare_pizza) {
                        for (current_ingredient_node = waiting_to_be_attended->first->ingredients->first; current_ingredient_node != NULL;
                             current_ingredient_node = current_ingredient_node->next) {
                            use_ingredient(splay_tree, current_ingredient_node->value->name, i);
                        }
                        in_the_oven = waiting_to_be_attended->first->order;
                        remove_order(waiting_to_be_attended, in_the_oven);
                        break;
                    } else { // if not add to the queue of orders wainting to be made
                        add_to_order_list(order_list, waiting_to_be_attended->first->order, waiting_to_be_attended->first->ingredients);
                        remove_order_without_ingredients(waiting_to_be_attended, waiting_to_be_attended->first->order);
                    }
                }

            }
        }

        // add the current customer the waiting line
        add_to_order_list(waiting_to_be_attended, current_ticket, ingredient_list);
        if (!in_the_oven) { // if there's no pizza in the oven, check if he can be attended
            while (waiting_to_be_attended->first != NULL) {
                can_prepare_pizza = 1;
                for (current_ingredient_node = waiting_to_be_attended->first->ingredients->first; current_ingredient_node != NULL;
                     current_ingredient_node = current_ingredient_node->next) {
                    if (!can_use_ingredient(splay_tree, current_ingredient_node->value->name, current_time)) {
                        can_prepare_pizza = 0;
                    }
                }

                if (can_prepare_pizza) {
                    for (current_ingredient_node = waiting_to_be_attended->first->ingredients->first; current_ingredient_node != NULL;
                         current_ingredient_node = current_ingredient_node->next) {
                        use_ingredient(splay_tree, current_ingredient_node->value->name, current_time);
                    }
                    in_the_oven = waiting_to_be_attended->first->order;
                    remove_order(waiting_to_be_attended, in_the_oven);
                    break;
                } else { // else put him in the orders queue
                    add_to_order_list(order_list, waiting_to_be_attended->first->order, waiting_to_be_attended->first->ingredients);
                    remove_order_without_ingredients(waiting_to_be_attended, waiting_to_be_attended->first->order);
                }
            }

        }


        current_ticket++;
        last_time = current_time;
    }

    i = current_time + 1;
    // while there are pizzas to be done, increment time one by one updating the status of the pizzas
    while (order_list->first != NULL || waiting_to_be_attended->first != NULL) {
        if (in_the_oven) {
            printf("%d ", in_the_oven);
            in_the_oven = 0;
        }

        for (current_order_node = order_list->first;
             current_order_node != NULL; current_order_node = current_order_node->next) {
            can_prepare_pizza = 1;
            for (current_ingredient_node = current_order_node->ingredients->first; current_ingredient_node != NULL;
                 current_ingredient_node = current_ingredient_node->next) {
                if (!check_if_ingredient_is_done(splay_tree, current_ingredient_node->value->name, i)) {
                    can_prepare_pizza = 0;
                    break;
                }
            }

            if (can_prepare_pizza) {
                for (current_ingredient_node = current_order_node->ingredients->first;
                     current_ingredient_node != NULL;
                     current_ingredient_node = current_ingredient_node->next) {
                    use_ingredient(splay_tree, current_ingredient_node->value->name, i);
                }

                in_the_oven = current_order_node->order;
                remove_order(order_list, in_the_oven);
                break;
            }
        }

        if (!in_the_oven) {
            while (waiting_to_be_attended->first != NULL) {
                can_prepare_pizza = 1;
                for (current_ingredient_node = waiting_to_be_attended->first->ingredients->first; current_ingredient_node != NULL;
                     current_ingredient_node = current_ingredient_node->next) {
                    if (!can_use_ingredient(splay_tree, current_ingredient_node->value->name, i)) {
                        can_prepare_pizza = 0;
                    }
                }

                if (can_prepare_pizza) {
                    for (current_ingredient_node = waiting_to_be_attended->first->ingredients->first; current_ingredient_node != NULL;
                         current_ingredient_node = current_ingredient_node->next) {
                        use_ingredient(splay_tree, current_ingredient_node->value->name, i);
                    }
                    in_the_oven = waiting_to_be_attended->first->order;
                    remove_order(waiting_to_be_attended, in_the_oven);
                    break;
                } else {
                    add_to_order_list(order_list, waiting_to_be_attended->first->order, waiting_to_be_attended->first->ingredients);
                    remove_order_without_ingredients(waiting_to_be_attended, waiting_to_be_attended->first->order);
                }
            }
        }

        i++;
    }

    if (in_the_oven) { // print the last pizza in the oven if present
        printf("%d ", in_the_oven);
    }

    // free the data structures
    free_order_list(order_list);
    free_order_list(waiting_to_be_attended);
    free_splay_tree(splay_tree);

    return 0;
}