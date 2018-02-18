#ifndef DS18X28_H_
#define DS18X28_H_

#include <stdlib.h>
#include <inttypes.h>
#include "onewire.h"


#define MAXSENSORS 1	// ilo�� czujnik�w


/* return values */
#define DS18X20_OK          0x00
#define DS18X20_ERROR       0x01
#define DS18X20_START_FAIL  0x02
#define DS18X20_ERROR_CRC   0x03

#define DS18X20_POWER_PARASITE 0x00
#define DS18X20_POWER_EXTERN   0x01

/* DS18X20 specific values (see datasheet) */
#define DS18S20_ID 0x10
#define DS18B20_ID 0x28

#define DS18X20_CONVERT_T	0x44
#define DS18X20_READ		0xBE
#define DS18X20_WRITE		0x4E
#define DS18X20_EE_WRITE	0x48
#define DS18X20_EE_RECALL	0xB8
#define DS18X20_READ_POWER_SUPPLY 0xB4

#define DS18B20_CONF_REG    4
#define DS18B20_9_BIT       0
#define DS18B20_10_BIT      (1<<5)
#define DS18B20_11_BIT      (1<<6)
#define DS18B20_12_BIT      ((1<<6)|(1<<5))

// indefined bits in LSB if 18B20 != 12bit
#define DS18B20_9_BIT_UNDF       ((1<<0)|(1<<1)|(1<<2))
#define DS18B20_10_BIT_UNDF      ((1<<0)|(1<<1))
#define DS18B20_11_BIT_UNDF      ((1<<0))
#define DS18B20_12_BIT_UNDF      0

// conversion times in ms
#define DS18B20_TCONV_12BIT      750
#define DS18B20_TCONV_11BIT      DS18B20_TCONV_12_BIT/2
#define DS18B20_TCONV_10BIT      DS18B20_TCONV_12_BIT/4
#define DS18B20_TCONV_9BIT       DS18B20_TCONV_12_BIT/8
#define DS18S20_TCONV            DS18B20_TCONV_12_BIT

// constant to convert the fraction bits to cel*(10^-4)
#define DS18X20_FRACCONV         625

#define DS18X20_SP_SIZE  9

extern uint8_t gSensorIDs[MAXSENSORS][OW_ROMCODE_SIZE];


/* for description of functions see ds18x20.c */

//funkcja zwracaj�ca ilo�� czujnik�w na magistrali 1wire
uint8_t search_sensors(void);
uint8_t	DS18X20_get_power_status(uint8_t id[]);


//funkcja dokonania pomiaru
uint8_t DS18X20_start_meas( uint8_t with_external, uint8_t id[]);


//odczyt z czujnika
uint8_t DS18X20_read_meas(uint8_t *id, uint8_t *subzero, uint8_t *cel, uint8_t *cel_frac_bits);

//odczyt z czujnika gdy jest tylko jeden czujnik. Pomija sprawdzanie numeru seryjnego
uint8_t DS18X20_read_meas_single(uint8_t familycode, uint8_t *subzero, uint8_t *cel, uint8_t *cel_frac_bits);



#endif /* DS18X28_H_ */