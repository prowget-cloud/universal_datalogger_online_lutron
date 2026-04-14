#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

// --- Konfigurasi Pin ---
#define RXD2 16  // Hubungkan ke pin R1OUT Modul MAX3232
#define TXD2 17  // (Tidak dipakai, tapi didefinisikan untuk Serial2)

// --- Variabel Global ---
char server_url[150] = "https://script.google.com/macros/s/XXXX/exec";
char device_name[30] = "Lutron-Gateway-01";
char log_interval[10] = "10"; // Dalam detik
bool shouldSaveConfig = false;

// Struktur Data Lutron
struct LutronData {
  String model;
  float value;
  String unit;
  bool isValid;
};

// Callback untuk WiFiManager jika ada setting yang diubah
void saveConfigCallback() {
  Serial.println("Konfigurasi baru diterima...");
  shouldSaveConfig = true;
}

// ==========================================
// 1. FUNGSI PARSING LUTRON (CHAPTER 11)
// ==========================================
LutronData parseLutron(char* stream) {
  LutronData data;
  data.isValid = false;

  // D15 harus '4' (Start Word)
  if (stream[0] != '4') return data;

  // Parsing Angka (D8 ke D1)
  // Stream index di array (0-15) terbalik dengan penamaan D15-D0
  // D15=0, D14=1, ..., D8=7, D1=14, D0=15
  char digits[9];
  for (int i = 0; i < 8; i++) {
    digits[i] = stream[7 + i]; // Mengambil D8 sampai D1
  }
  digits[8] = '\0';
  float val = atof(digits);

  // Parsing Titik Desimal (D9 ada di index 6)
  int dp = stream[6] - '0';
  if (dp == 1) val /= 10.0;
  else if (dp == 2) val /= 100.0;
  else if (dp == 3) val /= 1000.0;
  data.value = val;

  // Parsing Unit & Model (D12=index 3, D11=index 4)
  char d12 = stream[3];
  char d11 = stream[4];

  if (d12 == 'A' && d11 == '8') {
    data.model = "YK-37UVSD";
    data.unit = "mW/cm2";
  } else if (d12 == '0' && (d11 == '1' || d11 == '2')) {
    data.model = "Lutron Thermometer";
    data.unit = (d11 == '1') ? "Celsius" : "Fahrenheit";
  } else {
    data.model = "Lutron Universal";
    data.unit = "Unknown";
  }

  data.isValid = true;
  return data;
}

// ==========================================
// 2. SETUP & CONFIGURATION
// ==========================================
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Mount LittleFS
  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS Mount Failed");
  }

  // Load existing config
  if (LittleFS.exists("/config.json")) {
    File configFile = LittleFS.open("/config.json", "r");
    if (configFile) {
      StaticJsonDocument<512> doc;
      deserializeJson(doc, configFile);
      strcpy(server_url, doc["server_url"]);
      strcpy(device_name, doc["device_name"]);
      strcpy(log_interval, doc["log_interval"]);
    }
  }

  // WiFiManager Setup
  WiFiManager wm;
  wm.setSaveConfigCallback(saveConfigCallback);
  wm.setClass("invert"); // Dark Mode UI

  WiFiManagerParameter custom_server("server", "Server URL", server_url, 150);
  WiFiManagerParameter custom_devname("name", "Device ID", device_name, 30);
  WiFiManagerParameter custom_interval("int", "Interval (sec)", log_interval, 10);

  wm.addParameter(&custom_server);
  wm.addParameter(&custom_devname);
  wm.addParameter(&custom_interval);

  if (!wm.autoConnect("Lutron-Gateway-AP")) {
    Serial.println("Gagal koneksi WiFi");
    delay(3000);
    ESP.restart();
  }

  // Save config if changed
  if (shouldSaveConfig) {
    strcpy(server_url, custom_server.getValue());
    strcpy(device_name, custom_devname.getValue());
    strcpy(log_interval, custom_interval.getValue());

    File configFile = LittleFS.open("/config.json", "w");
    StaticJsonDocument<512> doc;
    doc["server_url"] = server_url;
    doc["device_name"] = device_name;
    doc["log_interval"] = log_interval;
    serializeJson(doc, configFile);
    configFile.close();
  }

  Serial.println("Gateway Online & Ready!");
}

// ==========================================
// 3. MAIN LOOP & DATA HANDLING
// ==========================================
unsigned long lastLog = 0;
char serialBuf[17];
int bufIdx = 0;

void loop() {
  // Membaca stream 16 digit dari Serial2
  if (Serial2.available()) {
    char c = Serial2.read();

    // Cari Start Word '4' (D15)
    if (c == '4' && bufIdx == 0) {
      serialBuf[bufIdx++] = c;
    } else if (bufIdx > 0) {
      serialBuf[bufIdx++] = c;
    }

    // Jika 16 digit terkumpul
    if (bufIdx == 16) {
      serialBuf[16] = '\0';
      LutronData res = parseLutron(serialBuf);
      bufIdx = 0; // Reset buffer

      // Kirim data berdasarkan interval
      unsigned long currentMillis = millis();
      int intervalInt = atoi(log_interval);
      if (res.isValid && (currentMillis - lastLog >= (intervalInt * 1000))) {
        sendToCloud(res);
        lastLog = currentMillis;
      }
    }
  }
}

void sendToCloud(LutronData d) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(server_url);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<256> jsonDoc;
    jsonDoc["device"] = device_name;
    jsonDoc["model"] = d.model;
    jsonDoc["value"] = d.value;
    jsonDoc["unit"] = d.unit;

    String payload;
    serializeJson(jsonDoc, payload);

    int httpCode = http.POST(payload);
    Serial.print("Data dikirim. HTTP Code: ");
    Serial.println(httpCode);
    
    http.end();
  }
}
