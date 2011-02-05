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

#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/select.h>
#include <dlfcn.h>

#include <cutils/log.h>

#include "BoschYamaha.h"

/*****************************************************************************/

int stub_is_sensor_enabled(uint32_t sensor_type) {
    return 0;
}

int stub_enable_disable_sensor(uint32_t sensor_type) {
    return -ENODEV;
}

int stub_set_delay(uint64_t delay) {
    return -ENODEV;
}

BoschYamaha::BoschYamaha()
: SensorBase(NULL, NULL),
      //mEnabled(0),
      mPendingMask(0),
      mInputReaderMagnetic(4),
      mInputReaderAccel(4)
{

    /* FIXME set input device name for magnetic sensor */
    data_name = "input0";
    data_compass_fd = openInput("geomagnetic");
	
	//Open Compass
	if (data_compass_fd) {
        strcpy(input_sysfs_path, "/sys/class/input/");
        strcat(input_sysfs_path, input_name);
        strcat(input_sysfs_path, "/device/");
        input_sysfs_path_len = strlen(input_sysfs_path);
        //enable(MagneticField, 1);

    }
    
    /* FIXME set input device name for accelereometer sensor */
    data_accel_name = "event6";
    data_fd = openInput("SMB380-Sensor");
    
		//Open Compass
	if (data_fd) {
        strcpy(input_accel_sysfs_path, "/sys/class/input/");
        strcat(input_accel_sysfs_path, data_accel_name);
        strcat(input_accel_sysfs_path, "/device/");
        input_accel_sysfs_path_len = strlen(input_accel_sysfs_path);

        enable(Accelerometer, 1);

    }

	
    memset(mPendingEvents, 0, sizeof(mPendingEvents));

    mPendingEvents[Accelerometer].version = sizeof(sensors_event_t);
    mPendingEvents[Accelerometer].sensor = ID_A;
    mPendingEvents[Accelerometer].type = SENSOR_TYPE_ACCELEROMETER;
    mPendingEvents[Accelerometer].acceleration.status = SENSOR_STATUS_ACCURACY_HIGH;

    mPendingEvents[MagneticField].version = sizeof(sensors_event_t);
    mPendingEvents[MagneticField].sensor = ID_M;
    mPendingEvents[MagneticField].type = SENSOR_TYPE_MAGNETIC_FIELD;
    mPendingEvents[MagneticField].magnetic.status = SENSOR_STATUS_ACCURACY_HIGH;

    mPendingEvents[Orientation].version = sizeof(sensors_event_t);
    mPendingEvents[Orientation].sensor = ID_O;
    mPendingEvents[Orientation].type = SENSOR_TYPE_ORIENTATION;
    mPendingEvents[Orientation].orientation.status = SENSOR_STATUS_ACCURACY_HIGH;


	
	
    for (int i=0 ; i<numSensors ; i++)
        mDelays[i] = 200000000; // 200 ms by default

}

BoschYamaha::~BoschYamaha()
{
	if(compassEnabled){
		enable(MagneticField, 0);
	}
	if(accelEnabled){
		enable(Accelerometer, 0);
	}
	
}

int BoschYamaha::enable(int32_t handle, int en)
{
    int what = -1;

    switch (handle) {
        case ID_A: what = Accelerometer; break;
        case ID_M: what = MagneticField; break;
        case ID_O: what = Orientation;   break;
    }

    if (uint32_t(what) >= numSensors)
        return -EINVAL;

    int newState  = en ? 1 : 0;
    int err = 0;

	//FIXME enabling the right sensor over sysfs interface
	if(what == MagneticField){
		what = Accelerometer; //Enable also Accel
		//Compass
		 LOGD("BoschYamaha::~enable Compass(0, %d)", en);
		int flags = en ? 1 : 0;
		if (flags != compassEnabled) {
			int fd;
			strcpy(&input_sysfs_path[input_sysfs_path_len], "enable");
			LOGD("BoschYamaha::~enable Compass(0, %d) open %s",en,  input_sysfs_path);
			fd = open(input_sysfs_path, O_RDWR);
			if (fd >= 0) {
				 LOGD("CompassSensor::~enable(0, %d) opened %s",en,  input_sysfs_path);
				char buf[2];
				int err;
				buf[1] = 0;
				if (flags) {
					buf[0] = '1';
				} else {
					buf[0] = '0';
				}
				err = write(fd, buf, sizeof(buf));
				close(fd);
				//mEnabled = flags;
				compassEnabled = flags;
				return 0;
			}
		}
	}
	
	if(what == Accelerometer){
		//Accelerometer
		 LOGD("BoschYamaha::~enable Accel(0, %d)", en);
		int flags = en ? 1 : 0;
		if (flags != accelEnabled) {
			int fd;
			strcpy(&input_accel_sysfs_path[input_accel_sysfs_path_len], "enable");
			LOGD("BoschYamaha::~enable Accel(0, %d) open %s",en,  input_accel_sysfs_path);
			fd = open(input_accel_sysfs_path, O_RDWR);
			if (fd >= 0) {
				 LOGD("CompassSensor::~enable(0, %d) opened %s",en,  input_accel_sysfs_path);
				char buf[2];
				int err;
				buf[1] = 0;
				if (flags) {
					buf[0] = '1';
				} else {
					buf[0] = '0';
				}
				err = write(fd, buf, sizeof(buf));
				close(fd);
				//mEnabled = flags;
				accelEnabled = flags;
				return 0;
			}
		}
	}
	

    return err;
}

int BoschYamaha::setDelay(int32_t handle, int64_t ns)
{
    int what = -1;
    switch (handle) {
        case ID_A: what = Accelerometer; break;
        case ID_M: what = MagneticField; break;
        case ID_O: what = Orientation;   break;
    }

    if (uint32_t(what) >= numSensors)
        return -EINVAL;

    if (ns < 0)
        return -EINVAL;

    mDelays[what] = ns;
    return update_delay();
}

int BoschYamaha::update_delay()
{
    return 0;
}


bool BoschYamaha::hasPendingEvents() {

    //LOGD("hasPendingEvents was called");
	if(accelEnabled || compassEnabled){
	    //LOGD("hasPendingEvents will return true");
		return true;
	}
	else {
		//LOGD("hasPendingEvents will return false");
		return false;
	}
}



int BoschYamaha::readEvents(sensors_event_t* data, int count)
{
    if (count < 1)
        return -EINVAL;
		

	int numEventReceived = 0;
	
	//LOGD("Sensor: Read events was called with count: %d", count);
	
	if(compassEnabled)
	{
		//LOGD("Sensor: Compass is enabled, going to take care of it, count: %d", count);
		ssize_t n = mInputReaderMagnetic.fill(data_compass_fd);
		if (n < 0)
			return n;

		input_event const* event;

		while ( count  && mInputReaderMagnetic.readEvent(&event)) {
			int type = event->type;       
			//Everything is ABS!
			if (type == EV_ABS) {
				float value = event->value;
					if (event->code == EVENT_TYPE_MAGV_X) {
						mPendingEvents[MagneticField].magnetic.x = (value * CONVERT_M_X);
					} else if (event->code == EVENT_TYPE_MAGV_Y) {
						mPendingEvents[MagneticField].magnetic.y = (value * CONVERT_M_Y);
					} else if (event->code == EVENT_TYPE_MAGV_Z) {
						mPendingEvents[MagneticField].magnetic.z = (value * CONVERT_M_Z);
					}
			}
			else if (type == EV_SYN) {
				mPendingEvents[MagneticField].timestamp = timevalToNano(event->time);
				if (compassEnabled) {
					//LOGD("Sensor: Compass was enabled, made a read and received a Sync");
					compassDataReady = 1;
					compassLastRead[0] = mPendingEvents[MagneticField].magnetic.x;
					compassLastRead[1] = mPendingEvents[MagneticField].magnetic.y;
					compassLastRead[2] = mPendingEvents[MagneticField].magnetic.z;	
					
					*data++ = mPendingEvents[MagneticField];
					count--;
					numEventReceived++;
				}
			} else {
				LOGE("BoschYamaha: unknown event (type=%d, code=%d)", type, event->code);
				
			}
			mInputReaderMagnetic.next();
		}
	}
	
	//LOGD("Sensor: Compass read quited, count: %d", count);
    
	
	if(accelEnabled)
	{
		//LOGD("Sensor: Accel is enabled, going to take care of it, count: %d", count);
		
		ssize_t n = mInputReaderAccel.fill(data_fd);
		//LOGD("Sensor: Accel Input Reader was filled up: %d", count);
		if (n < 0)
			return n;
			
		input_event const* event;		
		
		while (count && mInputReaderAccel.readEvent(&event)) {
			int type = event->type;
			if (type == EV_ABS) {
				//LOGD("Sensor: Received one EV_ABS Event");
				float value = event->value;
				if (event->code == EVENT_TYPE_ACCEL_X) {
					mPendingEvents[Accelerometer].acceleration.x = value * CONVERT_A_X;
				} else if (event->code == EVENT_TYPE_ACCEL_Y) {
					mPendingEvents[Accelerometer].acceleration.y = value * CONVERT_A_Y;
				} else if (event->code == EVENT_TYPE_ACCEL_Z) {
					mPendingEvents[Accelerometer].acceleration.z = value * CONVERT_A_Z;
				}
			} else if (type == EV_SYN) {
				mPendingEvents[Accelerometer].timestamp = timevalToNano(event->time);
				if (accelEnabled) {
					//LOGD("Sensor: Accel was enabled, made a read and received a Sync");
					accelDataReady = 1;
					accelLastRead[0] = mPendingEvents[Accelerometer].acceleration.x;
					accelLastRead[1] = mPendingEvents[Accelerometer].acceleration.y;
					accelLastRead[2] = mPendingEvents[Accelerometer].acceleration.z;
					*data++ = mPendingEvents[Accelerometer];
					count--;
					numEventReceived++;
				}
			}
			 else {
				LOGE("BoschYamaha: unknown event (type=%d, code=%d)", type, event->code);
				
			}
			mInputReaderAccel.next();
		}
	}
	
	//LOGD("Sensor: Accel read quited, count: %d, acceldata Ready: %d, compassData Ready = %d", count, accelDataReady, compassDataReady);
		
	if( (accelDataReady == 1) && (compassDataReady == 1)){
		//LOGD("BoschYamaha: Going to Process Orientation Data");
		accelDataReady = 0;
		compassDataReady = 0;
		processOrientation();
		*data++ = mPendingEvents[Orientation];
		numEventReceived++;
	}

	
    return numEventReceived;
}


int BoschYamaha::processOrientation(){
	
	float matrix[9], euler[3];
	int rt, i;

	
	rt = get_rotation_matrix(accelLastRead, compassLastRead, matrix);


	if (rt < 0) {
	   for (i = 0; i < 3; i++) {
	       euler[i] = 0;
	   }
	}
	else {
	    get_euler(matrix, euler);
	}
	
	//LOGD("BoschYamaha: azimuth is %d", (int)(euler[0]));
	//LOGD("BoschYamaha: pitch is %d", (int)(euler[1]));
	//LOGD("BoschYamaha: roll is %d", (int)(euler[2]));

	//Use CONVERT_O_A
    mPendingEvents[Orientation].orientation.azimuth = (int)(euler[0]);
    mPendingEvents[Orientation].orientation.pitch = (int)(euler[1]);
    mPendingEvents[Orientation].orientation.roll = (int)(euler[2]);
    //mPendingEvents[Orientation].orientation.status = uint8_t(value & SENSOR_STATE_MASK);

	return 1;

}


float BoschYamaha::calc_intensity(float x, float y, float z)
{
    return sqrt(x*x + y*y + z*z);
}


int BoschYamaha::get_rotation_matrix(const float *gsdata, const float *msdata, float *matrix)
{
    float m_intensity, g_intensity, a_intensity, b_intensity;
    float gdata[3], mdata[3], adata[3], bdata[3];
    int i;

    if (gsdata == NULL || msdata == NULL || matrix == NULL) {
        return -1;
    }
    g_intensity = calc_intensity(gsdata[0], gsdata[1], gsdata[2]);
    m_intensity = calc_intensity(msdata[0], msdata[1], msdata[2]);
    if (g_intensity == 0 || m_intensity == 0) {
        return -1;
    }
    for (i = 0; i < 3; i++) {
        gdata[i] = -gsdata[i] / g_intensity;
        mdata[i] = msdata[i] / m_intensity;
    }

    adata[0] = (gdata[1] * mdata[2] - gdata[2] * mdata[1]);
    adata[1] = (gdata[2] * mdata[0] - gdata[0] * mdata[2]);
    adata[2] = (gdata[0] * mdata[1] - gdata[1] * mdata[0]);
    a_intensity = calc_intensity(adata[0], adata[1], adata[2]);
    if (a_intensity == 0) {
        return -1;
    }
    for (i = 0; i < 3; i++) {
        adata[i] /= a_intensity;
    }

    bdata[0] = (adata[1] * gdata[2] - adata[2] * gdata[1]);
    bdata[1] = (adata[2] * gdata[0] - adata[0] * gdata[2]);
    bdata[2] = (adata[0] * gdata[1] - adata[1] * gdata[0]);
    b_intensity = calc_intensity(bdata[0], bdata[1], bdata[2]);
    if (b_intensity == 0) {
        return -1;
    }
    for (i = 0; i < 3; i++) {
        bdata[i] /= b_intensity;
    }

    matrix[0] = adata[0];
    matrix[1] = adata[1];
    matrix[2] = adata[2];
    matrix[3] = bdata[0];
    matrix[4] = bdata[1];
    matrix[5] = bdata[2];
    matrix[6] = -gdata[0];
    matrix[7] = -gdata[1];
    matrix[8] = -gdata[2];

    return 0;
}

int BoschYamaha::get_euler(const float *matrix, float *euler)
{
    float m11, m12;
    float m21, m22;
    float m31, m32, m33;
    float yaw = 0, roll = 0, pitch = 0;

    if (matrix == NULL || euler == NULL) {
        return -1;
    }

    m11 = matrix[0];
    m12 = matrix[1];
    m21 = matrix[3];
    m22 = matrix[4];
    m31 = matrix[6];
    m32 = matrix[7];
    m33 = matrix[8];

    yaw     = atan2(m12-m21, m11+m22);
    pitch   = -asin(m32);
    roll    = asin(m31);

    yaw     *= 180.0 / M_PI;
    pitch   *= 180.0 / M_PI;
    roll    *= 180.0 / M_PI;

    if (m33 < 0) {
        pitch = -180 - pitch;
        if (pitch < -180) {
            pitch += 360;
        }
    }
    if (yaw < 0) {
        yaw += 360.0f;
    }

    euler[0] = (float)(int)yaw;    /* yaw */
	
    euler[1] = (float)(int)pitch;  /* pitch */
    euler[2] = (float)(int)roll;   /* roll */

    return 0;
}



