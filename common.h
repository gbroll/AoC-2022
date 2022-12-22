
#ifndef COMMON_H
#define COMMON_H

#define TRUE 1
#define FALSE 0

typedef __uint8_t u8;
typedef __uint16_t u16;
typedef __uint32_t u32;
typedef __uint64_t u64;

typedef __int8_t s8;
typedef __int16_t s16;
typedef __int32_t s32;
typedef __int64_t s64;

typedef enum part {
    PART_ONE = 0,
    PART_TWO = 1
} Part;

#endif /* COMMON_H */