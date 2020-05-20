#include <iostream>
#include <sstream>
#include <string>
#include "sff/hypoinverse2000/eventSummary.hpp"
#include "sff/hypoinverse2000/stationArchive.hpp"
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
    EXPECT_NEAR(summary.getDistanceToClosestStation(), 4, 1.e-1);
    EXPECT_NEAR(summary.getAzimuthalGap(), 83, 1.e-1);
    EXPECT_NEAR(summary.getResidualTravelTimeRMS(), 0.16, 1.e-2);
    EXPECT_NEAR(summary.getPreferredMagnitude(), 2.37, 1.e-2);

    EXPECT_EQ(summary.getPreferredMagnitudeLabel(), 'L');
    EXPECT_EQ(summary.getNumberOfSWeightedResiduals(), 1);
    EXPECT_EQ(summary.getNumberOfFirstMotions(), 4);
    EXPECT_EQ(summary.getEventIdentifier(),
              static_cast<uint64_t> (60363637));
}

TEST(Hypo2000, StationArchive)
{
    std::string pPickString("RBU  UU  EHZ IPU0202003181320 2596 -14198        0                   0     218110 0      84 85227    300     D 02");
    std::string sPickString("NOQ  UU  HHN    4202003181320             2689ES 2 -15   1424 0 24       0 1341210  14     199   251       0J L01");
    
    SFF::Utilities::Time pickTime;
    StationArchive pPick;  
    EXPECT_NO_THROW(pPick.unpackString(pPickString));
    EXPECT_EQ(pPick.getNetworkName(), "UU");
    EXPECT_EQ(pPick.getStationName(), "RBU");
    EXPECT_EQ(pPick.getChannelName(), "EHZ");
    EXPECT_EQ(pPick.getLocationCode(), "02");
    EXPECT_EQ(pPick.getPRemark(), "IP");
    EXPECT_EQ(pPick.getPFirstMotion(), 'U');
    EXPECT_EQ(pPick.getPWeightCode(), 0);
    EXPECT_NO_THROW(pickTime = pPick.getPPickTime());
    std::stringstream pstream;
    pstream << pickTime;
    EXPECT_EQ(pstream.str(), std::string("2020-03-18T13:20:25.960000"));
    EXPECT_NEAR(pPick.getPResidual(), -0.14, 1.e-2);
    EXPECT_NEAR(pPick.getPWeightUsed(), 1.98, 1.e-2);
    EXPECT_EQ(pPick.getPDelayTime(), 0);
    EXPECT_NEAR(pPick.getEpicentralDistance(), 21.8, 1.e-1);
    EXPECT_NEAR(pPick.getTakeOffAngle(), 110, 1.e-1);
    EXPECT_NEAR(pPick.getPImportance(), 0.3, 1.e-1);
    EXPECT_NEAR(pPick.getDurationMagnitude(), 2.27, 1.e-2);
    EXPECT_FALSE(pPick.haveAmplitudeMagnitude());
    EXPECT_EQ(pPick.getDurationMagnitudeLabel(), 'D');
    EXPECT_FALSE(pPick.haveDataSourceCode());
    EXPECT_EQ(pPick.getDurationMagnitudeWeightCode(), 0);
    EXPECT_FALSE(pPick.haveAmplitudeMagnitudeWeightCode());
    EXPECT_FALSE(pPick.haveAmplitude());
    EXPECT_FALSE(pPick.haveAmplitudeUnits());
    EXPECT_NEAR(pPick.getAzimuth(), 85, 1.e-1); 
    EXPECT_FALSE(pPick.havePeriodOfAmplitudeMeasurement());
    EXPECT_NEAR(pPick.getCodaDuration(), 84, 1.e-1);
    auto pstring = pPick.packString();
    EXPECT_EQ(pstring, pPickString);
    std::cout << pPickString << std::endl;
    std::cout << pstring << std::endl;

    StationArchive sPick;
    EXPECT_NO_THROW(sPick.unpackString(sPickString));
    EXPECT_EQ(sPick.getNetworkName(), "UU");
    EXPECT_EQ(sPick.getStationName(), "NOQ");
    EXPECT_EQ(sPick.getChannelName(), "HHN");
    EXPECT_EQ(sPick.getLocationCode(), "01");
    EXPECT_EQ(sPick.getSRemark(), "ES");
    EXPECT_FALSE(sPick.havePFirstMotion());
    EXPECT_EQ(sPick.getSWeightCode(), 2);
    pickTime = sPick.getSPickTime();
    std::stringstream sstream;
    sstream << pickTime;
    EXPECT_EQ(sstream.str(), std::string("2020-03-18T13:20:26.890000"));
    EXPECT_NEAR(sPick.getSResidual(), -0.15, 1.e-2);
    EXPECT_NEAR(sPick.getSWeightUsed(), 0.24, 1.e-2);
    EXPECT_EQ(sPick.getSDelayTime(), 0);
    EXPECT_NEAR(sPick.getEpicentralDistance(), 13.4, 1.e-1);
    EXPECT_NEAR(sPick.getTakeOffAngle(), 121, 1.e-1);
    EXPECT_EQ(sPick.getSImportance(), 0);
    EXPECT_NEAR(sPick.getAmplitudeMagnitude(), 2.51, 1.e-2);
    EXPECT_FALSE(sPick.haveDurationMagnitude());
    EXPECT_EQ(sPick.getAmplitudeMagnitudeLabel(), 'L');
    EXPECT_EQ(sPick.getDataSourceCode(), 'J');
    EXPECT_EQ(sPick.getAmplitudeMagnitudeWeightCode(), 0);
    EXPECT_FALSE(sPick.haveDurationMagnitudeWeightCode());
    EXPECT_NEAR(sPick.getAmplitude(), 14.24, 1.e-2);
    EXPECT_EQ(sPick.getAmplitudeUnits(), AmplitudeUnits::PEAK_TO_PEAK);
    EXPECT_NEAR(sPick.getAzimuth(), 199, 1.e-1);
    EXPECT_NEAR(sPick.getPeriodOfAmplitudeMeasurement(), 0.14, 1.e-2);
    EXPECT_FALSE(sPick.haveCodaDuration());
    auto sstring = sPick.packString();
    EXPECT_EQ(sstring, sPickString);
    std::cout << sPickString << std::endl;
    std::cout << sstring << std::endl;
}

}
