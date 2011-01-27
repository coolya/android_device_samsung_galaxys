/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_BOSCHYAMAHA_SENSOR_H
#define ANDROID_BOSCHYAMAHA_SENSOR_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>


#include "sensors.h"
#include "SensorBase.h"
#include "InputEventReader.h"

/*****************************************************************************/

struct input_event;

class BoschYamaha : public SensorBase {
public:
            BoschYamaha();
    virtual ~BoschYamaha();
	

		
    enum {
        Accelerometer   = 0,
        MagneticField   = 1,
        Orientation     = 2,
        numSensors
    };

    virtual int setDelay(int32_t handle, int64_t ns);
    virtual int enable(int32_t handle, int enabled);
    virtual int readEvents(sensors_event_t* data, int count);
	virtual bool hasPendingEvents();
	int processOrientation();
	float calc_intensity(float x, float y, float z);
	int get_rotation_matrix(const float *gsdata, const float *msdata, float *matrix);
	int get_euler(const float *matrix, float *euler);

private:
    const char* data_accel_name;
    int         data_compass_fd;
    int update_delay();
    //uint32_t mEnabled;
	int compassEnabled;
	int accelEnabled;
	float accelLastRead[3];
	float compassLastRead[3];
	int compassDataReady;
	int accelDataReady;	
    uint32_t mPendingMask;
    InputEventCircularReader mInputReaderMagnetic;
    InputEventCircularReader mInputReaderAccel;
    sensors_event_t mPendingEvents[numSensors];
    uint64_t mDelays[numSensors];
	char input_sysfs_path[PATH_MAX];
    int input_sysfs_path_len;
	char input_accel_sysfs_path[PATH_MAX];
    int input_accel_sysfs_path_len;
	
};

/*****************************************************************************/

#endif  // ANDROID_BOSCHYAMAHA_SENSOR_H
