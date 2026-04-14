# Universal Lutron IoT Gateway (ESP32)

Project ini mengonversi alat ukur profesional Lutron seri SD Card (seperti YK-37UVSD) menjadi perangkat IoT yang dapat mengirim data real-time ke internet.

## 🛠 Hardware Specifications
- **Controller:** ESP32 (DevKit V1).
- **Interface:** RS232 to TTL (MAX3232).
- **Connector:** 3.5 mm Audio Jack.
- **Protocol:** RS232, 9600 bps, 8-N-1.

## 📡 Features
- **Auto-Model Detection**: Secara otomatis mengenali model Lutron berdasarkan unit data stream (D12/D11).
- **Dual Display Support**: Membaca data utama (UV/Light) dan data tambahan (Type K/J Temp) secara bersamaan.
- **WiFi Web Portal**: Konfigurasi SSID, Password, dan Endpoint Server tanpa flash ulang.
- **Data Persistence**: Menggunakan LittleFS untuk menyimpan konfigurasi.

## 🔍 Data Stream Structure (16 Digits)
Berdasarkan manual YK-37UVSD:
- `D15`: Start Word (`4`)
- `D13`: Display Source (`1` = Main, `2` = Temp)
- `D12-D11`: Unit ID (`A8` = mW/cm²)
- `D9`: Decimal Point position
- `D8-D1`: Measured Value
- `D0`: End Word

## 🚀 Setup
1. Hubungkan Pin TX Lutron (Tip Jack 3.5mm) ke RX Modul MAX3232.
2. Hubungkan Output TTL MAX3232 ke GPIO 16 (RX2) ESP32.
3. Nyalakan ESP32, konek ke WiFi `Lutron-Gateway-AP`.
4. Masukkan URL Server (Google Sheets/REST API) pada panel konfigurasi.
