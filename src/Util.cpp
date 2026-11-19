#include "Util.h"

uint32_t Util::duration(float dist, float speed) {
    if (dist <= 0.0f || speed <= 0.1f) return 0;
    return (uint32_t)((dist * 30.48f / speed) * 1000.0f);
}
