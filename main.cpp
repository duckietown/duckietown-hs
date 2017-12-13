/* Copyright (c) 2017 Perlatecnica no-profit organization
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "duckiebot_def.h"
#include "PostMode.h"
#include "NavMode.h"
#include "NavModeStop.h"
#include "RoadSignAlignMode.h"
#include "TrafficLightMode.h"
#include "CrossMode.h"
#include "ObstaclesMode.h"
#include "Devices.h"

//Serial connection to PC
Serial pc(USBTX, USBRX);

int currentmode = POST_CAL_MODE;

Devices devices(&pc);
PostMode postmode(&pc,&devices, POST_CAL_MODE);
NavMode navmode(&pc,&devices, NAV_MODE);
RoadSignAlignMode rsamode(&pc,&devices, ROAD_SIGN_ALIGNING_MODE);
TrafficLightMode tlmode(&pc,&devices, TRAFFICLIGHT_MANAGEMENT_MODE);
CrossMode crossmode(&pc,&devices, CROSS_MANAGEMENT_MODE);
ObstaclesMode obstmode(&pc,&devices, OBSTACLES_MANAGEMENT_MODE);
NavModeStop navmodestop(&pc,&devices, NAV_MODE_STOP);


int main() {

	//It changes baudrate
	pc.baud(115200);


	while(true) {

#ifdef DEBUG_MAIN
		pc.printf("Main: It works!\r\n");
#endif

		switch(currentmode){

		case POST_CAL_MODE:
			currentmode = postmode.runMode();
			break;

		case NAV_MODE:
			currentmode = navmode.runMode();
			//break is removed. It takes less time switching to the next mode that is the following ROAD_SIGN_ALIGNING_MODE

		case ROAD_SIGN_ALIGNING_MODE:
			currentmode = rsamode.runMode();
			break;

		case TRAFFICLIGHT_MANAGEMENT_MODE:
			currentmode = tlmode.runMode();
			break;

		case CROSS_MANAGEMENT_MODE:
			currentmode = crossmode.runMode();
			break;

		case OBSTACLES_MANAGEMENT_MODE:
			currentmode = obstmode.runMode();
			break;
		case NAV_MODE_STOP:
			currentmode = navmodestop.runMode();
		default:
			break;
		}
		wait_ms(100);
	}

}
