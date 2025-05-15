#ifndef BIT_PATH_H
#define BIT_PATH_H

#define SET_BIT(REG,BIT) ((REG) |= (1 << (BIT)))
#define CLR_BIT(REG,BIT) ((REG) &= ~(1 << (BIT)))
#define TOG_BIT(REG,BIT) ((REG) ^= (1 << (BIT)))
#define GET_BIT(REG,BIT) (((REG) >> (BIT)) & 1)

#endif
