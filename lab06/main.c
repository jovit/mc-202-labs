#include <stdio.h>
#include "Ingredient.h"
#include "OrderList.h"
#include "SplayTree.h"

int main(void) {
    int current_time;
    char can_prepare_pizza;
    int i;
    char ingredient_read[INGREDIENT_NAME_MAX_SIZE];
    char char_read;
    OrderList *order_list;
    IngredientList *ingredient_list;
    SplayTree *splay_tree;
    int last_time = 0;
    int current_ticket = 1;
    int in_the_oven = 0;
    OrderListNode *current_order_node;
    IngredientListNode *current_ingredient_node;

    order_list = create_order_list();
    splay_tree = create_splay_tree();

    //printf("oi");
    // while hasn't finished reading values
    while (scanf("%d%c", &current_time, &char_read) != EOF) {
        if(char_read=='d') {
            break;
        }

        ingredient_list = create_ingredient_list();

        while (char_read != '\n') {
            scanf("%s", ingredient_read);
            scanf("%c", &char_read);
            add_to_ingredient_list(ingredient_list, create_ingredient(ingredient_read, 0));
        }

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
        for (current_ingredient_node = ingredient_list->first; current_ingredient_node != NULL;
             current_ingredient_node = current_ingredient_node->next) {
            if (!can_use_ingredient(splay_tree, current_ingredient_node->value->name, current_time)) {
                can_prepare_pizza = 0;
            }
        }

        if (can_prepare_pizza && !in_the_oven) {
            for (current_ingredient_node = ingredient_list->first; current_ingredient_node != NULL;
                 current_ingredient_node = current_ingredient_node->next) {
                use_ingredient(splay_tree, current_ingredient_node->value->name, current_time);
            }
            in_the_oven = current_ticket;
        } else {
            add_to_order_list(order_list, current_ticket, ingredient_list);
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
        i++;
    }

    if (in_the_oven) {
        printf("%d", in_the_oven);
    }

    free_order_list(order_list);
    free_splay_tree(splay_tree);
    return 0;
}