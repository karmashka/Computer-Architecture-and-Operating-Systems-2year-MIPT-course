#include <stdint.h>

typedef enum {
    Zero = 1,
    Inf = 2,
    Regular = 3,
    Denormal = 4,
    NaN = 5
} unsigned_classes;

typedef enum {
    PlusZero = 0x00,
    MinusZero = 0x01,
    PlusInf = 0xF0,
    MinusInf = 0xF1,
    PlusRegular = 0x10,
    MinusRegular = 0x11,
    PlusDenormal = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN = 0x30,
    QuietNaN = 0x31
} float_class_t;

unsigned_classes pre_classify (uint64_t value) {
    uint64_t exponent_mask = ~(~0ull << 63) & (~0ull << 52);
    uint64_t fraction_mask = ~(~0ull << 63) & ~(~0ull << 52);
    uint64_t exponent = value & exponent_mask;
    uint64_t fraction = value & fraction_mask;
    if (exponent == 0) {
        if (fraction == 0) {
            return Zero;
        } else {
            return Denormal;
        }
    } else if (exponent == exponent_mask) {
        if (fraction == 0) {
            return Inf;
        }
        return NaN;
    }
    return Regular;
}

extern float_class_t classify (double *value_ptr) {
    void *value_ptr_void = value_ptr;
    uint64_t *value_ptr_int = value_ptr_void;
    uint64_t value = *value_ptr_int;
    unsigned_classes current_class = pre_classify (value);
    if (current_class == NaN) {
        if ((value & (1ull << 51))) {
            return QuietNaN;
        }
        return SignalingNaN;
    }
    if ((value & (1ull << 63))) {
        if (current_class == Zero) {
            return MinusZero;
        } else if (current_class == Denormal) {
            return MinusDenormal;
        } else if (current_class == Inf) {
            return MinusInf;
        }
        return MinusRegular;
    } else {
        if (current_class == Zero) {
            return PlusZero;
        } else if (current_class == Denormal) {
            return PlusDenormal;
        } else if (current_class == Inf) {
            return PlusInf;
        }
    }
    return PlusRegular;
}