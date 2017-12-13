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

#include "CrossMode.h"

// Constructor
CrossMode::CrossMode(Serial* ser,Devices* devices,int yourmode)
{
	mymode = yourmode;
	currDevices = devices;
}


int CrossMode::runMode(void)
{
#ifdef DEBUG_CROSS_MODE
	printf("Cross Mode: It works!\r\n");
#endif

	currentmode = mymode;
	currDevices->tof->display(currentmode);

	while(currentmode == mymode){
		currDevices->currMotors.run(0, 30, MOTOR_LEFT , MOTOR_RIGHT);
		wait(2);
		currDevices->currMotors.stop();
		currentmode = NULL_MODE;
	}
	return currentmode;
}
