
# Monitoring Kualitas Udara Berbasis IoT

Project ini merupakan bagian dari Tugas Akhir dengan judul:  
**"Pengembangan Internet of Things (IoT) untuk Monitoring Kualitas Udara dengan Analisis Polutan Berbasis Machine Learning"**

## 📦 Deskripsi
Sistem ini memanfaatkan sensor MQ135 dan MQ2 untuk mendeteksi kualitas udara. Data dikirim melalui ESP32 ke Firebase, dan ditampilkan melalui aplikasi Android menggunakan MIT App Inventor.

## 🔧 Perangkat yang Digunakan
- ESP32
- Sensor MQ135 (deteksi gas beracun)
- Sensor MQ2 (deteksi asap/gas)
- Buzzer
- Firebase (Realtime Database)
- MIT App Inventor (Aplikasi Android)

## 🔌 Cara Upload Program ke ESP32
1. Buka file `klasifikasi2.ino` di Arduino IDE
2. Pilih Board: ESP32 Dev Module
3. Sambungkan ESP32 via USB
4. Klik Upload

## 📊 Fitur Utama
- Monitoring real-time gas/asap
- Buzzer aktif saat nilai ambang terlampaui
- Menyimpan data ke Firebase
- Menampilkan grafik historis di aplikasi Android

---

## 👨‍💻 Author
Nurmansyah – Teknik Informatika  
Tugas Akhir 2025
