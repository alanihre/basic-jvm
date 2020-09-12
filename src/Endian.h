//
// Created by Alan Ihre on 2020-09-11.
//

#ifndef BASIC_JVM_ENDIAN_H
#define BASIC_JVM_ENDIAN_H

enum ENDIANNESS {
    LITTLEENDIAN, BIGENDIAN
};

inline ENDIANNESS CheckArchEndianalityV1(void) {
    int Endian = 0x00000001; // assuming target architecture is 32-bit

    // as Endian = 0x00000001 so MSB (Most Significant Byte) = 0x00 and LSB (Least     Significant Byte) = 0x01
    // casting down to a single byte value LSB discarding higher bytes

    return (*(char *) &Endian == 0x01) ? LITTLEENDIAN : BIGENDIAN;
}

inline void SwapEndian(u2 &val) {
    val = (val << 8) | (val >> 8);
}

inline void SwapEndian(u4 &val) {
    val = (val << 24) | ((val << 8) & 0x00ff0000) |
          ((val >> 8) & 0x0000ff00) | (val >> 24);
}


#endif //BASIC_JVM_ENDIAN_H
