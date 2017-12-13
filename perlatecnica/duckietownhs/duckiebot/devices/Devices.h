/* Copyright (c) 2016-2017 perlatecnica.it, MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef DEVICES_H
#define DEVICES_H

#include "TCS3200.h"
#include "STSpin240_250.h"
#include "HTS221Sensor.h"
#include "LPS22HBSensor.h"
#include "LSM6DSLSensor.h"
#include "MotorShieldIHM12A1.h"
#include "ToF53L0A1.h"
#include "duckiebot_def.h"


#define ROADSIGN_DETECTION_THRESHOLD_DEFAULT 0.8

class Devices {

public:
    Devices(Serial* ser);
    MotorShieldIHM12A1 currMotors;

    //Create a TCS3200 object S0    S1    S2     S3     OUT
    TCS3200 *color;

    ToF53L0A1 *tof;

    AnalogIn *rfrontIR;
    AnalogIn *lfrontIR;
    AnalogIn *cfrontIR;

    float roadsign_detect_threshold; // Roadsign detection threshold

    bool roadsignDetected(float cfrontIRvalue);
private:

};

#endif

