#include <FirebaseESP32.h>
#include <WiFi.h>

// Informasi Wi-Fi
const char* ssid = "St. Jombor";
const char* password = "satusampai8";

// Informasi Firebase
#define FIREBASE_HOST "https://ta-monitoring-udara-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyDWKlh40hVdpH6ayvVxzApkSpwAYzel0wM"
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Pin sensor dan output
const int mq135_pin = 34;   // MQ135 di pin 34
const int mq2_pin = 35;     // MQ2 di pin 35
const int buzzerPin = 25;   // Buzzer di pin 25

// Threshold dan sensitivitas
const int sensitivity = 350;

int air_quality_mq135 = 0;
int air_quality_mq2 = 0;

// Fungsi membaca sensor
void readSensors() {
    int val_mq135 = analogRead(mq135_pin);
    int val_mq2 = analogRead(mq2_pin);

    air_quality_mq135 = val_mq135 * sensitivity / 4096;
    air_quality_mq2 = val_mq2 * sensitivity / 4096;
}

// Fungsi klasifikasi berdasarkan nilai sensor
String klasifikasi(int nilai) {
    if (nilai <= 50) return "BAIK";
    else if (nilai <= 100) return "SEDANG";
    else if (nilai <= 200) return "TIDAK_SEHAT";
    else if (nilai <= 300) return "SANGAT_TIDAK_SEHAT";
    else return "BERBAHAYA";
}

// Setup WiFi
void setup_wifi() {
    Serial.print("Menghubungkan ke WiFi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi terhubung!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

// Setup awal
void setup() {
    Serial.begin(115200);
    setup_wifi();

    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    pinMode(mq135_pin, INPUT);
    pinMode(mq2_pin, INPUT);
    pinMode(buzzerPin, OUTPUT);

    Serial.println("Monitoring Asap dengan Sensor MQ135 & MQ2");
}

// Loop utama
void loop() {
    readSensors();

    Serial.print("MQ135: ");
    Serial.print(air_quality_mq135);
    Serial.print(" | MQ2: ");
    Serial.println(air_quality_mq2);

    // Kirim data ke Firebase
    Firebase.setInt(firebaseData, "/monitoring/mq135", air_quality_mq135);
    Firebase.setInt(firebaseData, "/monitoring/mq2", air_quality_mq2);

    // Ambil status dari masing-masing sensor
    String status_mq135 = klasifikasi(air_quality_mq135);
    String status_mq2 = klasifikasi(air_quality_mq2);

    // Gunakan status gabungan berdasarkan nilai maksimum
    int nilai_terburuk = max(air_quality_mq135, air_quality_mq2);
    String status_akhir = klasifikasi(nilai_terburuk);

    // Kirim status ke Firebase
    Firebase.setString(firebaseData, "/monitoring/status", status_akhir);

    Serial.print("Status Udara: ");
    Serial.println(status_akhir);

    // Aktifkan buzzer jika status lebih buruk dari SEDANG (nilai > 100)
    if (nilai_terburuk > 100) {
        Serial.println("Buzzer ON: Udara tidak baik!");
        for (int i = 0; i < 5; i++) {
            digitalWrite(buzzerPin, HIGH);
            delay(200);
            digitalWrite(buzzerPin, LOW);
            delay(200);
        }
    } else {
        Serial.println("Buzzer OFF: Udara baik atau sedang.");
        digitalWrite(buzzerPin, LOW);
    }

    delay(1000); // Delay 1 detik sebelum pengukuran berikutnya
}
