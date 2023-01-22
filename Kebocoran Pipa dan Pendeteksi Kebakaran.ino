#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


//Connection Config
#define WIFI_SSID "NAMASSID" //Nama Hostpot
#define WIFI_PASSWORD "PASSSSID" //Kosongi bila tanpa password
WiFiClient Client;

//MYSQL Config
const char* serverName = "http://nama-domain/post-esp-data.php";

//Config Ouput Buzzer dan LCD
LiquidCrystal_I2C lcd(0x27, 16,2);
const int pinbuzzer = 13;

//Config Sensor Api
const int pinapi = 12;
int nilaiapi;

//Config Sensor Air Hujan
const int pinhujan = 34;
int nilaihujan;

//Api dan String
String apiKeyValue = "tPmAT5Ab3j7F9";

//Data Sensor
String sensorName = "NAMASENSOR";
String sensorLocation = "LOKASI";

void ConnectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Menghubungkan Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("terhubung dengan WiFi IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  WiFi.disconnect();
  ConnectToWiFi();
  
  pinMode(pinapi, INPUT);
  pinMode (pinhujan, INPUT);
  pinMode(pinbuzzer, OUTPUT);

  //Set up LCD
  lcd.begin();
  lcd.setBacklight(255); // Max 
  lcd.setCursor(0,0);
  lcd.print("=Safety Kitchen=");
  lcd.setCursor(0,1);
  lcd.print("Pasyah Vegananda");
  delay(1000);
}

void baca_sensor_api() {
  nilaiapi = digitalRead(pinapi); // 0 & 1
  Serial.print("Deteksi Api: ");
  Serial.println(nilaiapi);
  Serial.println("");
}

void baca_sensor_hujan() {
  nilaihujan = analogRead(pinhujan); // mulai dari 4000
  Serial.print("Tingkat Kebocoran: ");
  Serial.println(nilaihujan);
  Serial.println("");
}

void lcd_penampil() {
lcd.clear();
if (nilaiapi == LOW) // LOW = 0 , ADA API
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("!Terdeteksi API!");
  lcd.setCursor(0,1);
  lcd.print("Pasyah Vegananda");
  digitalWrite(pinbuzzer, HIGH); // menyala
  delay(1000);
  digitalWrite(pinbuzzer, LOW); // mati
  delay(3000);
}
else if (nilaihujan <= 1000 && nilaiapi == LOW) 
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bocor & Ada Api!");
  lcd.setCursor(0,1);
  lcd.print("Pasyah Vegananda");
  digitalWrite(pinbuzzer, HIGH); // menyala
  delay(500);
  digitalWrite(pinbuzzer, LOW); // mati
  delay(1000);
}

else if (nilaihujan <= 1000) 
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Air Bocor Tipis!");
  lcd.setCursor(0,1);
  lcd.print("Pasyah Vegananda");
}

else if (nilaihujan <= 500) 
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Air Bocor Deras!");
  lcd.setCursor(0,1);
  lcd.print("Pasyah Vegananda");
}
else {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("==Kondisi Aman==");
  digitalWrite(pinbuzzer, LOW); // mati
  lcd.setCursor(0,1);
  lcd.print("Pasyah Vegananda");
  digitalWrite(pinbuzzer, LOW); // mati
}
}

void kirim_data_http() {
  
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Domain id dan path
    http.begin(client, serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                          + "&location=" + sensorLocation + "&value1=" + nilaiapi
                          + "&value2=" + nilaihujan + "";
    Serial.print("httpRequestData: ");

    
    Serial.println(httpRequestData);


    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request tiap 30 detik
  delay(20000);  

}

void loop() {
  baca_sensor_api();
  baca_sensor_hujan();
  lcd_penampil();
  kirim_data_http();
  delay(2000);
}