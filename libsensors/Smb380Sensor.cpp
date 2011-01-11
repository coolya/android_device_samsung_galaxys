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

#define FETCH_FULL_EVENT_BEFORE_RETURN 1

/*****************************************************************************/

Smb380Sensor::Smb380Sensor()
    : SensorBase(NULL, NULL),
      mEnabled(0)
{
    LOGD("Smb380Sensor::Smb380Sensor()");
    mPendingEvent.version = sizeof(sensors_event_t);
    mPendingEvent.sensor = ID_GY;
    mPendingEvent.type = SENSOR_TYPE_ACCELEROMETER;
    memset(mPendingEvent.data, 0, sizeof(mPendingEvent.data));
    
    LOGD("Smb380Sensor::Smb380Sensor() open /dev/accelerometer");
    data_fd = open("/dev/accelerometer", O_RDONLY);

    if (data_fd) {
        LOGD("Smb380Sensor::Smb380Sensor() /dev/accelerometer is open");
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
    mHasPendingEvent = true;
    return 0;
}

int Smb380Sensor::enable(int32_t, int en) {
    LOGD("Smb380Sensor::~enable(0, %d)", en);
    int flags = en ? 1 : 0;
    if (flags != mEnabled) {
        LOGD("Smb380Sensor::~enable(0, %d) ioctl IOC_SET_ACCELEROMETER %d", en, flags);
        if (ioctl(data_fd, IOC_SET_ACCELEROMETER, &flags))
        {
            LOGE("Smb380Sensor::~enable(0, %d) ioctl IOC_SET_ACCELEROMETER failed", en);
            return -1;
        }
        LOGD("Smb380Sensor::~enable(0, %d) ioctl IOC_SET_ACCELEROMETER mEnabled (%d) = flags", en, mEnabled, flags);
        mEnabled = flags;        
    }
    return 0;
}

bool Smb380Sensor::hasPendingEvents() const {
    LOGD("Smb380Sensor::~hasPendingEvents() %d", mHasPendingEvent);
    return mEnabled;
}

int Smb380Sensor::setDelay(int32_t handle, int64_t delay_ns)
{
    LOGD("Smb380Sensor::~setDelay(%d, %d)", handle, delay_ns);
    /* FIXME needs changes to the kernel driver.
       We need to add a IOCTL that can set the samplingrate
       the driver in ther kernel supports this allready only need
       to add a IOCTL on both sides for that*/
    return 0;
}

int Smb380Sensor::readEvents(sensors_event_t* data, int count)
{
    LOGD("Smb380Sensor::~readEvents() %d", count);
    if (count < 1)
        return -EINVAL;
        
    if (data_fd < 0)
    {
        LOGE("Smb380Sensor::~readEvents() data_fd(%d) < 0", data_fd);
        return -EINVAL;
    }
        
    int numEventReceived = 0;

    while (count && data_fd >= 0) {    
         LOGD("Smb380Sensor::~readEvents() loop count = %d", count);
         struct smb380acc_t sensordata;
         
         if (!ioctl(data_fd, IOCTL_SMB_GET_ACC_VALUE, &sensordata))
         {
   
            mPendingEvent.acceleration.x = sensordata.x;
            mPendingEvent.acceleration.y = sensordata.y;
            mPendingEvent.acceleration.z = sensordata.z;

            mPendingEvent.timestamp = getTimestamp();
            
            if (mHasPendingEvent)
            {
                mHasPendingEvent = false;
            }
         
            if (mEnabled) {
                 *data++ = mPendingEvent;
                 count--;
                 numEventReceived++;
                 LOGD("Smb380Sensor::~readEvents() numEventReceived++");
            }
        }
        else
        {
            LOGE("Smb380Sensor::~readEvents() %d data_fd (%d) IOCTL_SMB_GET_ACC_VALUE failed", count, data_fd);
        }

    }
    LOGD("Smb380Sensor::~readEvents() numEventReceived = %d", numEventReceived);
    return numEventReceived;
}

