#include "system.h"
#define CURRENT_YEAR 2014                            // Change this each year!

struct Time
{ 
      unsigned char sec;
      unsigned char min;
      unsigned char hour;
      unsigned char day;
      unsigned char month;
      unsigned int year;
 }current_time;

/* Prints an instance of Time struct */
void print_Time(Time t)
{
      print(t.day);
      print("-");
      print(t.month);
      print("-");
      print(t.year);
      print("\t");
      print(t.hour);
      print(":");
      print(t.min);
      print(":");
      print(t.sec);
}

/* Checks whether year is a leap year, returns 1 if True, 0 if false */
unsigned char is_leap_year(unsigned int year)
{
      if(year%4 == 0 && year%400 != 0)
      {
            return 1;
      }
      return 0;
}

/* Adds Time struct 'c' to another Time 't' and stores answer in 't', returns 1
* if no change in t.year, otherwise returns 0. */
unsigned char add_Time(Time *t, Time *c)
{
      unsigned char carry = 0, p;
      unsigned char isleap = is_leap_year(t->year);

      t->sec = t->sec + c->sec;
      carry = t->sec / 60;
      t->sec %= 60;

      t->min = t->min + c->min + carry;
      carry = t->min / 60;
      t->min %= 60;    

      t->hour = t->hour + c->hour + carry;
      carry = t->hour / 24;
      t->hour %= 24;    

      switch(t->month)
      {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                  p = 31;
                  break;
            case 2:
                  if(isleap)
                  {
                        p = 29;
                        break;
                  }
                  p = 28;
                  break;
            default:
                  p = 30;
                  break;
      }

      t->day = t->day + c->day + carry;
      carry = t->sec / p;
      t->sec %= p;

      t->month = t->month + c->month + carry;
      carry = t->month / 12;
      t->sec %= 12;     

      t->year = t->year + c->year + carry;

      return 0;
}

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
 
 
unsigned char get_RTC_register(int reg)
{
      outportb(cmos_address, reg);
      return inportb(cmos_data);
}

void read_rtc()
{
      unsigned char last_sec;
      unsigned char last_min;
      unsigned char last_hour;
      unsigned char last_day;
      unsigned char last_month;
      unsigned char last_year;
      unsigned char registerB;
  
      // Note: This uses the "read registers until you get the same values twice in a row" technique
      //       to avoid getting dodgy/inconsistent values due to RTC updates

      while (get_update_in_progress_flag());    // Make sure an update isn't in progress

      current_time.sec = get_RTC_register(0x00);
      current_time.min = get_RTC_register(0x02);
      current_time.hour = get_RTC_register(0x04);
      current_time.day = get_RTC_register(0x07);
      current_time.month = get_RTC_register(0x08);
      current_time.year = get_RTC_register(0x09);
 
      do
      {
            last_sec = current_time.sec;
            last_min = current_time.min;
            last_hour = current_time.hour;
            last_day = current_time.day;
            last_month = current_time.month;
            last_year = current_time.year;
 
            while (get_update_in_progress_flag());  // Make sure an update isn't in progress
            current_time.sec = get_RTC_register(0x00);
            current_time.min = get_RTC_register(0x02);
            current_time.hour = get_RTC_register(0x04);
            current_time.day = get_RTC_register(0x07);
            current_time.month = get_RTC_register(0x08);
            current_time.year = get_RTC_register(0x09);
      } while( (last_sec != current_time.sec) || (last_min != current_time.min) || (last_hour != current_time.hour) || (last_day != current_time.day) || (last_month != current_time.month) || (last_year != current_time.year) );
 
      registerB = get_RTC_register(0x0B);

      // Convert BCD to binary values if necessary
 
      if (!(registerB & 0x04))
      {
            current_time.sec = (current_time.sec & 0x0F) + ((current_time.sec / 16) * 10);
            current_time.min = (current_time.min & 0x0F) + ((current_time.min / 16) * 10);
            current_time.hour = ( (current_time.hour & 0x0F) + (((current_time.hour & 0x70) / 16) * 10) ) | (current_time.hour & 0x80);
            current_time.day = (current_time.day & 0x0F) + ((current_time.day / 16) * 10);
            current_time.month = (current_time.month & 0x0F) + ((current_time.month / 16) * 10);
            current_time.year = (current_time.year & 0x0F) + ((current_time.year / 16) * 10);
      }

      /* Add time according to system time zone */
      Time timezone = {0, 30, 5, 0, 0, 0};     
      add_Time(&current_time, &timezone);

      // Convert 12 hour clock to 24 hour clock if necessary      
      if (!(registerB & 0x02) && (current_time.hour & 0x80)) {
            current_time.hour = ((current_time.hour & 0x7F) + 12) % 24;
      }
      
      // Calculate the full (4-digit) year      
       current_time.year += (CURRENT_YEAR / 100) * 100;  
      if(current_time.year < CURRENT_YEAR) current_time.year += 100;

      print_Time(current_time);
}