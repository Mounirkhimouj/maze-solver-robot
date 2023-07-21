#pragma once

class PID {
public:
    /* Controller gains */
    float kp;  // Proportional gain
    float ki;  // Integral gain
    float kd;  // Derivative gain

    /* Derivative low-pass filter time constant */
    float tau; // Time constant used in the differentiator computation

    /* Output limits */
    float limMin; // Minimum output limit for the controller
    float limMax; // Maximum output limit for the controller

    /* Sample time (in seconds) */
    float T; // Sampling time for the PID controller

    /* Controller "memory" */
    float integrator;      // Accumulated integral term
    float prevError;       // Previous error for integral calculation
    float differentiator;  // Filtered derivative term
    float prevMeasurement; // Previous measurement for derivative calculation

    float out; // PID controller output

    /* Constructor for the PID class.
       Initializes the PID controller with the given parameters.
       kp: Proportional gain.
       ki: Integral gain.
       kd: Derivative gain.
       tau: Time constant used in the differentiator computation.
       T: Sampling time for the PID controller.
       limMin: Minimum output limit for the controller.
       limMax: Maximum output limit for the controller. */
    PID(float kp, float ki, float kd, float tau, float T, int limMin, int limMax);

    /* Update the PID controller with the new setpoint and measurement.
       setpoint: The desired value to achieve.
       measurement: The current measured value from the system.
       returns: The PID controller output. */
    float Up_date(float setpoint, float measurement);
};
