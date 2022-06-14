#include "baseoutputinterface.h"

void BaseOutputInterface::activate() {
    printf("Base class of an output interface received an activation signal. This should not happen.\n");
}

void BaseOutputInterface::deactivate(int reason) {
    printf("Base class of an output interface received a deactivation signal for reason id %i. This should not happen.\n", reason);
}

void BaseOutputInterface::setMode(char m) {
    printf("Base class of an output interface received a mode change signal to mode '%c'. This should not happen.\n", m);
}

void BaseOutputInterface::setColor(color_t c) {
    printf("Base class of an output interface received a color change signal to color_t(%i,%i,%i,%i). This should not happen.\n", c.r, c.g, c.b, c.v);
}

BaseOutputInterface::~BaseOutputInterface() {
    printf("Base class of an output interface received a destruction signal. This should not happen, and will cause memory leaks.\n");
}
