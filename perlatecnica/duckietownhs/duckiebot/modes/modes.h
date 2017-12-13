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

#ifndef MODES_H
#define MODES_H

// Power On Self Test & Calibration
#define POST_CAL_MODE 0

// Navigation mode: the bot navigates in the streets staying in the way
#define NAV_MODE 1

// Aligning mode: The bot has recognised a road sign
#define ROAD_SIGN_ALIGNING_MODE 2

// It manages the trafficlight
#define TRAFFICLIGHT_MANAGEMENT_MODE 3

// It manages the cross
#define CROSS_MANAGEMENT_MODE 4

// It manages the obstacles
#define OBSTACLES_MANAGEMENT_MODE 5

// NULL MODE
#define NULL_MODE 6

// Navigation mode & stop: the bot navigates in the streets staying in the way and stop on first white line
#define NAV_MODE_STOP 7



#endif
