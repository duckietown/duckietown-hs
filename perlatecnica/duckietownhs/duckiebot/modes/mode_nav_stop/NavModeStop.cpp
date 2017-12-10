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

#include "NavModeStop.h"

// Constructor
NavModeStop::NavModeStop(Serial* ser,Devices* devices,int yourmode)
{
	mymode = yourmode;
	currDevices = devices;
}


int NavModeStop::runMode(void)
{
#ifdef DEBUG_NAV_MODE_STOP
	printf("Nav Mode: It works!\r\n");
#endif

	currentmode = mymode;
	currDevices->tof->display(currentmode);

	while(currentmode == mymode){

		// Reading IRs value
		rfrontIR = currDevices->rfrontIR->read();
		lfrontIR = currDevices->lfrontIR->read();
		cfrontIR = currDevices->cfrontIR->read();

		targetdirection = lfrontIR - rfrontIR;

		if (targetdirection > 0)
		{
			direction = (int8_t) ((targetdirection - 0.3)*75);
		}
		else
		{
			direction = (int8_t) ((targetdirection - 0.5)*80);
		}


#ifdef DEBUG_NAV_MODE_STOP
		printf("rfrontIR: %f\r\n",rfrontIR);
		printf("lfrontIR: %f\r\n",lfrontIR);
		printf("cfrontIR: %f\r\n",cfrontIR);
		printf("direction: %3d\r\n",direction);
		printf("\033[4A");
#endif

		if(currDevices->roadsignDetected(cfrontIR)){
			currDevices->currMotors.run(0,-5, MOTOR_LEFT , MOTOR_RIGHT);
			// Stop Bot
			currentmode = NULL_MODE;
			break;
		}
		else
		{
			// The duckiebot navigates
			currDevices->currMotors.run(direction, 50, MOTOR_LEFT , MOTOR_RIGHT);
		}
	}
	return currentmode;
}
