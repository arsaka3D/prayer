/*
  Prayer.cpp
*/

#include "Prayer.h"
#include "Arduino.h"

/*Macro Function */
#define d2r(x) x *M_PI / 180
#define r2d(x) x * 180 / M_PI

//Constanta
// const float lunarY = 354.367068f;

Prayer::Prayer()
{
}

void Prayer::Update(float TIMEZONE,
                    float LATITUDE,
                    float LONGITUDE,
                    float ALTITUDE,
                    uint16_t YEAR,
                    uint16_t MONTH,
                    uint16_t DATE)
{
  _LATITUDE = LATITUDE;
  _LONGITUDE = LONGITUDE;
  _ALTITUDE = ALTITUDE;
  _TIMEZONE = TIMEZONE;
  _YEAR = YEAR;
  _MONTH = MONTH;
  _DATE = DATE;
  Sholat();
}

float Prayer::fix_hour(float a)
{
  a = a - (float)24.0 * floor(a / 24.0);
  a = a < 0.0 ? a + 24.0 : a;
  return a;
}

float Prayer::fix_angle(float a)
{
  a = a - (float)360.0 * floor(a / 360.0);
  a = a < 0.0 ? a + 360.0 : a;
  return a;
}

float Prayer::Dql(float EJD)
{
  float g = fix_angle((357.529f + 0.98560028f * EJD));
  float q = fix_angle((280.459f + 0.98564736f * EJD));
  float L = fix_angle((q + 1.915f * sin(d2r(g)) + 0.020f * sin(d2r(2 * g))));
  float e = (23.439f - 0.00000036f * EJD);

  float dd = r2d(asin(sin(d2r(e)) * sin(d2r(L)))); // declination of the Sun
  return dd;
}

float Prayer::HourAngle(float Alfa, float Declination, float Latitude)
{
  float rn = acos((-sin(d2r(Alfa)) - sin(d2r(Latitude)) * sin(d2r(Declination))) /
                  (cos(d2r(Latitude)) * cos(d2r(Declination)))) /
             15;
  return r2d(rn);
}

float Prayer::EqT(const float EJD)
{
  float g = fix_angle(357.529f + 0.98560028f * EJD);
  float q = fix_angle(280.459f + 0.98564736f * EJD);
  float L = fix_angle(q + 1.915 * sin(d2r(g)) + 0.020 * sin(d2r(2 * g)));
  float e = (23.439f - 0.00000036f * EJD);

  float RA = r2d(atan2(cos(d2r(e)) * sin(d2r(L)), cos(d2r(L)))) / 15;
  float Eq = (q / 15 - fix_hour(RA));
  return Eq;
}

float Prayer::E_Julian_date(int Year, int Month, int Days, float Longitude)
{
  if (Month <= 2)
  {
    Year -= 1;
    Month += 12;
  }

  float A = floor(((float)Year / 100.0));
  float B = 2 - A + floor(A / 4.0);
  float CLong = Longitude / (float)(15 * 24);
  float JD = floor(365.25 * (float)(Year + 4716)) - 2451545 + floor(30.6001 * (float)(Month + 1)) + (float)Days + B - 1524.5 - CLong;
  return JD;
}

void Prayer::Pray_Time(float TimeZone,
                       float Latitude,
                       float Longitude,
                       float Altitude,
                       float Declination,
                       float EquationOfTime)
{
  // Dzuhur
  float BaseTime = fix_hour((float)12 + TimeZone - (Longitude / 15) - EquationOfTime);
  sholatT[4] = BaseTime + (float)setIkhtiyati / 60;
  floatDzuhur = sholatT[4];

  // Ashr
  float alfa = r2d(-atan(1 / (1 + tan(d2r(fabs(Latitude - Declination))))));
  float HA = HourAngle(alfa, Declination, Latitude);
  sholatT[5] = BaseTime + HA + (float)setIkhtiyati / 60;
  floatAshar = sholatT[5];

  // Maghrib
  alfa = 0.8333f + 0.0347f * sqrt(Altitude);
  HA = HourAngle(alfa, Declination, Latitude);
  sholatT[6] = BaseTime + HA + (float)setIkhtiyati / 60;
  floatMaghrib = sholatT[6];

  // Terbit
  sholatT[2] = BaseTime - HA;
  floatTerbit = sholatT[2];

  // Isya
  HA = HourAngle((float)18, Declination, Latitude);
  sholatT[7] = BaseTime + HA + (float)setIkhtiyati / 60;
  floatIsya = sholatT[7];

  // Shubuh
  HA = HourAngle((float)20, Declination, Latitude);
  sholatT[1] = BaseTime - HA + (float)setIkhtiyati / 60;
  floatSubuh = sholatT[1];

  // Imsak
  sholatT[0] = sholatT[1] - (float)10 / 60;
  floatImsak = sholatT[0];

  // Dhuha
  HA = HourAngle((float)-4.5, Declination, Latitude);
  sholatT[3] = BaseTime - HA;
  floatDhuha = sholatT[3];
}

void Prayer::Sholat()
{
  float EJD = E_Julian_date(_YEAR, _MONTH, _DATE, _LONGITUDE);
  float Decl = Dql(EJD);
  float EqOfTime = EqT(EJD);
  Pray_Time(_TIMEZONE, _LATITUDE, _LONGITUDE, _ALTITUDE, Decl, EqOfTime);

  for (int i = 0; i < 8; i++)
  {
    float stime = sholatT[i];
    uint8_t shour = floor(stime);
    uint8_t sminute = floor((stime - (float)shour) * 60);
    uint8_t ssecond = floor((stime - (float)shour - (float)sminute / 60) * 3600);
    switch (i)
    {
    case 0:
      sprintf(getImsak, "%02d:%02d", shour, sminute);
      break;
    case 1:
      sprintf(getSubuh, "%02d:%02d", shour, sminute);
      break;
    case 2:
      sprintf(getTerbit, "%02d:%02d", shour, sminute);
      break;
    case 3:
      sprintf(getDhuha, "%02d:%02d", shour, sminute);
      break;
    case 4:
      sprintf(getDzuhur, "%02d:%02d", shour, sminute);
      break;
    case 5:
      sprintf(getAshar, "%02d:%02d", shour, sminute);
      break;
    case 6:
      sprintf(getMaghrib, "%02d:%02d", shour, sminute);
      break;
    case 7:
      sprintf(getIsya, "%02d:%02d", shour, sminute);
      break;
    default:
      break;
    }
  }
}

// ==========================================================================
Hijriyah::Hijriyah()
{
}

long Hijriyah::Days(uint16_t YEAR, uint16_t MONTH, uint16_t DATE)
{
  if (MONTH < 3)
  {
    YEAR -= 1;
    MONTH += 12;
  }
  YEAR = YEAR - 2000;
  long ndays = floor(365.25 * YEAR) + floor(30.6001 * (MONTH + 1)) + floor(YEAR / 100) + floor(YEAR / 400) + DATE + 196;
  return ndays;
}

long Hijriyah::DaysHijri(uint16_t YEAR, uint16_t MONTH, uint16_t DATE)
{
  YEAR = YEAR - 1420;
  long hari = floor(29.5 * MONTH - 28.999) + floor(lunarY * YEAR) + DATE;
  return hari;
}

void Hijriyah::Update(uint16_t YEAR, uint16_t MONTH, uint16_t DATE, int16_t CORRECTION) // core --> corection date today=0   yesterday=-1 tomorrow=1
{
  long nday = Days(YEAR, MONTH, DATE) + (1 + CORRECTION);

  long tahun = floor(nday / lunarY) + 1420;
  long bulan = 1;
  long harike = 1;
  while (DaysHijri(tahun, bulan, 1) <= nday)
  {
    tahun++;
  };
  tahun--;
  while (DaysHijri(tahun, bulan, 1) <= nday)
  {
    bulan++;
  };
  bulan--;
  harike = 1 + nday - DaysHijri(tahun, bulan, 1);
  if (bulan == 13)
  {
    bulan = 12;
    harike += 29;
  };
  getHijriyahDate = harike;
  getHijriyahMonth = bulan;
  getHijriyahYear = tahun;
}