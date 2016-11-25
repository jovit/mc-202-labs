#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Heap.h"

#define WHITE 0xFFFFFF
#define RESULT_MESSAGE "Maria deve memorizar %d regioes."

typedef struct {
    int width, height;
    int **pixels;
    char **has_searched;
    int white_x, white_y;
} Image;

Image *read_image() {
    Image *img;
    char peek;
    int i, j, r, g, b;
    assert(img = malloc(sizeof(*img)));
    scanf("P3 ");
    while((peek = getchar()) == '#') scanf("%*[^\r\n]%*[\r\n]");
    ungetc(peek,stdin);
    assert(scanf("%d %d %*d", &img->width, &img->height)==2);
    assert(img->pixels = malloc(sizeof(*img->pixels) * img->height));
    assert(img->has_searched = malloc(sizeof(*img->has_searched) * img->height));
    for (i = 0; i < img->height; i++) {
        assert(img->pixels[i] = malloc(sizeof(**img->pixels) * img->width));
        assert(img->has_searched[i] = malloc(sizeof(**img->has_searched) * img->width));
        for (j = 0; j < img->width; j++) {
            assert(scanf("%d%d%d", &r, &g, &b)==3);
            img->pixels[i][j] = (r << 16) + (g << 8) + b;
            img->has_searched[i][j] = 0;
            if (img->pixels[i][j] == WHITE) {
                img->white_x = j;
                img->white_y = i;
            }
        }
    }
    return img;
}

void free_image(Image *image) {
    int i;
    for (i = 0; i < image->height; i++) {
        free(image->pixels[i]);
        free(image->has_searched[i]);
    }

    free(image->pixels);
    free(image->has_searched);
    free(image);
}


int main(void) {
    Heap *queue;
    HeapNode heap_node; // auxiliar
    int current_distance;
    int current_x, current_y;

    Image *image = read_image();

    queue = create_heap(image->height * image->width);

    heap_node.key = 0;
    heap_node.x = image->white_x;
    heap_node.y = image->white_y;
    insert(queue, heap_node);

    while (queue->size > 0) {
        heap_node = remove_min(queue);
        current_x = heap_node.x;
        current_y = heap_node.y;
        current_distance = heap_node.key;

        image->has_searched[current_y][current_x] = 1;

        //check each one of the adjacent pixels, adding them to the queue with the same priority if they
        // have the same color or with increased priority
        if (current_x > 0 && !image->has_searched[current_y][current_x - 1]) {
            heap_node.x = current_x - 1;
            heap_node.y = current_y;
            heap_node.key = current_distance;

            if (image->pixels[heap_node.y][heap_node.x] != image->pixels[current_y][current_x]) {
                heap_node.key += 1;
            }

            insert(queue, heap_node);
        }

        if (current_x < image->width - 1 && !image->has_searched[current_y][current_x + 1]) {
            heap_node.x = current_x + 1;
            heap_node.y = current_y;
            heap_node.key = current_distance;

            if (image->pixels[heap_node.y][heap_node.x] != image->pixels[current_y][current_x]) {
                heap_node.key += 1;
            }

            insert(queue, heap_node);
        }

        if (current_y > 0 && !image->has_searched[current_y - 1][current_x]) {
            heap_node.x = current_x ;
            heap_node.y = current_y - 1;
            heap_node.key = current_distance;

            if (image->pixels[heap_node.y][heap_node.x] != image->pixels[current_y][current_x]) {
                heap_node.key += 1;
            }

            insert(queue, heap_node);
        }

        if (current_y < image->height - 1 && !image->has_searched[current_y + 1][current_x]) {
            heap_node.x = current_x;
            heap_node.y = current_y + 1;
            heap_node.key = current_distance;

            if (image->pixels[heap_node.y][heap_node.x] != image->pixels[current_y][current_x]) {
                heap_node.key += 1;
            }

            insert(queue, heap_node);
        }

        // if found another white area different from the initial one
        if (image->pixels[current_y][current_x] == WHITE && current_distance > 0) {
            printf(RESULT_MESSAGE, current_distance - 1); // the priority - 1 is equal to the distance
            break;
        }
    }

    free_image(image);
    free_heap(queue);

    return 0;
}
