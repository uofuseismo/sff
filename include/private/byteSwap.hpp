#ifndef SFF_PRIVATE_BYTESWAP_HPP
#define SFF_PRIVATE_BYTESWAP_HPP
#include <cstdint>
#ifndef BIG_ENDIAN
#define BIG_ENDIAN 0
#endif
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1
#endif
namespace
{

/// @brief Determines the byte order.
/// @result A flag indicating this architecture is BIG_ENDIAN or
///         LITTLE_ENDIAN.
[[nodiscard]] int testByteOrder()
{
    short int word = 0x0001;
    char *b = (char *) &word;
    return (b[0] ? LITTLE_ENDIAN : BIG_ENDIAN);
}

//----------------------------------------------------------------------------//
//                                   Unpack                                   //
//----------------------------------------------------------------------------//



union SI2
{   
    char c2[2];
    int16_t val;
};

union SI4 
{   
    char c4[4];
    int32_t val;
}; 

union SF4 
{   
    char c4[4];
    float val;
}; 

union SF8
{
    char c8[8];
    double val;
};

#pragma omp declare simd uniform(lswap)
[[maybe_unused]] int16_t unpackShort(const char c[2], const bool lswap)
{
    SI2 s;
    if (lswap)
    {
        s.c2[0] = c[1];
        s.c2[1] = c[0];
    }
    else
    {
        s.c2[0] = c[0];
        s.c2[1] = c[1];
    }
    return s.val;
}

#pragma omp declare simd uniform(lswap)
[[maybe_unused]] int32_t unpackInt(const char c[4], const bool lswap)
{
    SI4 s;
    if (lswap)
    {
        s.c4[0] = c[3];
        s.c4[1] = c[2];
        s.c4[2] = c[1];
        s.c4[3] = c[0];
    }
    else
    {
        s.c4[0] = c[0];
        s.c4[1] = c[1];
        s.c4[2] = c[2];
        s.c4[3] = c[3];
    }
    return s.val;
}

#pragma omp declare simd uniform(lswap)
[[maybe_unused]] float unpackFloat(const char c[4], const bool lswap)
{
    SF4 s;
    if (lswap)
    {
        s.c4[0] = c[3];
        s.c4[1] = c[2];
        s.c4[2] = c[1];
        s.c4[3] = c[0];
    }
    else
    {
        s.c4[0] = c[0];
        s.c4[1] = c[1];
        s.c4[2] = c[2];
        s.c4[3] = c[3];
    }
    return s.val;
}

#pragma omp declare simd uniform(lswap)
[[maybe_unused]] double unpackDouble(const char c[8], const bool lswap)
{
    SF8 s;
    if (lswap)
    {
        s.c8[0] = c[7];
        s.c8[1] = c[6];
        s.c8[2] = c[5];
        s.c8[3] = c[4];
        s.c8[4] = c[3];
        s.c8[5] = c[2];
        s.c8[6] = c[1];
        s.c8[7] = c[0];
    }
    else
    {
        s.c8[0] = c[0];
        s.c8[1] = c[1];
        s.c8[2] = c[2];
        s.c8[3] = c[3];
        s.c8[4] = c[4];
        s.c8[5] = c[5];
        s.c8[6] = c[6];
        s.c8[7] = c[7];
    }
    return s.val;
}

//----------------------------------------------------------------------------//
//                                   Packing Functions                        //
//----------------------------------------------------------------------------//

#pragma omp declare simd uniform(lswap)
[[maybe_unused]] void packShort(const int16_t valIn, char c[2],
                                const bool lswap)
{
    SI2 s;
    s.val = valIn;
    if (lswap)
    {
        c[0] = s.c2[1];
        c[1] = s.c2[0];
    }
    else
    {
        c[0] = s.c2[0];
        c[1] = s.c2[1];
    }
}

#pragma omp declare simd uniform(lswap)
[[maybe_unused]] void packInt(const int32_t valIn, char c[4], const bool lswap)
{
    SI4 s;
    s.val = valIn;
    if (lswap)
    {
        c[0] = s.c4[3];
        c[1] = s.c4[2];
        c[2] = s.c4[1];
        c[3] = s.c4[0];
    }
    else
    {
        c[0] = s.c4[0];
        c[1] = s.c4[1];
        c[2] = s.c4[2];
        c[3] = s.c4[3];
    }
}

#pragma omp declare simd uniform(lswap)
[[maybe_unused]] void packFloat(const float valIn, char c[4], const bool lswap)
{
    SF4 s;
    s.val = valIn;
    if (lswap)
    {
        c[0] = s.c4[3];
        c[1] = s.c4[2];
        c[2] = s.c4[1];
        c[3] = s.c4[0];
    }
    else
    {
        c[0] = s.c4[0];
        c[1] = s.c4[1];
        c[2] = s.c4[2];
        c[3] = s.c4[3];
    }
}

#pragma omp declare simd uniform(lswap)
[[maybe_unused]] void packDouble(const double valIn, char c[8],
                                 const bool lswap)
{
    SF8 s;
    s.val = valIn;
    if (lswap)
    {
        c[0] = s.c8[7];
        c[1] = s.c8[6];
        c[2] = s.c8[5];
        c[3] = s.c8[4];
        c[4] = s.c8[3];
        c[5] = s.c8[2];
        c[6] = s.c8[1];
        c[7] = s.c8[0];
    }
    else
    {
        c[0] = s.c8[0];
        c[1] = s.c8[1];
        c[2] = s.c8[2];
        c[3] = s.c8[3];
        c[4] = s.c8[4];
        c[5] = s.c8[5];
        c[6] = s.c8[6];
        c[7] = s.c8[7];
    }
}

///--------------------------------------------------------------------------///
///                            Reverse Bytes for a Number                    ///
///--------------------------------------------------------------------------///
[[nodiscard]] float swapFloat(const float f4)
{
    SF4 s;
    s.val = f4;
    char c4Temp[4];
    std::reverse_copy(s.c4, s.c4 + 4, c4Temp);
    std::copy(c4Temp, c4Temp + 4, s.c4);
    return s.val;
}

}
#endif
