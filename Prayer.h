/*
  Prayer.h
*/

#ifndef Prayer_h
#define Prayer_h

#include "Arduino.h"

class Prayer
{
public:
  Prayer();
  void Update(float TIMEZONE = 7,
              float LATITUDE = -6.5212022,
              float LONGITUDE = 106.7762829,
              float ALTITUDE = 45,
              uint16_t YEAR = 2021,
              uint16_t MONTH = 4,
              uint16_t DATE = 16);

  float floatImsak;
  float floatSubuh;
  float floatTerbit;
  float floatDhuha;
  float floatDzuhur;
  float floatAshar;
  float floatMaghrib;
  float floatIsya;

  char getImsak[6];
  char getSubuh[6];
  char getTerbit[6];
  char getDhuha[6];
  char getDzuhur[6];
  char getAshar[6];
  char getMaghrib[6];
  char getIsya[6];

  float sholatT[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  uint16_t setIkhtiyati = 2;

private:
  float fix_hour(float a);
  float fix_angle(float a);
  float Dql(float EJD);
  float HourAngle(float Alfa, float Declination, float Latitude);
  float EqT(const float EJD);
  float E_Julian_date(int Year, int Month, int Days, float Longitude);
  void Pray_Time(float TimeZone,
                 float Latitude,
                 float Longitude,
                 float Altitude,
                 float Declination,
                 float EquationOfTime);
  void Sholat();
  float _LATITUDE;
  float _LONGITUDE;
  float _ALTITUDE;
  float _TIMEZONE;
  uint16_t _YEAR;
  uint16_t _MONTH;
  uint16_t _DATE;
};

class Hijriyah
{
public:
  Hijriyah();
  void Update(uint16_t YEAR, uint16_t MONTH, uint16_t DATE, int16_t CORRECTION);

  // uint16_t DATE;
  // uint16_t MONTH;
  // uint16_t YEAR;
  // int16_t CORRECTION;
  uint16_t getHijriyahDate;
  uint16_t getHijriyahMonth;
  uint16_t getHijriyahYear;
  const float lunarY = 354.367068f;

private:
  long Days(uint16_t YEAR, uint16_t MONTH, uint16_t DATE);
  long DaysHijri(uint16_t YEAR, uint16_t MONTH, uint16_t DATE);
};

#endif