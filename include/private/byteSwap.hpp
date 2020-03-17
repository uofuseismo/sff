#ifndef SFF_BYTESWAP_HPP
#define SFF_BYTESWAP_HPP
#include <cstdint>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

#ifndef BIG_ENDIAN
#define BIG_ENDIAN 0
#endif
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1
#endif
namespace
{

/*!
 * @brief Determines the byte order.
 * @result A flag indicating this architecture is BIG_ENDIAN or
 *         LITTLE_ENDIAN.
 */
int testByteOrder()
{
    short int word = 0x0001;
    char *b = (char *) &word;
    return (b[0] ? LITTLE_ENDIAN : BIG_ENDIAN);
}

//----------------------------------------------------------------------------//
//                                   Unpack                                   //
//----------------------------------------------------------------------------//

#pragma omp declare simd uniform(lswap)
int16_t unpackShort(const char c[2], const bool lswap)
{
    union
    {
        char c2[2];
        int16_t val;
    };
    if (lswap)
    {
        c2[0] = c[1];
        c2[1] = c[0];
    }
    else
    {
        c2[0] = c[0];
        c2[1] = c[1];
    }
    return val;
}

#pragma omp declare simd uniform(lswap)
int32_t unpackInt(const char c[4], const bool lswap)
{
    union
    {
        char c4[4];
        int32_t val;
    };
    if (lswap)
    {
        c4[0] = c[3];
        c4[1] = c[2];
        c4[2] = c[1];
        c4[3] = c[0];
    }
    else
    {
        c4[0] = c[0];
        c4[1] = c[1];
        c4[2] = c[2];
        c4[3] = c[3];
    }
    return val;
}

#pragma omp declare simd uniform(lswap)
float unpackFloat(const char c[4], const bool lswap)
{
    union
    {
        char c4[4];
        float val;
    };
    if (lswap)
    {
        c4[0] = c[3];
        c4[1] = c[2];
        c4[2] = c[1];
        c4[3] = c[0];
    }
    else
    {
        c4[0] = c[0];
        c4[1] = c[1];
        c4[2] = c[2];
        c4[3] = c[3];
    }
    return val;
}

#pragma omp declare simd uniform(lswap)
double unpackDouble(const char c[8], const bool lswap)
{
    union
    {
        char c8[8];
        double val;
    };  
    if (lswap)
    {
        c8[0] = c[7];
        c8[1] = c[6];
        c8[2] = c[5];
        c8[3] = c[4];
        c8[4] = c[3];
        c8[5] = c[2];
        c8[6] = c[1];
        c8[7] = c[0];
    }
    else
    {
        c8[0] = c[0];
        c8[1] = c[1];
        c8[2] = c[2];
        c8[3] = c[3];
        c8[4] = c[4];
        c8[5] = c[5];
        c8[6] = c[6];
        c8[7] = c[7];
    }
    return val;
}

//----------------------------------------------------------------------------//
//                                   Packing Functions                        //
//----------------------------------------------------------------------------//

#pragma omp declare simd uniform(lswap)
void packShort(const int16_t valIn, char c[2], const bool lswap)
{
    union
    {
        char c2[2];
        int16_t val;
    };
    val = valIn;
    if (lswap)
    {
        c[0] = c2[1];
        c[1] = c2[0];
    }
    else
    {
        c[0] = c2[0];
        c[1] = c2[1];
    }
}

#pragma omp declare simd uniform(lswap)
void packInt(const int32_t valIn, char c[4], const bool lswap)
{
    union
    {
        char c4[4];
        int32_t val;
    };
    val = valIn;
    if (lswap)
    {
        c[0] = c4[3];
        c[1] = c4[2];
        c[2] = c4[1];
        c[3] = c4[0];
    }
    else
    {
        c[0] = c4[0];
        c[1] = c4[1];
        c[2] = c4[2];
        c[3] = c4[3];
    }
}

#pragma omp declare simd uniform(lswap)
void packFloat(const float valIn, char c[4], const bool lswap)
{
    union
    {
        char c4[4];
        float val;
    };
    val = valIn;
    if (lswap)
    {
        c[0] = c4[3];
        c[1] = c4[2];
        c[2] = c4[1];
        c[3] = c4[0];
    }
    else
    {
        c[0] = c4[0];
        c[1] = c4[1];
        c[2] = c4[2];
        c[3] = c4[3];
    }
}

#pragma omp declare simd uniform(lswap)
void packDouble(const double valIn, char c[8], const bool lswap)
{
    union
    {
        char c8[8];
        double val;
    };
    val = valIn;
    if (lswap)
    {
        c[0] = c8[7];
        c[1] = c8[6];
        c[2] = c8[5];
        c[3] = c8[4];
        c[4] = c8[3];
        c[5] = c8[2];
        c[6] = c8[1];
        c[7] = c8[0];
    }
    else
    {
        c[0] = c8[0];
        c[1] = c8[1];
        c[2] = c8[2];
        c[3] = c8[3];
        c[4] = c8[4];
        c[5] = c8[5];
        c[6] = c8[6];
        c[7] = c8[7];
    }
}

}
#pragma GCC diagnostic pop
#endif
