#include <eve/eve.hpp>
#include <eve/module/core.hpp>
#include <vector>

using namespace eve;

bool detect_gesture(const float* sensor_data, size_t length) {
    constexpr size_t simd_width = wide<float>::size();  // e.g., 8 for AVX2
    size_t i = 0;
    wide<float> threshold = 0.5f;  // Broadcast implicitly

    for (; i + simd_width <= length; i += simd_width) {
        wide<float> data = load(sensor_data + i);
        auto mask = data > threshold;
        if (auto match_index = first_true(mask); match_index.has_value()) {
            return true;  // Gesture detected at first match
        }
    }

    // Handle remainder scalarly
    for (; i < length; ++i) {
        if (sensor_data[i] > 0.5f) {
            return true;
        }
    }
    return false;
}
