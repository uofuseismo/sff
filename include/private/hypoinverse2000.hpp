#ifndef SFF_PRIVATE_HYPOINVERSE2000_HPP
#define SFF_PRIVATE_HYPOINVERSE2000_HPP
#include <cmath>
#include <array>
#include <locale>
#include <algorithm>
namespace
{

void ltrim(std::string &s)
{
    auto it = std::find_if(s.begin(), s.end(),
                           [](char c) {
                               return !std::isspace<char>(c, std::locale::classic());
                           });
    s.erase(s.begin(), it);
}

void rtrim(std::string &s)
{
    auto it = std::find_if(s.rbegin(), s.rend(),
                           [](char c) {
                               return !std::isspace<char>(c, std::locale::classic());
                           });
    s.erase(it.base(), s.end());
}

[[maybe_unused]] void trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}

char unpackChar(const int i1, const char *stringPtr, const int maxLen)
{
    if (i1 >= maxLen){return '\0';}
    if (stringPtr[i1] == ' '){return '\0';}
    return stringPtr[i1];
}

std::pair<bool, char> unpackCharPair(const int i1, const char *stringPtr,
                                     const int maxLen)
{
    auto c = unpackChar(i1, stringPtr, maxLen);
    return std::pair(c != '\0', c);
}

int unpackInt(const int i1, const int i2, const char *stringPtr,
              const int maxLen)
{
    if (i1 >= maxLen){return std::numeric_limits<int>::max();}
    char subString[8];
    std::fill(subString, subString+8, '\0');
    std::copy(stringPtr+i1,  stringPtr+std::min(i1 + maxLen, i2), subString);
    // Deal with negative numbers
    try
    {
        return std::stoi(subString);
    }
    catch (const std::exception &e)
    {
        for (int i=i2-i1-1; i>=0; --i)
        {
            if (subString[i] == '-'){return -1;}
        }
        return std::numeric_limits<int>::max();
    }
}

std::pair<bool, int> unpackIntPair(const int i1, const int i2,
                                   const char *stringPtr,
                                   const int maxLen)
{
    auto i = unpackInt(i1, i2, stringPtr, maxLen);
    return std::pair(i < std::numeric_limits<int>::max(), i);
}


uint64_t unpackUInt64(const int i1, const int i2, const char *stringPtr,
                      const int maxLen)
{
    if (i1 >= maxLen){return std::numeric_limits<int>::max();}
    std::array<char, 11> subString{"\0\0\0\0\0\0\0\0\0\0"};
    std::copy(stringPtr + i1,  stringPtr + std::min(i1 + maxLen, i2),
              subString.data());
    try
    {
        return std::stol(subString.data());
    }
    catch (const std::exception &e)
    {
        return std::numeric_limits<uint64_t>::max();
    }
}

[[maybe_unused]] std::pair<bool, uint64_t>
    unpackUInt64Pair(int i1, int i2, const char *stringPtr,
                     const int maxLen)
{
    auto i = unpackUInt64(i1, i2, stringPtr, maxLen);
    return std::pair(i < std::numeric_limits<uint64_t>::max(), i);
}

double unpackDouble(const int i1, const int i2,
                    const int whole,
                    const char *stringPtr,
                    const int maxLen)
{
    double result = std::numeric_limits<double>::max();
    std::string swork;
    swork.reserve(i2-i1);
    for (int i=i1; i<std::min(maxLen, i2); ++i)
    {
        if (!isblank(stringPtr[i])){swork.push_back(stringPtr[i]);}
    }
    if (swork.empty()){return std::numeric_limits<double>::max();} 
    try 
    {
        double temp = std::stod(swork);
        double xden = std::pow(10.0, -(i2 - i1 - whole));
        result = xden*temp;
    }
    catch (const std::exception &e)
    {
#ifndef DNDEBUG
        std::cout << "Failed to unpack: " << swork << std::endl; 
#endif
        return std::numeric_limits<double>::max();
    }
    return result;
/*  
    double result = std::numeric_limits<double>::max();
    // Copy whole
    std::string snum;
    snum.reserve(10);
    auto j1 = i1;
    auto j2 = i1 + whole;
    double ipos = 1;
    for (int j=j1; j<std::min(j2, maxLen); ++j)
    {
        if (!isblank(stringPtr[j])){snum.push_back(stringPtr[j]);}
    }
    snum.push_back('.');
    // Copy decimal
    j1 = i1 + whole;
    j2 = i2;
    for (int j=j1; j<std::min(j2, maxLen); ++j)
    {
        //if (!isblank(stringPtr[j])){snum.push_back(stringPtr[j]);}
        if (!isblank(stringPtr[j]))
        {
            if (stringPtr[j] == '-')
            {
                ipos =-1;
            }
            else
            {
                snum.push_back(stringPtr[j]);
            }
        }
    }
    if (!snum.empty())
    {
        try
        {
            result = ipos*std::stod(snum);
        }
        catch (const std::exception &e)
        {
            return result;
        }
    }
    return result;
*/
}

std::pair<bool, double> unpackDoublePair(const int i1, const int i2,
                                         const int whole,
                                         const char *stringPtr,
                                         const int maxLen)
{
    auto d = unpackDouble(i1, i2, whole, stringPtr, maxLen);
    return std::pair(d < std::numeric_limits<double>::max(), d);
}

std::string unpackString(int i1, int i2, const char *stringPtr,
                         const int maxLen)
{
    std::string result;
    result.resize(i2-i1, '\0');
    if (i1 >= maxLen){return result;}
    // Is string blank?
    bool lblank = true;
    for (int i=i1; i<std::min(maxLen, i2); ++i)
    {
        if (!std::isblank(stringPtr[i])){lblank = false;}
    }
    if (lblank){return result;}
    for (int i=i1; i<std::min(maxLen, i2); ++i)
    {
        result[i-i1] = stringPtr[i];
    }
    return result;
}

[[maybe_unused]]
void setString(const int i1, const int i2, const std::string &add,
               std::string &update)
{
    if (add.empty()){return;}
#ifdef DNDEBUG
    assert(i1 < i2);
    assert(i2 <= update.size());
#endif
    auto ncopy = std::min(i2 - i1, static_cast<int> (add.size()));
    std::copy(add.begin(), add.begin()+ncopy, update.begin()+i1);
}

[[maybe_unused]]
void setInteger(const int i1, const int i2, const int value,
                std::string &update,
                const bool keepLeadingZero = true)
{
#ifdef DNDEBUG
    assert(i1 < i2);
    assert(i2 <= update.size());
#endif
    int len = i2 - i1;
    std::string cformat = "%0" + std::to_string(i2-i1) + "d";
    char c16[16];
    std::fill(c16, c16+16, '\0');
    sprintf(c16, cformat.c_str(), value);
    if (keepLeadingZero)
    {
        std::copy(c16, c16 + len, update.begin() + i1);
    }
    else
    {
        int j = 0; // If this is all zero then copy something
        bool lAllZero = true;
        for (int i = 0; i < len; ++i)
        {
            if (c16[i] != '0' && c16[i] != '-')
            {
                j = i;
                lAllZero = false;
                break;
            }
        }
        // Deal with negative
        if (value < 0 && j > 0)
        {
            j = j - 1;
            c16[j] = '-';
        }
        if (!lAllZero)
        {
            std::copy(c16 + j, c16 + len, update.begin() + i1 + j);
        }
        else
        {
            update[i2-1] = '0';
        }
    }
    /*
    char cvalue[10];
    // Copy each digit
    auto approxValue = 0;
    for (int i = 0; i < len; ++i)
    {
        auto digit = static_cast<int> (value/std::pow(10, i));
        auto c = std::to_string(digit);
        cvalue[len-1-i] = c[0];
        update[i2-1-i] = c[0];
    }
    std::cout << cvalue << std::endl;
     */
}
[[maybe_unused]] std::pair<bool, std::string>
unpackStringPair(int i1, int i2, const char *stringPtr, const int maxLen)
{
    auto s = unpackString(i1, i2, stringPtr, maxLen);
    return std::pair(s[0] != '\0', s);
}

}
#endif
