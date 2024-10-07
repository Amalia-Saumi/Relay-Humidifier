#include <DHT.h>

// Konfigurasi Sensor DHT22
#define DHTTYPE DHT22
#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE);

// Konfigurasi Relay Humidifier
const int relayPin = 4;   // Pin digital untuk mengontrol relay
const int humidifierTriggerLevel = 60; // Level kelembaban untuk mengaktifkan humidifier

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);
  
  // Inisialisasi sensor DHT22
  dht.begin();
  
  // Inisialisasi pin relay untuk humidifier
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Memastikan relay dalam keadaan OFF (HIGH = off, LOW = on)
}

void loop() {
  // Membaca data dari sensor DHT22
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Cek kegagalan pembacaan sensor DHT
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Gagal membaca sensor DHT!");
  } else {
    Serial.print("Kelembaban: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Suhu: ");
    Serial.print(temperature);
    Serial.println(" *C");
  }

  // Mengontrol relay berdasarkan kelembaban
  if (humidity < humidifierTriggerLevel) {
    digitalWrite(relayPin, LOW); // Aktifkan relay (ON)
    Serial.println("Humidifier ON");
  } else {
    digitalWrite(relayPin, HIGH); // Nonaktifkan relay (OFF)
    Serial.println("Humidifier OFF");
  }

  delay(1000); // Perbarui setiap 1 detik
}

