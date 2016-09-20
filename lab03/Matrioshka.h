#ifndef MARIOSHKA_H
#define MARIOSHKA_H

enum MatrioshkaColor {
    BLUE,
    RED
};

typedef struct {
    int value;
    enum MatrioshkaColor color;
    int blue_child;
} Matrioshka;

#endif