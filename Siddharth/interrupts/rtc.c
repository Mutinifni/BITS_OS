#include <system.h>
#define CURRENT_YEAR 2014                            // Change this each year!
 
UInt16 sec;
UInt16 min;
UInt16 hour;
UInt16 day;
UInt16 month;
UInt16 year;
 
enum
{
      cmos_address = 0x70,
      cmos_data    = 0x71
};
 
 
int get_update_in_progress_flag()
{
      outportb(cmos_address, 0x0A);
      return (inportb(cmos_data) & 0x80);
}
 
 
UInt16 get_RTC_register(int reg)
{
      outportb(cmos_address, reg);
      return inportb(cmos_data);
}
 
 
void read_rtc()
{
      UInt16 last_sec;
      UInt16 last_min;
      UInt16 last_hour;
      UInt16 last_day;
      UInt16 last_month;
      UInt16 last_year;
      UInt16 registerB;
  
      while (get_update_in_progress_flag());

      sec = get_RTC_register(0x00);
      min = get_RTC_register(0x02);
      hour = get_RTC_register(0x04);
      day = get_RTC_register(0x07);
      month = get_RTC_register(0x08);
      year = get_RTC_register(0x09);
 
      do
      {
            last_sec = sec;
            last_min = min;
            last_hour = hour;
            last_day = day;
            last_month = month;
            last_year = year;
 
            while (get_update_in_progress_flag());
            sec = get_RTC_register(0x00);
            min = get_RTC_register(0x02);
            hour = get_RTC_register(0x04);
            day = get_RTC_register(0x07);
            month = get_RTC_register(0x08);
            year = get_RTC_register(0x09);
      } while( (last_sec != sec) || (last_min != min) || (last_hour != hour) || (last_day != day) || (last_month != month) || (last_year != year) );
 
      registerB = get_RTC_register(0x0B);
 
      if (!(registerB & 0x04))
      {
            sec = (sec & 0x0F) + ((sec / 16) * 10);
            min = (min & 0x0F) + ((min / 16) * 10);
            hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
            day = (day & 0x0F) + ((day / 16) * 10);
            month = (month & 0x0F) + ((month / 16) * 10);
            year = (year & 0x0F) + ((year / 16) * 10);
      }
 
      if (!(registerB & 0x02) && (hour & 0x80)) {
            hour = ((hour & 0x7F) + 12) % 24;
      }
 
      year += (CURRENT_YEAR / 100) * 100;
      if(year < CURRENT_YEAR) year += 100;

      print(day);
      print("-");
      print(month);
      print("-");
      print(year);
      print("\t");
      print(hour);
      print(":");
      print(min);
      print(":");
      print(sec);
}