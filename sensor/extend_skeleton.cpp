#include <eve/eve.hpp>
#include <eve/module/core.hpp>
#include <vector>

using namespace eve;

int classify_threat(const float* image_data, const float* audio_data, size_t length) {
    constexpr size_t simd_width = wide<float>::size();
    size_t i = 0;
    wide<float> threshold = 0.8f;
    wide<float> total_score = 0.0f;

    for (; i + simd_width <= length; i += simd_width) {
        wide<float> image = load(image_data + i);
        wide<float> audio = load(audio_data + i);
        wide<float> combined = image + audio;
        auto mask = combined > threshold;
        total_score += reduce[mask](combined, plus);
    }

    // Handle remainder scalarly
    float rem_score = 0.0f;
    for (; i < length; ++i) {
        float combined = image_data[i] + audio_data[i];
        if (combined > 0.8f) {
            rem_score += combined;
        }
    }
    float final_score = hz_reduce(total_score) + rem_score;  // Horizontal reduce

    return final_score > 5.0f ? 1 : 0;  // 1 = threat detected
}
//Add to the same file binding with pybind11
m.def("classify_threat", [](py::array_t<float> image_data, py::array_t<float> audio_data) {
    auto img_buf = image_data.request();
    auto aud_buf = audio_data.request();
    if (img_buf.size != aud_buf.size) throw std::runtime_error("Input sizes mismatch");
    return classify_threat(static_cast<float*>(img_buf.ptr), static_cast<float*>(aud_buf.ptr), img_buf.size);
});
