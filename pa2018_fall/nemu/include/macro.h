#ifndef __MACRO_H__
#define __MACRO_H__

#define str_temp(x) #x
#define str(x) str_temp(x)

#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)
#define concat3(x, y, z) concat(concat(x, y), z)
#define concat4(x, y, z, w) concat3(concat(x, y), z, w)
#define concat5(x, y, z, v, w) concat4(concat(x, y), z, v, w)
#define concat6(x, y, z, v, w, u) concat5(concat(x, y), z, v, w, u)
#define concat7(x, y, z, v, w, u, h) concat6(concat(x, y), z, v, w, u, h)

#define rw1byte(addr) (*(uint8_t *)(addr))
#define rw2byte(addr) (*(uint16_t *)(addr))
#define rw3byte(addr) (rw1byte(addr) | (rw2byte((void*)(addr) + 1) << 8))
#define rw4byte(addr) (*(uint32_t *)(addr))

#endif
