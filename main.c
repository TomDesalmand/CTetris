// Header files include //
#include "include/application/application.h"

// STD include //
#include <stdlib.h>
#include <stdbool.h>

// Return macros
#define SUCCESS 0
#define FAIL 1

int main() {
    struct Application* application = malloc(sizeof(struct Application));
    if (!application) {
        return FAIL;
    }
    if (!initApplicationStructures(&application)) {
        free(application);
        return FAIL;
    }
    initApplication();
    initColor();
    run(&application);
    endApplication();
    freeApplicationStructures(&application);
    return SUCCESS;
}