#pragma once
#include "filter.h"
#include "Arduino.h"

// Constructor for the filter class.
// a: size of the buffer for calculating the median.
// b: size of the buffer for calculating the moving average.
// c: initial value to set all elements in the buffers (optional, default is 0).
filter::filter(int a, int b, int c) {
    total = 0;
    median_num = a;
    average_num = b;
    bias = c;

    // Initialize the read buffer with the initial bias value.
    for (int i = 0; i < median_num; i++) {
        read.push_front(bias);
    }

    // Initialize the average buffer with the initial bias value.
    for (int i = 0; i < average_num; i++) {
        average_buffer.push_front(bias);
    }
}

// Method to perform filtering on the input data using the moving average digital filter.
// y: the new (raw) data point to be filtered.
// returns: the filtered result.
float filter::filtering(float y) {
    // Add new reading to the front of the read buffer and remove the oldest reading.
    read.pop_front();
    read.push_back(y);

    int medianValue;
    if (median_num % 2 == 0) {
        // If the median buffer size is even, take the average of the two middle values.
        medianValue = (read[median_num / 2 - 1] + read[median_num / 2]) / 2;
    } else {
        // If the median buffer size is odd, take the middle value directly.
        medianValue = read[median_num / 2];
    }

    // Update the total sum in the average buffer.
    total = total - average_buffer.front();
    average_buffer.pop_front();
    average_buffer.push_back(medianValue);
    total = total + average_buffer.back();

    // Calculate the moving average based on the last 'average_num' median values.
    return bias + (total / average_num);
}

// Method to initialize the filter buffers with a bias term.
// j: initial value to set all elements in the buffers.
void filter::initialize(int j) {
    total = 0;
    bias = j;

    // Clear and re-initialize the read buffer with the new bias value.
    read.clear();
    for (int i = 0; i < median_num; i++) {
        read.push_front(bias);
    }

    // Clear and re-initialize the average buffer with the new bias value.
    average_buffer.clear();
    for (int i = 0; i < average_num; i++) {
        average_buffer.push_front(bias);
    }
}
