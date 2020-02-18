#include "sff/version.hpp"
#include "time.hpp"
#include "sac.hpp"
#include "silixaSEGY.hpp"
#include <pybind11/pybind11.h>

PYBIND11_MODULE(pysff, m)
{
    m.attr("__version__") = SFF_VERSION;
    PBSFF::initializeTime(m);
    PBSFF::initializeSAC(m);

    pybind11::module silixaSegyModule = m.def_submodule("SilixaSEGY");
    PBSFF::SEGY::Silixa::initializeTrace(silixaSegyModule);
}
