#!/bin/sh

# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

DEVICE=galaxysmtd
MANUFACTURER=samsung

####################################
# aries-common
#

    mkdir -p ../../../vendor/$MANUFACTURER/aries-common/proprietary

    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libsecril-client.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/etc/gps.conf -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libsecril-client.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/bin/gpsd -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    chmod 755 ../../../vendor/$MANUFACTURER/aries-common/proprietary/gpsd
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/bin/pvrsrvinit -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    chmod 755 ../../../vendor/$MANUFACTURER/aries-common/proprietary/pvrsrvinit
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/etc/gps.xml -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/firmware/bcm4329.hcd -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/firmware/nvram_net.txt -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/firmware/cypress-touchkey.bin -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/firmware/samsung_mfc_fw.bin -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/egl/libGLES_android.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/egl/libEGL_POWERVR_SGX540_120.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/egl/libGLESv1_CM_POWERVR_SGX540_120.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/egl/libGLESv2_POWERVR_SGX540_120.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/hw/gps.aries.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/hw/gralloc.aries.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/libakm.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/libglslcompiler.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/libIMGegl.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/libpvr2d.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/libpvrANDROID_WSEGL.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/libPVRScopeServices.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/libsec-ril.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/libsrv_init.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/libsrv_um.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/firmware/CE147F02.bin -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/libusc.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/libsensor_yamaha_test.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/lib/libsensorservice.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/bin/orientationd -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    chmod 755 ../../../vendor/$MANUFACTURER/aries-common/proprietary/orientationd
    unzip -j -o ../../../${DEVICE}_update.zip system/vendor/bin/geomagneticd -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    chmod 755 ../../../vendor/$MANUFACTURER/aries-common/proprietary/geomagneticd

    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libActionShot.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libarccamera.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libcamera_client.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libcamerafirmwarejni.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libcameraservice.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libCaMotion.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libcaps.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libPanoraMax1.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libPlusMe.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libs3cjpeg.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libseccamera.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libseccameraadaptor.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libsecjpegencoder.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libtvout.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/lib_tvoutengine.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libtvoutfimc.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libtvouthdmi.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libtvoutservice.so -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/bin/tvoutserver -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    chmod 755 ../../../vendor/$MANUFACTURER/aries-common/proprietary/tvoutserver
    unzip -j -o ../../../${DEVICE}_update.zip system/cameradata/datapattern_420sp.yuv -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/cameradata/datapattern_front_420sp.yuv -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/firmware/CE147F00.bin -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/firmware/CE147F01.bin -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/firmware/CE147F02.bin -d ../../../vendor/$MANUFACTURER/aries-common/proprietary
    unzip -j -o ../../../${DEVICE}_update.zip system/firmware/CE147F03.bin -d ../../../vendor/$MANUFACTURER/aries-common/proprietary

(cat << EOF) | sed s/__DEVICE__/$DEVICE/g | sed s/__MANUFACTURER__/$MANUFACTURER/g > ../../../vendor/$MANUFACTURER/aries-common/aries-vendor-blobs.mk
# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# This file is generated by device/__MANUFACTURER__/__DEVICE__/unzip-files.sh - DO NOT EDIT

# Prebuilt libraries that are needed to build open-source libraries
PRODUCT_COPY_FILES := \\
    vendor/$MANUFACTURER/aries-common/proprietary/libsecril-client.so:obj/lib/libsecril-client.so

# All the blobs necessary for aries platform
PRODUCT_COPY_FILES += \\
    vendor/$MANUFACTURER/aries-common/proprietary/gps.conf:system/etc/gps.conf \\
    vendor/$MANUFACTURER/aries-common/proprietary/libsecril-client.so:system/lib/libsecril-client.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/gpsd:system/vendor/bin/gpsd \\
    vendor/$MANUFACTURER/aries-common/proprietary/pvrsrvinit:system/vendor/bin/pvrsrvinit \\
    vendor/$MANUFACTURER/aries-common/proprietary/gps.xml:system/vendor/etc/gps.xml \\
    vendor/$MANUFACTURER/aries-common/proprietary/bcm4329.hcd:system/vendor/firmware/bcm4329.hcd \\
    vendor/$MANUFACTURER/aries-common/proprietary/nvram_net.txt:system/vendor/firmware/nvram_net.txt \\
    vendor/$MANUFACTURER/aries-common/proprietary/cypress-touchkey.bin:system/vendor/firmware/cypress-touchkey.bin \\
    vendor/$MANUFACTURER/aries-common/proprietary/samsung_mfc_fw.bin:system/vendor/firmware/samsung_mfc_fw.bin \\
    vendor/$MANUFACTURER/aries-common/proprietary/libGLES_android.so:system/lib/egl/libGLES_android.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libEGL_POWERVR_SGX540_120.so:system/vendor/lib/egl/libEGL_POWERVR_SGX540_120.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libGLESv1_CM_POWERVR_SGX540_120.so:system/vendor/lib/egl/libGLESv1_CM_POWERVR_SGX540_120.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libGLESv2_POWERVR_SGX540_120.so:system/vendor/lib/egl/libGLESv2_POWERVR_SGX540_120.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/gps.aries.so:system/vendor/lib/hw/gps.aries.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/gralloc.aries.so:system/vendor/lib/hw/gralloc.aries.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libakm.so:system/vendor/lib/libakm.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libglslcompiler.so:system/vendor/lib/libglslcompiler.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libIMGegl.so:system/vendor/lib/libIMGegl.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libpvr2d.so:system/vendor/lib/libpvr2d.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libpvrANDROID_WSEGL.so:system/vendor/lib/libpvrANDROID_WSEGL.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libPVRScopeServices.so:system/vendor/lib/libPVRScopeServices.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libsec-ril.so:system/vendor/lib/libsec-ril.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libsrv_init.so:system/vendor/lib/libsrv_init.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libsrv_um.so:system/vendor/lib/libsrv_um.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/CE147F02.bin:system/vendor/firmware/CE147F02.bin \\
    vendor/$MANUFACTURER/aries-common/proprietary/libusc.so:system/vendor/lib/libusc.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libsensor_yamaha_test.so:system/vendor/lib/libsensor_yamaha_test.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libsensorservice.so:system/vendor/lib/libsensorservice.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/orientationd:system/vendor/bin/orientationd \\
    vendor/$MANUFACTURER/aries-common/proprietary/geomagneticd:system/vendor/bin/geomagneticd

PRODUCT_COPY_FILES += \\
    vendor/$MANUFACTURER/aries-common/proprietary/libActionShot.so:system/lib/libActionShot.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libarccamera.so:system/lib/libarccamera.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libcamera_client.so:system/lib/libcamera_client.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libcamerafirmwarejni.so:system/lib/libcamerafirmwarejni.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libcameraservice.so:system/lib/libcameraservice.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libCaMotion.so:system/lib/libCaMotion.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libcaps.so:system/lib/libcaps.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libPanoraMax1.so:system/lib/libPanoraMax1.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libPlusMe.so:system/lib/libPlusMe.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libs3cjpeg.so:system/lib/libs3cjpeg.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libseccamera.so:system/lib/libseccamera.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libseccameraadaptor.so:system/lib/libseccameraadaptor.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libsecjpegencoder.so:system/lib/libsecjpegencoder.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libtvout.so:system/lib/libtvout.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/lib_tvoutengine.so:system/lib/lib_tvoutengine.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libtvoutfimc.so:system/lib/libtvoutfimc.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libtvouthdmi.so:system/lib/libtvouthdmi.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/libtvoutservice.so:system/lib/libtvoutservice.so \\
    vendor/$MANUFACTURER/aries-common/proprietary/tvoutserver:system/bin/tvoutserver \\
    vendor/$MANUFACTURER/aries-common/proprietary/datapattern_420sp.yuv:system/cameradata/datapattern_420sp.yuv \\
    vendor/$MANUFACTURER/aries-common/proprietary/datapattern_front_420sp.yuv:system/cameradata/datapattern_front_420sp.yuv \\
    vendor/$MANUFACTURER/aries-common/proprietary/CE147F00.bin:system/firmware/CE147F00.bin \\
    vendor/$MANUFACTURER/aries-common/proprietary/CE147F01.bin:system/firmware/CE147F01.bin \\
    vendor/$MANUFACTURER/aries-common/proprietary/CE147F02.bin:system/firmware/CE147F02.bin \\
    vendor/$MANUFACTURER/aries-common/proprietary/CE147F03.bin:system/firmware/CE147F03.bin
EOF

####################################
# galaxys
#

    mkdir -p ../../../vendor/$MANUFACTURER/$DEVICE/proprietary

    unzip -j -o ../../../${DEVICE}_update.zip system/lib/libcamera.so -d ../../../vendor/$MANUFACTURER/$DEVICE/proprietary

(cat << EOF) | sed s/__DEVICE__/$DEVICE/g | sed s/__MANUFACTURER__/$MANUFACTURER/g > ../../../vendor/$MANUFACTURER/$DEVICE/$DEVICE-vendor-blobs.mk
# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# This file is generated by device/__MANUFACTURER__/__DEVICE__/unzip-files.sh - DO NOT EDIT

# Prebuilt libraries that are needed to build open-source libraries
PRODUCT_COPY_FILES := \\
    vendor/$MANUFACTURER/$DEVICE/proprietary/libcamera.so:obj/lib/libcamera.so

# All the blobs necessary for galaxys
PRODUCT_COPY_FILES += \\
    vendor/$MANUFACTURER/$DEVICE/proprietary/libcamera.so:system/lib/libcamera.so
EOF

####################################

./setup-makefiles.sh
