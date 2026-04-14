# Standard Operating Procedure (SOP)
## Universal Lutron IoT Gateway System

Dokumen ini menjelaskan langkah-langkah standar untuk instalasi, konfigurasi, dan pengoperasian Gateway IoT untuk perangkat Lutron SD-Series.

---

## 1. Persiapan Perangkat (Pre-Operating)
Sebelum memulai, pastikan seluruh komponen berikut tersedia:
- **Unit Lutron** (Contoh: YK-37UVSD) dalam kondisi daya optimal.
- **Sensor Probe** yang sesuai (UVA/UVC/Thermocouple).
- **Unit Gateway ESP32** beserta kabel Jack Audio 3.5mm.
- **Power Source** (Power bank atau adaptor USB 5V 1A).

### Koneksi Hardware:
1. Pasang probe sensor ke socket input Lutron.
2. Hubungkan Jack Audio 3.5mm ke port **RS-232 Output** pada Lutron.
3. Hubungkan sisi lain kabel ke port input pada Gateway ESP32.
4. Hubungkan ESP32 ke sumber daya USB.

---

## 2. Konfigurasi Jaringan & Server (WiFi Setup)
Langkah ini wajib dilakukan jika perangkat berpindah lokasi atau URL server berubah.

1. Nyalakan Gateway ESP32.
2. Cari jaringan WiFi bernama **`Lutron-Gateway-AP`** melalui Smartphone/Laptop.
3. Hubungkan ke jaringan tersebut (tanpa password).
4. Browser akan otomatis membuka panel konfigurasi (atau akses `192.168.4.1`).
5. **Isi Parameter Berikut:**
   - **SSID & Password**: Informasi WiFi lokal yang memiliki akses internet.
   - **Server URL**: URL dari Google Apps Script (Deployment URL).
   - **Device ID**: Nama unik alat (Contoh: `LAB-UV-01`).
   - **Interval**: Durasi jeda pengiriman data (dalam detik).
6. Klik **Save**. Gateway akan restart dan mencoba terhubung ke internet.

---

## 3. Prosedur Pengoperasian (Operating)
1. Nyalakan unit Lutron dengan menekan tombol **Power**.
2. Pilih mode pengukuran (UVA/UVC) dengan menekan tombol **Function** sesuai kebutuhan.
3. **Zeroing**: Tutup sensor, lalu tekan tombol **Zero** pada Lutron selama 3 detik hingga layar menunjukkan angka `0`.
4. Buka sensor dan arahkan ke objek yang diukur.
5. Gateway akan membaca data serial secara otomatis dan mengirimkannya ke cloud setiap interval yang ditentukan.

> **Catatan:** Pastikan fitur "Hold" pada Lutron **tidak aktif** agar data yang dikirimkan tetap real-time.

---

## 4. Pemantauan Data (Monitoring)
1. Buka file **Google Sheets** yang sudah dihubungkan.
2. Periksa apakah data baru masuk pada baris paling bawah.
3. Pastikan kolom **Timestamp, Device ID, Value, dan Unit** terisi dengan benar.

---

## 5. Troubleshooting
| Masalah | Penyebab Umum | Tindakan |
| :--- | :--- | :--- |
| Data di Sheet tidak update | Koneksi internet terputus | Cek sinyal WiFi atau kuota internet di lokasi. |
| Nilai selalu "0.00" | Kabel RS232 longgar | Pastikan Jack 3.5mm terpasang sempurna. |
| Tidak bisa akses WiFi Portal | ESP32 terhubung ke WiFi lama | Reset ESP32 menggunakan tombol fisik di board. |
| Unit terdeteksi "Unknown" | Protokol tidak dikenali | Pastikan baud rate Lutron di-set ke 9600 (default). |

---

## 6. Pemeliharaan & Keamanan
- Hindari menarik kabel Jack secara kasar.
- Simpan unit di tempat kering untuk menghindari korosi pada pin RS232.
- Cabut daya dari Gateway jika tidak digunakan dalam waktu lama.
