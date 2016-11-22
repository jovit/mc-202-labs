#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

HashTable *generate_graph(Image *image) {
    int i, j;
    HashTable *graph = create_hash_table(image->height * image->height);

    for (i = 0; i < image->width; i++) {
        for (j = 0; j < image->height; j++) {

        }
    }

}

int main(void) {
    Image *img = read_image();

    free_image(img);
    return 0;
}
