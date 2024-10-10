#ifndef _STATISTICS_H
    #define _STATISTICS_H

#include <Arduino.h>

float mean(uint16_t* x, int n);
float variance(uint16_t* x, int n, float mean);
float stddev(float variance);
int compare(const void* a, const void* b);
float median(uint16_t* x, int n);
float mode(uint16_t *x, int n);

#endif