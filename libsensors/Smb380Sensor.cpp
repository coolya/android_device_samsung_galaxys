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
#include <cutils/log.h>


#include "Smb380Sensor.h"


/*****************************************************************************/
Smb380Sensor::Smb380Sensor()
    : SensorBase(NULL, "SMB380-Sensor"),
      mEnabled(0),

      mInputReader(4),
      mHasPendingEvent(false)
{
    LOGD("Smb380Sensor::Smb380Sensor()");
    mPendingEvent.version = sizeof(sensors_event_t);
    mPendingEvent.sensor = ID_A;
    mPendingEvent.type = SENSOR_TYPE_ACCELEROMETER;
    memset(mPendingEvent.data, 0, sizeof(mPendingEvent.data));
    
    LOGD("Smb380Sensor::Smb380Sensor() open data_fd");
	
    if (data_fd) {
        strcpy(input_sysfs_path, "/sys/class/input/");
        strcat(input_sysfs_path, input_name);
        strcat(input_sysfs_path, "/device/");
        input_sysfs_path_len = strlen(input_sysfs_path);

        enable(0, 1);
    }
}

Smb380Sensor::~Smb380Sensor() {

    LOGD("Smb380Sensor::~Smb380Sensor()");
    if (mEnabled) {
        enable(0, 0);
    }
}


int Smb380Sensor::setInitialState() {
    
    LOGD("Smb380Sensor::~setInitialState()");
    struct input_absinfo absinfo_x;
    struct input_absinfo absinfo_y;
    struct input_absinfo absinfo_z;
    float value;
    if (!ioctl(data_fd, EVIOCGABS(EVENT_TYPE_ACCEL_X), &absinfo_x) &&
        !ioctl(data_fd, EVIOCGABS(EVENT_TYPE_ACCEL_Y), &absinfo_y) &&
        !ioctl(data_fd, EVIOCGABS(EVENT_TYPE_ACCEL_Z), &absinfo_z)) {
        value = absinfo_x.value;
        mPendingEvent.acceleration.x = value * CONVERT_A_X;
        value = absinfo_y.value;
        mPendingEvent.acceleration.y = value * CONVERT_A_Y;
        value = absinfo_z.value;
        mPendingEvent.acceleration.z = value * CONVERT_A_Z;
        mHasPendingEvent = true;
    }
    else
    {
        LOGD("Smb380Sensor::~setInitialState() ioctl failed");
    }
    return 0;
}


int Smb380Sensor::enable(int32_t, int en) {

	   
    LOGD("Smb380Sensor::~enable(0, %d)", en);
    int flags = en ? 1 : 0;
    if (flags != mEnabled) {
        int fd;
        strcpy(&input_sysfs_path[input_sysfs_path_len], "enable");
        LOGD("Smb380Sensor::~enable(0, %d) open %s",en,  input_sysfs_path);
        fd = open(input_sysfs_path, O_RDWR);
        if (fd >= 0) {
             LOGD("Smb380Sensor::~enable(0, %d) opened %s",en,  input_sysfs_path);
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
            mEnabled = flags;
            setInitialState();
            return 0;
        }
        return -1;        
    }
    return 0;
}


bool Smb380Sensor::hasPendingEvents() const {
    /* FIXME probably here should be returning mEnabled but instead
	mHasPendingEvents. It does not work, so we cheat.*/
    //LOGD("Smb380Sensor::~hasPendingEvents %d", mHasPendingEvent ? 1 : 0 );
    return mHasPendingEvent;
}


int Smb380Sensor::setDelay(int32_t handle, int64_t ns)
{
    LOGD("Smb380Sensor::~setDelay(%d, %d)", handle, ns);
    /* FIXME needs changes to the kernel driver.
       We need to add a IOCTL that can set the samplingrate
       the driver in ther kernel supports this allready only need
       to add a IOCTL on both sides for that*/
    return 0;
}


int Smb380Sensor::readEvents(sensors_event_t* data, int count)
{
    //LOGD("Smb380Sensor::~readEvents() %d", count);
    if (count < 1)
        return -EINVAL;
        
    if (mHasPendingEvent) {
        mHasPendingEvent = false;
        mPendingEvent.timestamp = getTimestamp();
        *data = mPendingEvent;
        return mEnabled ? 1 : 0;
    }
        
    ssize_t n = mInputReader.fill(data_fd);
    if (n < 0)
        return n;

    int numEventReceived = 0;
    input_event const* event;
	
    while (count && mInputReader.readEvent(&event)) {
        int type = event->type;
        if (type == EV_ABS) {
            float value = event->value;
            if (event->code == EVENT_TYPE_ACCEL_X) {
                mPendingEvent.acceleration.x = value * CONVERT_A_X;
            } else if (event->code == EVENT_TYPE_ACCEL_Y) {
                mPendingEvent.acceleration.y = value * CONVERT_A_Y;
            } else if (event->code == EVENT_TYPE_ACCEL_Z) {
                mPendingEvent.acceleration.z = value * CONVERT_A_Z;
            }
        } else if (type == EV_SYN) {
            mPendingEvent.timestamp = timevalToNano(event->time);
            if (mEnabled) {
                *data++ = mPendingEvent;
                count--;
                numEventReceived++;
            }
        } else {
            LOGE("Smb380Sensor: unknown event (type=%d, code=%d)",
                    type, event->code);
        }
        mInputReader.next();
    }
 
	//LOGD("Smb380Sensor::~readEvents() numEventReceived = %d", numEventReceived);
	return numEventReceived++;
		
}
