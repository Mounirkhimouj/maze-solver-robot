/////////////////////////////////////////////////////////////////////////////////
//
//  Digital filter : Moving Average 
//  The filter is a combinaison of 2 buffers 
//  The data structure of the buffer is a queue
//
/////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "QList.h"

class filter {
public:
    // Initialize the size of the two buffers: one for calculating the median and one for calculating the average.
    // median_num: size of the buffer for calculating the median.
    // average_num: size of the buffer for calculating the average.
    int median_num, average_num;

    // The total variable is used to keep track of the sum of elements in the average buffer.
    // The bias variable is used to initialize the values of the buffers (optional, default is 0).
    float total, bias;

    // Two queues (lists) to store data: read buffer and average buffer.
    QList<float> read;
    QList<float> average_buffer;

    // Constructor for the filter class.
    filter(int median_num, int average_num, int bias = 0);

    // Method to perform filtering on the input data using the moving average digital filter.
    // input: the new data point to be filtered.
    // returns: the filtered result.
    float filtering(float input);

    // Method to initialize the filter buffers with a bias term
    void initialize(int bias);
};
