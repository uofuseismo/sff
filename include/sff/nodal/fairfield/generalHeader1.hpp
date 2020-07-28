#ifndef SFF_NODAL_FAIRFIELD_GENERALHEADER1_HPP
#define SFF_NODAL_FAIRFIELD_GENERALHEADER1_HPP
#include <memory>
#include "sff/utilities/time.hpp"

namespace SFF::Nodal::Fairfield
{

class GeneralHeader1
{
public:
    GeneralHeader1();
    GeneralHeader1(const GeneralHeader1 &gh1);
    GeneralHeader1(GeneralHeader1 &&gh1) noexcept;
    GeneralHeader1& operator=(const GeneralHeader1 &gh1);
    GeneralHeader1& operator=(GeneralHeader1 &&gh1) noexcept;

    ~GeneralHeader1(); 
    void unpack(const char data[32]);

    SFF::Utilities::Time getStartTime() const noexcept;
    /// @result Gets the file number
    int getFileNumber() const noexcept;
    /// @result The format code.
    int getDataFormatCode() const noexcept;
    /// @result The number of general headers
    int getNumberOfGeneralHeaders() const noexcept;
    /// @result Gets the manufacturer code.
    int getManufacturersCode() const noexcept;
    /// @result The base scan interval which is equivalent to the sampling
    ///         rate in Hz for this file type.
    int getBaseScanInterval() const noexcept; 
    /// @result The serial number.
    int getSerialNumber() const noexcept;
    /// @result The record length in increments of 0.512 seconds.
    /// @note I don't think this is meaningful in this context.
    int getRecordLength() const noexcept;
    /// @result The polarity code.
    int getPolarityCode() const noexcept; 
    /// @result The number of scan types per record.
    int getNumberOfScanTypesPerRecord() const noexcept;
    /// @result The number of channel sets per scan type.
    int getNumberOfChannelSetsPerScanType() const noexcept;
    /// @result The number of 32 byte fields added to the end of each scan type
    ///         header.
    int getNumberOfSkewBlocks() const noexcept;
    /// @result The extended header length.
    int getNumberOfExtendedHeaders() const noexcept;
    /// @result The external header length.
    int getNumberOfExternalHeaders() const noexcept;
private:
    class GeneralHeader1Impl;
    std::unique_ptr<GeneralHeader1Impl> pImpl;
};
std::ostream& operator<<(std::ostream &os, const GeneralHeader1 &gh1);

}
#endif
