#include "../chatBot.h"

#include <stdlib.h>

int random_custom(int l_bound, h_bound) {

    return l_bound <= h_bound ? (rand()%(h_bound - l_bound)) + l_bound : random_custom(h_bound, l_bound);

}