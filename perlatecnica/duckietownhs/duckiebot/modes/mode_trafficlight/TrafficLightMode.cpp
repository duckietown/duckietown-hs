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

#include "TrafficLightMode.h"


// Constructor
TrafficLightMode::TrafficLightMode(Serial* ser,Devices* devices,int yourmode)
{
	mymode = yourmode;
	currDevices = devices;
}


int TrafficLightMode::runMode(void)
{
#ifdef DEBUG_TRAFFICLIGHT_MODE
	printf("TrafficLight Mode: It works!\r\n");
#endif

	int red = 0;
	int green = 0;

	currentmode = mymode;
	currDevices->tof->display(currentmode);

	while(currentmode == mymode){
		cfrontIR = currDevices->cfrontIR->read();
		red = currDevices->color->ReadRed();
		green = currDevices->color->ReadGreen();

		printf("RED %d\r\n", red);
		printf("GREEN %d\r\n", green);

		if(currDevices->roadsignDetected(cfrontIR)){
			currDevices->currMotors.run(0, 25, MOTOR_LEFT , MOTOR_RIGHT);
		}
		else
		{
			//RDD Mauro:400 Francesco:200
			if(red < 200){
				currDevices->currMotors.run(0, -10, MOTOR_LEFT , MOTOR_RIGHT);
				//currDevices->currMotors.stop();
			} else if(green < 400){
				//currentmode = NAV_MODE;//CROSS_MANAGEMENT_MODE;

				//only for demo
				currentmode = NAV_MODE_STOP;//CROSS_MANAGEMENT_MODE;
				currDevices->color->SetMode(TCS3200::POWERDOWN);
				break;

			} else {
				currDevices->currMotors.run(0, 25, MOTOR_LEFT , MOTOR_RIGHT);
			}
		}

	}
	return currentmode;
}
