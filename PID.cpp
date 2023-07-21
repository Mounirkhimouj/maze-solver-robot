#pragma once
#include "PID.h"

// Constructor for the PID class.
// Initializes the PID controller with the given parameters.
// KP: Proportional gain.
// KI: Integral gain.
// KD: Derivative gain.
// TAU: Time constant used in the differentiator computation.
// TIME: Sampling time for the PID controller.
// min: Minimum output limit for the controller.
// max: Maximum output limit for the controller.
PID::PID(float KP, float KI, float KD, float TAU, float TIME, int min, int max) {
    kp = KP;
    ki = KI;
    kd = KD;
    tau = TAU;
    T = TIME;
    integrator = 0;
    prevError = 0;
    differentiator = 0;
    prevMeasurement = 0;
    out = 0;
    limMin = min;
    limMax = max;
}

// Update the PID controller with the new setpoint and measurement.
// setpoint: The desired value to achieve.
// measurement: The current measured value from the system.
// returns: The PID controller output.
float PID::Up_date(float setpoint, float measurement) {

    /* Error signal */
    float error = setpoint - measurement;

    /* Proportional */
    float proportional = kp * error;

    /* Integral */
    integrator = integrator + 0.5f * ki * T * (error + prevError);

    /* Anti-wind-up via dynamic integrator clamping */
    float limMinInt, limMaxInt;

    /* Compute integrator limits */
    if (limMax > proportional) {
        limMaxInt = limMax - proportional;
    } else {
        limMaxInt = 0.0f;
    }

    if (limMin < proportional) {
        limMinInt = limMin - proportional;
    } else {
        limMinInt = 0.0f;
    }

    /* Clamp integrator */
    if (integrator > limMaxInt) {
        integrator = limMaxInt;
    } else if (integrator < limMinInt) {
        integrator = limMinInt;
    }

    /* Derivative (band-limited differentiator) */
    differentiator = (2.0f * kd * (measurement - prevMeasurement) + (2.0f * tau - T) * differentiator) / (2.0f * tau + T); 
    /* Note: derivative on measurement! */

    /* Compute output and apply limits */
    out = proportional + integrator + differentiator;

    if (out > limMax) {
        out = limMax;
    } else if (out < limMin) {
        out = limMin;
    }

    /* Store error and measurement for later use */
    prevError = error;
    prevMeasurement = measurement;

    /* Return controller output */
    return out;
}
