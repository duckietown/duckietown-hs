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

#include "RoadSignAlignMode.h"

// Constructor
RoadSignAlignMode::RoadSignAlignMode(Serial* ser,Devices* devices,int yourmode)
{
	mymode = yourmode;
	currDevices = devices;
}


int RoadSignAlignMode::runMode(void)
{
#ifdef DEBUG_ROADSIGNALIGN_MODE
	printf("Roadsign aligning Mode: It works!\r\n");
#endif

	int status = 0;
	int bitcount = 0;
	bool righold = false;

	currentmode = mymode;
	currDevices->tof->display(currentmode);

	while(currentmode == mymode){
		rfrontIR = 0;
		lfrontIR = 0;
		cfrontIR = 0;

		for(int k=0;k<5;k++){
			rfrontIR += currDevices->rfrontIR->read();
			lfrontIR += currDevices->lfrontIR->read();
			cfrontIR += currDevices->cfrontIR->read();
			wait_ms(10);
		}

		rfrontIR = rfrontIR/5;
		lfrontIR = lfrontIR/5;
		cfrontIR = cfrontIR/5;

#ifdef DEBUG_ROADSIGNALIGN_MODE
		printf("rfrontIR: %f\r\n",rfrontIR);
		printf("lfrontIR: %f\r\n",lfrontIR);
		printf("cfrontIR: %f\r\n",cfrontIR);
		printf("direction: %3d\r\n",direction);
		printf("\033[4A");
#endif
		printf("status %d\r\n", status);
		if(status==0){

			if(LEFT_IR_WHITE){
				currDevices->currMotors.speed(MOTOR_LEFT,25);
			} else {
				currDevices->currMotors.stop(MOTOR_LEFT);
			}

			if(RIGHT_IR_WHITE){
				currDevices->currMotors.speed(MOTOR_RIGHT,25);
			} else {
				currDevices->currMotors.stop(MOTOR_RIGHT);
			}
			if((RIGHT_IR_BLACK) & (LEFT_IR_BLACK) ){
				wait_ms(500);
				currDevices->currMotors.run(0, 30, MOTOR_LEFT , MOTOR_RIGHT);
				//wait_ms(500);
				status=1;
			}
		}

		if(status>0){
			printf("status > 0\r\n");
			if (righold && RIGHT_IR_BLACK){
				status++;
			}

			righold = RIGHT_IR_WHITE;

			if (status>2){
				// Switch ON the sensor of color
				currDevices->color->SetMode(TCS3200::SCALE_20);
				currentmode = TRAFFICLIGHT_MANAGEMENT_MODE;
				currDevices->currMotors.stop();
				currDevices->tof->display("ECCE");
				//while(true);
				break;
			}
		}


	} // end while
	return currentmode;
}
