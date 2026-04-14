# 📡 prowget-cloud: Universal Lutron IoT Gateway

Sistem gateway IoT berbasis **ESP32** untuk mengonlinekan instrumen profesional **Lutron SD-Series** (seperti YK-37UVSD, LX-1128SD, dll) melalui antarmuka RS232.

---

## 📂 Struktur Proyek
Sesuai dengan repositori ini, proyek dibagi menjadi beberapa bagian:
- **`/docs`**: Berisi panduan operasional standar ([SOP.md](./docs/SOP.md)).
- **`/firmware`**: Kode sumber Arduino (.ino) untuk ESP32.
- **`/hardware`**: Informasi skematik, pinout, dan kebutuhan komponen.
- **`/web-service`**: Script backend ([code.gs](./web-service/code.gs)) untuk Google Apps Script.

---

## ✨ Fitur Utama
- **Auto-Model Detection**: Mengenali otomatis jenis alat Lutron (UV Meter, Lux Meter, dll) via Unit ID.
- **WiFi Manager UI**: Konfigurasi jaringan dan server URL melalui portal web smartphone.
- **LittleFS Integration**: Penyimpanan konfigurasi aman secara lokal di ESP32.
- **Cloud Ready**: Integrasi mulus dengan Google Sheets untuk datalogging real-time.

---

## 🛠️ Koneksi Cepat (Wiring)
| Lutron (Audio Jack) | MAX3232 (RS232 Side) | ESP32 (TTL Side) |
| :--- | :--- | :--- |
| **Tip** (Signal) | Pin R1IN | - |
| **Sleeve** (GND) | Pin GND | Pin GND |
| - | Pin R1OUT | **GPIO 16 (RX2)** |

---

## 🚀 Cara Penggunaan
1. **Upload Firmware**: Flash kode di folder `/firmware` ke ESP32 kamu.
2. **Deploy Service**: Gunakan script di folder `/web-service` untuk membuat Web App di Google Sheets.
3. **Konfigurasi**: Hubungkan HP ke WiFi `Lutron-Gateway-AP`, masukkan URL dari Google Web App, lalu simpan.
4. **Monitoring**: Data akan otomatis masuk ke Google Sheets sesuai interval yang ditentukan.

> Untuk instruksi langkah-demi-langkah bagi operator, silakan merujuk pada **[Dokumen SOP](./docs/SOP.md)**.

---

## 👨‍💻 Author
- **Anggi** - *Software Developer & IoT Engineer*

---

## 📜 License
Proyek ini dilisensikan di bawah **MIT License**.
