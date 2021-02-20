/*
This example use Arduino its self to keep time without RTC.
By M Lab
21 Feb 2021
meng.inventor@gmail.com
*/
#include <TimeLib.h>//Download from https://github.com/PaulStoffregen/Time
#include <stdio.h>
void setup() {
  Serial.begin(115200);
  setTime(compile_datetime());
}

void loop() {
  digitalClockDisplay();
  delay(1000);

}


time_t compile_datetime(){
  //Modified from https://stackoverflow.com/questions/1765014/convert-string-from-date-into-a-time-t
  char const *compile_date = __DATE__;
  char const *compile_time = __TIME__;
  char s_month[5];
  int year;
  tmElements_t t;
  static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

  sscanf(compile_date, "%s %hhd %d", s_month, &t.Day, &year);
  sscanf(compile_time, "%2hhd %*c %2hhd %*c %2hhd", &t.Hour, &t.Minute, &t.Second);

  // Find where is s_month in month_names. Deduce month value.
  t.Month = (strstr(month_names, s_month) - month_names) / 3 + 1;

  // year can be given as '2010' or '10'. It is converted to years since 1970
  if (year > 99) t.Year = year - 1970;
  else t.Year = year + 30;

  return makeTime(t);
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}
