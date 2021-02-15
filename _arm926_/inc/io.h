#ifndef __IO_H__
#define __IO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define read8(x) (*((volatile uint8_t *)(x)))
#define write8(x,y) (*((volatile uint8_t *)(x)) = y)

#define read16(x) (*((volatile uint16_t *)(x)))
#define write16(x,y) (*((volatile uint16_t *)(x)) = y)

#define read32(x) (*((volatile uint32_t *)(x)))
#define write32(x,y) (*((volatile uint32_t *)(x)) = y)

#define read64(x) (*((volatile uint64_t *)(x)))
#define write64(x,y) (*((volatile uint64_t *)(x)) = y)

#ifdef __cplusplus
}
#endif

#endif /* __IO_H__ */