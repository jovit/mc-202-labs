#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Heap.h"

#define WHITE 0xFFFFFF

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

void free_image(Image *img) {
    int i;
    for (i = 0; i < img->height; i++) {
        free(img->pixels[i]);
        free(img->has_searched[i]);
    }

    free(img->pixels);
    free(img->has_searched);
    free(img);
}


int main(void) {
    Heap *queue;
    HeapNode heap_node;
    int current_distance;
    int current_x, current_y;

    Image *img = read_image();

    queue = create_heap(img->height * img->width);

    heap_node.key = 0;
    heap_node.x = img->white_x;
    heap_node.y = img->white_y;
    insert(queue, heap_node);

    while (queue->size > 0) {
        heap_node = remove_min(queue);
        current_x = heap_node.x;
        current_y = heap_node.y;
        current_distance = heap_node.key;

        img->has_searched[current_y][current_x] = 1;

        if (current_x > 0 && !img->has_searched[current_y][current_x - 1]) {
            heap_node.x = current_x - 1;
            heap_node.y = current_y;
            heap_node.key = current_distance;

            if (img->pixels[heap_node.y][heap_node.x] != img->pixels[current_y][current_x]) {
                heap_node.key += 1;
            }

            insert(queue, heap_node);
        }

        if (current_x < img->width - 1 && !img->has_searched[current_y][current_x + 1]) {
            heap_node.x = current_x + 1;
            heap_node.y = current_y;
            heap_node.key = current_distance;

            if (img->pixels[heap_node.y][heap_node.x] != img->pixels[current_y][current_x]) {
                heap_node.key += 1;
            }

            insert(queue, heap_node);
        }

        if (current_y > 0 && !img->has_searched[current_y - 1][current_x]) {
            heap_node.x = current_x ;
            heap_node.y = current_y - 1;
            heap_node.key = current_distance;

            if (img->pixels[heap_node.y][heap_node.x] != img->pixels[current_y][current_x]) {
                heap_node.key += 1;
            }

            insert(queue, heap_node);
        }

        if (current_y < img->height - 1 && !img->has_searched[current_y + 1][current_x]) {
            heap_node.x = current_x;
            heap_node.y = current_y + 1;
            heap_node.key = current_distance;

            if (img->pixels[heap_node.y][heap_node.x] != img->pixels[current_y][current_x]) {
                heap_node.key += 1;
            }

            insert(queue, heap_node);
        }

        if (img->pixels[current_y][current_x] == WHITE && current_distance > 0) {
            printf("Maria deve memorizar %d regioes.", current_distance - 1);
            break;
        }
    }

    free_image(img);
    free_heap(queue);

    return 0;
}
