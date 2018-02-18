#define F_CPU 1000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "LCD/lcd44780.h"
#include "1Wire/ds18x20.h"


uint8_t czujniki_cnt;		//iloœæ czujników na magistrali

uint8_t subzero, cel, cel_fract_bits; //subzero - temperatura dodatnia==0 lub ujemna==1;
									  //cel - wartosc dziesietna temperatury
									  //cel_fract_bits - wartosc dziesietna po przecinku


int main(void) 
{
	
  lcd_init();                                          // inicjalizacja LCD
  czujniki_cnt = search_sensors();                     /*funkcja search_sensors() zwraca liczbê 
                                                         czujników ma magistrali 1wire*/
  while(1)
  {
    DS18X20_start_meas( DS18X20_POWER_EXTERN, NULL );  // rozkaz pomiaru do czujnika

	if( DS18X20_OK == DS18X20_read_meas_single(gSensorIDs[0], &subzero, &cel, &cel_fract_bits) )
	{
	  lcd_locate(0,0);
	  lcd_str("Temp zew");
	  if(subzero) 
	    lcd_str("-");	              //jeœli subzero==1 wyœwietla znak minus (temp. ujemna)
	  else 
	    lcd_str(" ");	              //jeœli subzero==0 wyœwietl spacjê zamiast znaku minus (temp. dodatnia)

	  lcd_int(cel);	                  // wyœwietl dziesiêtne czêœci temperatury
	  lcd_str(".");	                  // wyœwietl kropkê 
	  lcd_int(cel_fract_bits);        // wyœwietl dziesiêtne czêœci stopnia 
	  lcd_str(" C ");                 // wyœwietl znak jednostek (C - stopnie Celsiusza) 
    }
	else 
	{				
	  lcd_locate(0,9);
	  lcd_str(" error ");	
	}
  }
}




