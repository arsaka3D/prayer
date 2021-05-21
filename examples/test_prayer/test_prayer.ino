#include <Prayer.h>
// Prayer parameter
float Latitude = -6.1822265;
float Longitude = 106.8014452;
float Altitude = 13;
float TimeZone = 7;
uint16_t Year = 2021;
uint16_t Month = 5;
uint16_t Date = 21;
int16_t Correction = 0; //Koreksi tanggal hijriyah, -1 untuk mengurangi, 0 tanpa koreksi, 1 untuk menambah

//Month name
char BulanHjrName[][16] = {"", "Muharram", "Shafar", "Rabi’ul Awal", "Rabi’ul Akhir", "Jumadil Awal", "Jumadil Akhir", "Rajab", "Sya'ban", "Ramadhan", "Syawal", "Zulqaidah", "Zulhijjah"};

// Constractor
Prayer JWS;
Hijriyah Hijir;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    JWS.Update(TimeZone, Latitude, Longitude, Altitude, Year, Month, Date); // Jalankan fungsi ini untuk update jadwal sholat
    JWS.setIkhtiyati = 2;                                                   // Set ikhtiyati, toleransi waktu sholat

    Serial.println("---------------------- DATA CHAR ----------------------");
    Serial.print("IMSAK : ");
    Serial.println(JWS.getImsak);
    Serial.print("SUBUH : ");
    Serial.println(JWS.getSubuh);
    Serial.print("TERBIT : ");
    Serial.println(JWS.getTerbit);
    Serial.print("DHUHA : ");
    Serial.println(JWS.getDhuha);
    Serial.print("DZUHUR : ");
    Serial.println(JWS.getDzuhur);
    Serial.print("ASHAR : ");
    Serial.println(JWS.getAshar);
    Serial.print("MAGHRIB : ");
    Serial.println(JWS.getMaghrib);
    Serial.print("ISYA : ");
    Serial.println(JWS.getIsya);
    Serial.println("=================================");

    Serial.println("---------------------- DATA FLOAT ----------------------");
    Serial.print("IMSAK : ");
    Serial.println(JWS.floatImsak);
    Serial.print("SUBUH : ");
    Serial.println(JWS.floatSubuh);
    Serial.print("TERBIT : ");
    Serial.println(JWS.floatTerbit);
    Serial.print("DHUHA : ");
    Serial.println(JWS.floatDhuha);
    Serial.print("DZUHUR : ");
    Serial.println(JWS.floatDzuhur);
    Serial.print("ASHAR : ");
    Serial.println(JWS.floatAshar);
    Serial.print("MAGHRIB : ");
    Serial.println(JWS.floatMaghrib);
    Serial.print("ISYA : ");
    Serial.println(JWS.floatIsya);
    Serial.println("=================================");

    Serial.println("---------------------- TANGGAL HIJRIYAH ----------------------");
    Hijir.Update(Year, Month, Date, Correction); //Jalankan fungsi ini untuk update tanggal
    Serial.print("Date : ");
    Serial.println(Hijir.getHijriyahDate);
    Serial.print("Month : ");
    Serial.println(BulanHjrName[Hijir.getHijriyahMonth]);
    Serial.print("Year : ");
    Serial.println(Hijir.getHijriyahYear);
    Serial.println("=================================");

    delay(5000);
}
