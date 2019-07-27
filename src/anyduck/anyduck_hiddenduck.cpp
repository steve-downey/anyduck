#include <anyduck/anyduck_hiddenduck.h>

using namespace anyduck;

HiddenMallard::HiddenMallard() {}
HiddenMallard::~HiddenMallard() {}

int HiddenMallard::quack(int length) const {
    return 3*length;
}
