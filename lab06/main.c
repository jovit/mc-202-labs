#include <stdio.h>
#include "Ingredient.h"
#include "OrderList.h"
#include "SplayTree.h"

int main(void) {
    int current_time;
    char can_prepare_pizza;
    int i;
    char ingredient_read[INGREDIENT_NAME_MAX_SIZE];
    OrderList *order_list;
    OrderList *waiting_to_be_attended;
    IngredientList *ingredient_list;
    SplayTree *splay_tree;
    int last_time = 0;
    int current_ticket = 1;
    int in_the_oven = 0;
    OrderListNode *current_order_node;
    IngredientListNode *current_ingredient_node;

    order_list = create_order_list();
    waiting_to_be_attended = create_order_list();
    splay_tree = create_splay_tree();


    while (scanf("%d", &current_time) == 1) {
        ingredient_list = create_ingredient_list();

        while (scanf("%*[ ]%[^ \r\n]", ingredient_read) == 1) {
            add_to_ingredient_list(ingredient_list, create_ingredient(ingredient_read, 0));
        }

        add_to_order_list(waiting_to_be_attended, current_ticket, ingredient_list);

        for (i = last_time + 1; i <= (current_time); i++) {
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

        }

        can_prepare_pizza = 1;
        if (!in_the_oven) {

            while (waiting_to_be_attended->first != NULL) {
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
                } else {
                    add_to_order_list(order_list, waiting_to_be_attended->first->order, waiting_to_be_attended->first->ingredients);
                    remove_order_without_ingredients(waiting_to_be_attended, waiting_to_be_attended->first->order);
                }
            }

        }

        current_ticket++;
        last_time = current_time;
    }

    i = current_time + 1;
    while (order_list->first != NULL) {
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
                } else {
                    add_to_order_list(order_list, waiting_to_be_attended->first->order, waiting_to_be_attended->first->ingredients);
                    remove_order_without_ingredients(waiting_to_be_attended, waiting_to_be_attended->first->order);
                }
            }

        }

        i++;
    }

    if (in_the_oven) {
        printf("%d", in_the_oven);
    }

    free_order_list(order_list);
    free_order_list(waiting_to_be_attended);
    free_splay_tree(splay_tree);
    return 0;
}