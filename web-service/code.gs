function doPost(e) {
  try {
    var ss = SpreadsheetApp.getActiveSpreadsheet();
    var sheet = ss.getSheets()[0];
    var data = JSON.parse(e.postData.contents);
    
    // Ambil data dari JSON yang dikirim ESP32
    var device = data.device;
    var model = data.model;
    var value = data.value;
    var unit = data.unit;
    var timestamp = new Date();
    
    // Masukkan ke baris paling bawah
    sheet.appendRow([timestamp, device, model, value, unit]);
    
    return ContentService.createTextOutput("Success").setMimeType(ContentService.MimeType.TEXT);
    
  } catch (f) {
    return ContentService.createTextOutput("Error: " + f.toString()).setMimeType(ContentService.MimeType.TEXT);
  }
}
