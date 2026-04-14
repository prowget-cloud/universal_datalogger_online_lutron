# 📡 Universal Lutron SD-Series IoT Gateway (ESP32)

Project ini adalah solusi IoT berbasis **ESP32** untuk mengonlinekan instrumen profesional **Lutron SD Card Series** (seperti YK-37UVSD UV Meter). Gateway ini membaca data stream RS232 dari alat Lutron dan mengirimkannya secara real-time ke **Google Sheets** atau webserver kustom.

---

## ✨ Fitur Utama
- **Auto-Detect Model**: Mengenali jenis alat Lutron secara otomatis melalui Unit ID (D12/D11).
- **WiFi Manager UI**: Konfigurasi SSID, Password, dan URL Server via smartphone (Captive Portal).
- **Persistent Storage**: Menyimpan konfigurasi ke memori internal menggunakan **LittleFS**.
- **Accurate Parsing**: Konversi otomatis protokol 16-digit Lutron menjadi nilai desimal yang presisi.
- **Dark Mode UI**: Antarmuka konfigurasi modern yang nyaman di mata.

---

## 🛠️ Skema Hardware

### Komponen yang Dibutuhkan:
1. **ESP32 DevKit V1**
2. **Modul MAX3232 (RS232 to TTL)**: Wajib digunakan untuk menyesuaikan level tegangan.
3. **Jack Audio 3.5mm**: Untuk mengambil data dari port RS232 Lutron.

### Wiring Diagram:
| Lutron (Audio Jack) | Modul MAX3232 | ESP32 |
| :--- | :--- | :--- |
| **Tip (TX Data)** | Pin R1IN | - |
| **Sleeve (GND)** | Pin GND | Pin GND |
| - | Pin R1OUT (TTL Side) | **GPIO 16 (RX2)** |
| - | Pin VCC (TTL Side) | Pin 3.3V |

---

## 🚀 Panduan Instalasi

### 1. Persiapan Firmware
- Instal library **WiFiManager** (oleh tzapu) dan **ArduinoJson** (oleh Benoit Blanchon) di Arduino IDE.
- Unggah file `Lutron_IoT_Gateway.ino` ke board ESP32 kamu.

### 2. Setup Google Sheets (Penerima Data)
- Buat Google Sheets baru.
- Masuk ke **Extensions** > **Apps Script**.
- Masukkan kode `code.gs` yang tersedia di repositori ini.
- Klik **Deploy** > **New Deployment** > **Web App**.
- Atur akses ke **"Anyone"** dan salin URL yang dihasilkan.

### 3. Konfigurasi Perangkat
- Nyalakan ESP32.
- Hubungkan HP kamu ke WiFi hotspot bernama `Lutron-Gateway-AP`.
- Panel konfigurasi akan muncul secara otomatis.
- Masukkan URL Google Apps Script yang sudah disalin ke kolom **Server URL**.
- Masukkan interval pengiriman data (misal: 10 detik).
- Klik **Save**.

---

## 📊 Protokol Data (Reverse Engineering)
Berdasarkan manual Lutron Chapter 11, data dikirim dalam 16 digit stream:
- **D15**: Start Word (`4`)
- **D12-D11**: Unit ID (Contoh: `A8` untuk mW/cm²)
- **D9**: Posisi Titik Desimal (0-3)
- **D8-D1**: Nilai mentah pengukuran.
- **D0**: End Word.

---

## 👨‍💻 Kontributor
- **Anggi** - *Software Developer & IoT Engineer*

---

## 📜 Lisensi
Proyek ini dilisensikan di bawah **MIT License**.
