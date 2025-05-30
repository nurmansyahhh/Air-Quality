# Monitoring Kualitas Udara Berbasis App Android

Repository ini berisi kode program Arduino IDE (.ino) yang digunakan untuk memonitor kualitas udara menggunakan sensor gas **MQ135** dan **MQ2**, dengan dukungan koneksi **Firebase** dan notifikasi buzzer. Project ini merupakan bagian dari Tugas Akhir dengan judul:  
**"Perancangan Sistem Monitoring Kualitas Udara Berbasis App Android dengan MIT App Inventor"**

## 📜 Penjelasan Program `klasifikasi2.ino`

### 🔌 Koneksi & Inisialisasi
- Menggunakan library:
  - `WiFi.h` untuk koneksi internet.
  - `FirebaseESP32.h` untuk integrasi ke Firebase.
- Terhubung ke jaringan WiFi lokal.
- Mengatur kredensial dan endpoint Firebase Realtime Database.

```cpp
const char* ssid = "St. Jombor";
const char* password = "satusampai8";
#define FIREBASE_HOST "https://ta-monitoring-udara-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyDWKlh40hVdpH6ayvVxzApkSpwAYzel0wM"
```

### 🧪 Pembacaan Sensor
- **MQ135** → mendeteksi gas berbahaya seperti CO₂, NH₃, dan benzena.
- **MQ2** → mendeteksi gas seperti LPG, asap, dan hidrogen.
- Nilai sensor dikalikan `sensitivity` (350) lalu disesuaikan ke skala 0–350.

```cpp
air_quality_mq135 = val_mq135 * sensitivity / 4096;
air_quality_mq2 = val_mq2 * sensitivity / 4096;
```

### 📊 Klasifikasi Kualitas Udara
Fungsi `klasifikasi()` akan mengembalikan status kualitas udara berdasarkan nilai sensor:
- `<= 50`: BAIK
- `<= 100`: SEDANG
- `<= 200`: TIDAK_SEHAT
- `<= 300`: SANGAT_TIDAK_SEHAT
- `> 300`: BERBAHAYA

### ☁️ Pengiriman ke Firebase
- Nilai sensor dikirim ke Firebase di path:
  - `/monitoring/mq135`
  - `/monitoring/mq2`
  - `/monitoring/status` (hasil klasifikasi terburuk dari dua sensor)

```cpp
Firebase.setInt(firebaseData, "/monitoring/mq135", air_quality_mq135);
Firebase.setInt(firebaseData, "/monitoring/status", status_akhir);
```

### 🚨 Kendali Buzzer
- Jika status udara lebih buruk dari `SEDANG` (nilai > 100), buzzer akan menyala berkedip 5 kali.
- Jika udara BAIK/SEDANG, buzzer dimatikan.

```cpp
if (nilai_terburuk > 100) {
    // Buzzer ON
} else {
    // Buzzer OFF
}
```

### 🔁 Loop Utama
Program terus berjalan setiap 1 detik:
1. Baca sensor
2. Kirim data
3. Evaluasi status
4. Aktifkan buzzer jika perlu

---

## ⚙️ Perangkat Keras yang Digunakan
- **ESP32**
- **Sensor MQ135**
- **Sensor MQ2**
- **Buzzer**
- Koneksi WiFi

## 📱 Output dan Visualisasi
- Data realtime tersimpan di Firebase.
- Dapat ditampilkan dalam bentuk angka dan status di aplikasi Android menggunakan **MIT App Inventor**.

---

📌 File program utama: [`klasifikasi2.ino`](klasifikasi2.ino)
