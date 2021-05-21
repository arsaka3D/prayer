# Prayer Library for Arduino

## Contributors

Prayer library merupakan library perhitungan waktu sholat berdasarkan koordinat lokasi suatu tempat. Selain itu, prayer library juga memiliki class untuk mengkonversi tanggal masehi menjadi tanggal hijriyah. Library ini ditujukan untuk mempermudah dalam pembuatan project jam waktu sholat / JWS.
Main source dari library ini diperoleh dari sketch JWS 1000 masjid yang ditulis oleh Bpk. Wardi Utari di dalam group facebook [Untuk1000Masjid](https://www.facebook.com/groups/761058907424496).

## Getting Started

- Download file library, kemudian tambahkan pada folder arduino. Anda dapat mencari tahu bagaimana cara menambahkan library ke arduino.
- Tambhkan prayer library pada bagian atas sketch.

```
    #include <Prayer.h>
```

## Description Code

### 1. Parameter

Library ini memerlukan beberapa parameter diantaranya:

| Parameter  | Description                    | Data Ttype |
| :--------- | :----------------------------- | :--------: |
| Latitude   | Garis lintang                  |   float    |
| Longitude  | Garis Bujur                    |   float    |
| Altitude   | Ketinggian dari permukaan laut |   float    |
| Timezone   | Zona waktu suatu wilayah       |   float    |
| Year       | Tahun                          |    int     |
| Month      | Bulan                          |    int     |
| Date       | Tanggal                        |    int     |
| Correction | Koreksi tanggal hijriyah       |    int     |

### 2. Constractor

Ada dua buah constractor yang harus dipanggil diantaranya:

| Constractor Name | Description                                        |
| :--------------- | :------------------------------------------------- |
| Prayer           | Untuk menjalankan fungsi perhitungan jadwal sholat |
| Hijriyah         | Untuk menjalankan fungsi konversi tanggal hijriyah |

Cara menuliskannya pada sketch adalah sebagai berikut,

```
    Prayer JWS;
    Hijriyah Hijir;
```

Pemberian nama setelah constractor dalam hal ini `JWS` dapat anda ganti dengan nama apapun sesuai keinginan anda, begitu pula dengan nama `Hijir`.

### 3. Update

Untuk mengupdate jadwal anda perlu menjalankan fungsi `Update` yang berisikan parameter.

Untuk mengupdate jadwal sholat gunakan kode berikut.

```
JWS.Update(TimeZone, Latitude, Longitude, Altitude, Year, Month, Date);
```

Untuk mengupdate tanggal hijriyah gunakan kode berikut.

```
Hijir.Update(Year, Month, Date, Correction);
```

### 4. Toleransi Waktu Sholat

Untuk mengatur toleransi waktu sholat, anda dapat mengaturnya melalui parameter `setIkhtiyari`. Berikut contohnya.

```
JWS.setIkhtiyati = 2;
```

### 5. Get Data

Setelah menjalankan constractor dan fungsi update, selanjutnya kita akan mengambil data berupa jadwal sholat ataupun tanggal hijriyah. Berikut adalah daftar class yang bisa dipanggil.

- Daftar Class Prayer

| Class Name     | Description                      | Data Ttype | Format |
| :------------- | :------------------------------- | :--------: | :----: |
| `getImsak`     | Memanggil waktu imsak            |    char    | HH:mm  |
| `getSubuh`     | Memanggil waktu subuh            |    char    | HH:mm  |
| `getTerbit`    | Memanggil waktu terbit           |    char    | HH:mm  |
| `getDhuha`     | Memanggil waktu dhuha            |    char    | HH:mm  |
| `getDzuhur`    | Memanggil waktu dzuhur           |    char    | HH:mm  |
| `getAshar`     | Memanggil waktu ashar            |    char    | HH:mm  |
| `getMaghrib`   | Memanggil waktu maghrib          |    char    | HH:mm  |
| `getIsya`      | Memanggil waktu isya             |    char    | HH:mm  |
| `floatImsak`   | Waktu imsak dalam bentuk float   |   float    |        |
| `floatSubuh`   | Waktu subuh dalam bentuk float   |   float    |        |
| `floatTerbit`  | Waktu terbit dalam bentuk float  |   float    |        |
| `floatDhuha`   | Waktu dhuha dalam bentuk float   |   float    |        |
| `floatDzuhur`  | Waktu dzuhur dalam bentuk float  |   float    |        |
| `floatAshar`   | Waktu ashar dalam bentuk float   |   float    |        |
| `floatMaghrib` | Waktu maghrib dalam bentuk float |   float    |        |
| `floatIsya`    | Waktu isya dalam bentuk float    |   float    |        |

Contoh kita ingin memanggil waktu sholat dzuhur dan menampilkannya ke dalam serial monitor, maka scriptnya seperti berikut,

```
    Serial.print("DZUHUR : ");
    Serial.println(JWS.getDzuhur);
```

- Daftar Class Hijriyah

| Class Name         | Description                | Data Ttype | Format |
| :----------------- | :------------------------- | :--------: | :----: |
| `getHijriyahDate`  | Memanggil tanggal hijriyah |    int     |   d    |
| `getHijriyahMonth` | Memanggil bulan hijriyah   |    int     |   m    |
| `getHijriyahYear`  | Memanggil tahun hijriyah   |    int     |  yyyy  |

Contoh kita ingin memanggil tanggal, bulan, dan tahun hijriyah dan akan menampilkannya ke dalam serial monitor. Berikut scriptnya,

```
    Serial.print("Date : ");
    Serial.println(Hijir.getHijriyahDate);
    Serial.print("Month : ");
    Serial.println(Hijir.getHijriyahMonth);
    Serial.print("Year : ");
    Serial.println(Hijir.getHijriyahYear);
```

Anda dapat menambahkan char array yang berisikan nama bulan dalam hijriyah kemudian menggunakan class `getHijriyahMonth` sebagai indexnya. Contoh sebagai berikut,

```
    char BulanHjrName[][16] = {"", "Muharram", "Shafar", "Rabi’ul Awal", "Rabi’ul Akhir", "Jumadil Awal", "Jumadil Akhir", "Rajab", "Sya'ban", "Ramadhan", "Syawal", "Zulqaidah", "Zulhijjah"};
```

```
    Serial.print("Month : ");
    Serial.println(BulanHjrName[Hijir.getHijriyahMonth]);
```

Untuk lebih lengkapnya, anda dapat melihatnya di dalam folder example/test_prayer.ino

## Board Supported

Library ini sudah dicoba pada board :

- Arduino nano 328
- ESP32 WROOM

dan kemungkinan akan bekerja pada board-board dengan arduino compatible.

##  
