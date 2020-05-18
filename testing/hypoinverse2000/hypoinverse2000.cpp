#include <iostream>
#include <sstream>
#include <string>
#include "sff/hypoinverse2000/eventSummary.hpp"
#include "sff/utilities/time.hpp"
#include <gtest/gtest.h>

namespace 
{
using namespace SFF::HypoInverse2000;

TEST(Hypo2000, EventSummary)
{
    const std::string line = "202003181320217640 4594112  399  771    24 83  4  1633184  88154 5  44298     33    1  44  87  4     100    47       D 24 L237 20         60363637L237  20        5FUUP1";
    EventSummary summary;
    SFF::Utilities::Time originTime;
    EXPECT_NO_THROW(summary.unpackString(line));
    EXPECT_NO_THROW(originTime = summary.getOriginTime());
    std::stringstream sstream;
    sstream << originTime;
    EXPECT_EQ(sstream.str(),
              std::string("2020-03-18T13:20:21.760000"));
    EXPECT_EQ(originTime.getYear(), 2020);
    EXPECT_EQ(originTime.getMonth(), 3);
    EXPECT_EQ(originTime.getDayOfMonth(), 18);
    EXPECT_EQ(originTime.getHour(), 13);
    EXPECT_EQ(originTime.getMinute(), 20);
    EXPECT_EQ(originTime.getSecond(), 21);
    EXPECT_EQ(originTime.getMicroSecond(), 760000);
    EXPECT_NEAR(summary.getLatitude(), 40.7657, 1.e-4);
    auto lon = summary.getLongitude();
    if (lon > 180){lon = lon - 360;}
    EXPECT_NEAR(lon, -112.066, 1.e-3);
    EXPECT_NEAR(summary.getDepth(), 7.71, 1.e-2);
    EXPECT_EQ(summary.getNumberOfWeightedResiduals(), 24);
    EXPECT_NEAR(summary.getAzimuthalGap(), 83, 1.e-1);
    EXPECT_NEAR(summary.getResidualTravelTimeRMS(), 0.16, 1.e-2);
    EXPECT_NEAR(summary.getPreferredMagnitude(), 2.37, 1.e-2);

    EXPECT_EQ(summary.getPreferredMagnitudeLabel(), 'L');
    EXPECT_EQ(summary.getNumberOfFirstMotions(), 4);
    EXPECT_EQ(summary.getEventIdentifier(),
              static_cast<uint64_t> (60363637));
}

}
