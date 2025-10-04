#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

PYBIND11_MODULE(simd_modules, m) {
    m.def("detect_gesture", [](py::array_t<float> sensor_data) {
        auto buf = sensor_data.request();
        return detect_gesture(static_cast<float*>(buf.ptr), buf.size);
    });
} 
