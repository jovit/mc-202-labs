#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "HashTable.h"

#define WHITE 0xFFFFFF

typedef struct {
    int width, height;
    int **pixels;
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
    for (i = 0; i < img->height; i++) {
        assert(img->pixels[i] = malloc(sizeof(**img->pixels) * img->width));
        for (j = 0; j < img->width; j++) {
            assert(scanf("%d%d%d", &r, &g, &b)==3);
            img->pixels[i][j] = (r << 16) + (g << 8) + b;
        }
    }
    return img;
}

void free_image(Image *img) {
    int i;
    for (i = 0; i < img->height; i++)
        free(img->pixels[i]);
    free(img->pixels);
    free(img);
}

unsigned long hash_pixel(int color, int x, int y) {
    unsigned long hash;

    hash = (unsigned long) color;
    hash = hash * 31 + x;
    hash = hash * 31 + y;

    return hash;
}

void flood_insert(HashTable *graph, int **pixels, int color, int width, int height, unsigned long *inital_pixel_key, int currentX, int currentY) {

    if ( currentX >= 0 && currentY >= 0 && currentX < width
         && currentY < height && pixels[currentY][currentX] != INT_MAX && pixels[currentY][currentX] == color) {
        add_to_hash_table(graph, color, inital_pixel_key, hash_pixel(color, currentX, currentY));
        pixels[currentY][currentX] = INT_MAX;

        printf("%d %d\n", currentX, currentY);

        flood_insert(graph, pixels, color, width, height, inital_pixel_key, currentX+1, currentY);
        flood_insert(graph, pixels, color, width, height, inital_pixel_key, currentX-1, currentY);
        flood_insert(graph, pixels, color, width, height, inital_pixel_key, currentX, currentY+1);
        flood_insert(graph, pixels, color, width, height, inital_pixel_key, currentX, currentY-1);
    }
}

HashTable *generate_graph(Image *image) {
    int i, j;
    unsigned long *another_key;
    HashTable *graph = create_hash_table(image->height * image->height);

    for (i = 0; i < image->height; i++) {
        for (j = 0; j < image->width; j++) {
            if (image->pixels[i][j] != INT_MAX) {
                another_key = malloc(sizeof(unsigned long));
                *another_key = hash_pixel(image->pixels[i][j], i, j);
                flood_insert(graph, image->pixels, image->pixels[i][j], image->width, image->height, another_key, j, i);
                free(another_key);
            }
        }

    }

    return graph;
}

int main(void) {
    HashTable *graph;

    Image *img = read_image();

    graph = generate_graph(img);

    free_image(img);
    free_hash_table(graph);

    return 0;
}
