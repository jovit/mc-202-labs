
#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"

void validate_malloc(void *pointer) {
    if (pointer == NULL) {
        printf("Out of memory");
        exit(1);
    }
}