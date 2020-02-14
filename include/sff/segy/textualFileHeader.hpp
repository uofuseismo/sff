#ifndef SFF_SEGY_TEXTUALFILEHEADER_HPP
#define SFF_SEGY_TEXTUALFILEHEADER_HPP
#include <memory>
namespace SFF::SEGY
{
class TextualFileHeader
{
public:
    TextualFileHeader();
    TextualFileHeader(const TextualFileHeader &header);
    TextualFileHeader(TextualFileHeader &&header) noexcept;

    TextualFileHeader& operator=(const TextualFileHeader &header);
    TextualFileHeader& operator=(TextualFileHeader &&header) noexcept;

    ~TextualFileHeader();
    void clear() noexcept;

    void setEBCDIC(const std::string &header);
    void setEBCDIC(const char header[3200]);
    void setASCII(const std::string &header);
    void setASCII(const char header[3200]);
    
    std::string getEBCDIC() const noexcept;
    void getEBCDIC(char *header[3200]) const;
    std::string getASCII() const noexcept;
    void getASCII(char *header[3200]) const;

private:
    class TextualFileHeaderImpl;
    std::unique_ptr<TextualFileHeaderImpl> pImpl;
};
}
#endif
