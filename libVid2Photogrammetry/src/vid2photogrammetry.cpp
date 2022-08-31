#include <pybind11/pybind11.h>

#include "extractFrames.hpp"
#include "resizeFrames.hpp"
#include "detectBlur.hpp"
#include "denoiseFrames.hpp"
#include "deleteNearDuplicates.hpp"
#include "deleteOutliers.hpp"

namespace py = pybind11;

PYBIND11_MODULE(vid2photogrammetry, m) {
    m.doc() = "Epic gaming!";
    m.def("extractFrames", &extractFrames);
    m.def("resizeFrames", &resizeFrames);
    m.def("removeBlurryFrames", &removeBlurryFrames);
    m.def("denoiseFrames", &denoiseFrames);
    m.def("deleteNearDuplicates", &deleteNearDuplicates);
    m.def("deleteOutliers", &deleteOutliers);
}