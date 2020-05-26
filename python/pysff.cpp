#include "sff/version.hpp"
#include "time.hpp"
#include "sac.hpp"
#include "silixaSEGY.hpp"
#include "hypoinverse2000.hpp"
#include <pybind11/pybind11.h>

PYBIND11_MODULE(pysff, m)
{
    m.attr("__version__") = SFF_VERSION;
    PBSFF::initializeTime(m);
    PBSFF::initializeSAC(m);

    pybind11::module silixaSegyModule = m.def_submodule("SilixaSEGY");
    PBSFF::SEGY::Silixa::initializeTrace(silixaSegyModule);

    pybind11::module hypo2kModule = m.def_submodule("HypoInverse2000");
    PBSFF::HypoInverse2000::initialize(hypo2kModule);
}
