# Computer-Architecture-and-Operating-Systems-2year-MIPT-course

## Problem inf01-0: c/generic/sum-numbers
На стандартном потоке ввода подается последовательно вещественное число x и целое число в 16-ричной записи y.
Единственным аргументов программы является целое число z в 27-ричной системе исчисления.
Необходимо вывести вычислить значение x+y+z и вывести его на стандартный поток вывода с точностью до 3-го знака после точки.

## Problem inf01-1: generic/ieee754/classify
Реализуйте функцию с прототипом:

typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01,
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31
} float_class_t;

extern float_class_t
classify(double *value_ptr);
   
которая классифицирует специальные значения вещественного числа, на которое указывает value_ptr, в соответствии со стандартом IEEE 754.
При решении допускается использовать только побитовые операции, включая сдвиги.
