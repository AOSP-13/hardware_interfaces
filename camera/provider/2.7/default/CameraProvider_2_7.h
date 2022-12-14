/*
 * Copyright (C) 2021 The Android Open Source Project
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

#ifndef ANDROID_HARDWARE_CAMERA_PROVIDER_V2_7_CAMERAPROVIDER_H
#define ANDROID_HARDWARE_CAMERA_PROVIDER_V2_7_CAMERAPROVIDER_H

#include <android/hardware/camera/provider/2.6/ICameraProviderCallback.h>
#include <android/hardware/camera/provider/2.7/ICameraProvider.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace camera {
namespace provider {
namespace V2_7 {
namespace implementation {

using ::android::sp;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::hardware::camera::common::V1_0::CameraDeviceStatus;
using ::android::hardware::camera::common::V1_0::Status;
using ::android::hardware::camera::common::V1_0::TorchModeStatus;
using ::android::hardware::camera::common::V1_0::VendorTag;
using ::android::hardware::camera::common::V1_0::VendorTagSection;
using ::android::hardware::camera::provider::V2_4::ICameraProviderCallback;
using ::android::hardware::camera::provider::V2_5::DeviceState;
using ::android::hardware::camera::provider::V2_7::CameraIdAndStreamCombination;
using ::android::hardware::camera::provider::V2_7::ICameraProvider;
using ::android::hidl::base::V1_0::IBase;

// Default recommended RPC thread count for camera provider implementations
const int HWBINDER_THREAD_COUNT = 6;

template <typename IMPL>
struct CameraProvider : public ICameraProvider {
    CameraProvider() : impl() {}
    ~CameraProvider() {}

    // Caller must use this method to check if CameraProvider ctor failed
    bool isInitFailed() { return impl.isInitFailed(); }

    // Methods from ::android::hardware::camera::provider::V2_4::ICameraProvider follow.
    Return<Status> setCallback(const sp<ICameraProviderCallback>& callback) override {
        return impl.setCallback(callback);
    }

    Return<void> getVendorTags(getVendorTags_cb _hidl_cb) override {
        return impl.getVendorTags(_hidl_cb);
    }

    Return<void> getCameraIdList(getCameraIdList_cb _hidl_cb) override {
        return impl.getCameraIdList(_hidl_cb);
    }

    Return<void> isSetTorchModeSupported(isSetTorchModeSupported_cb _hidl_cb) override {
        return impl.isSetTorchModeSupported(_hidl_cb);
    }

    Return<void> getCameraDeviceInterface_V1_x(const hidl_string& cameraDeviceName,
                                               getCameraDeviceInterface_V1_x_cb _hidl_cb) override {
        return impl.getCameraDeviceInterface_V1_x(cameraDeviceName, _hidl_cb);
    }

    Return<void> getCameraDeviceInterface_V3_x(const hidl_string& cameraDeviceName,
                                               getCameraDeviceInterface_V3_x_cb _hidl_cb) override {
        return impl.getCameraDeviceInterface_V3_x(cameraDeviceName, _hidl_cb);
    }

    // Methods from ::android::hardware::camera::provider::V2_5::ICameraProvider follow.
    Return<void> notifyDeviceStateChange(hardware::hidl_bitfield<DeviceState> newState) override {
        return impl.notifyDeviceStateChange(newState);
    }

    // Methods from ::android::hardware::camera::provider::V2_7::ICameraProvider follow.
    Return<void> getConcurrentStreamingCameraIds(
            getConcurrentStreamingCameraIds_cb _hidl_cb) override {
        return impl.getConcurrentStreamingCameraIds(_hidl_cb);
    }

    Return<void> isConcurrentStreamCombinationSupported(
            const hidl_vec<
                    ::android::hardware::camera::provider::V2_6::CameraIdAndStreamCombination>&
                    configs,
            isConcurrentStreamCombinationSupported_cb _hidl_cb) override {
        return impl.isConcurrentStreamCombinationSupported(configs, _hidl_cb);
    }

    Return<void> isConcurrentStreamCombinationSupported_2_7(
            const hidl_vec<CameraIdAndStreamCombination>& configs,
            isConcurrentStreamCombinationSupported_2_7_cb _hidl_cb) override {
        return impl.isConcurrentStreamCombinationSupported_2_7(configs, _hidl_cb);
    }

  private:
    IMPL impl;
};

}  // namespace implementation
}  // namespace V2_7
}  // namespace provider
}  // namespace camera
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_CAMERA_PROVIDER_V2_4_CAMERAPROVIDER_H