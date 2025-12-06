<div align="center">

  <!-- Banner -->
  <div style="
      width: 100%;
      padding: 45px 0;
      background: linear-gradient(135deg, #0d1b2a, #1b263b);
      border-radius: 14px;
      color: #ffffff;
      font-family: Arial, sans-serif;
  ">
      <h1 style="font-size: 40px; margin-bottom: 8px;">🔌 ESP32 → PHP API → MySQL</h1>
      <p style="font-size: 18px; opacity: 0.9;">
          IoT Data Logging System Using ESP32 with Two Sensors  
      </p>
  </div>

  <br />

  <!-- Badges -->
  <img src="https://img.shields.io/badge/ESP32-Microcontroller-blue?style=for-the-badge" />
  <img src="https://img.shields.io/badge/PHP-Backend%20API-777BB4?style=for-the-badge" />
  <img src="https://img.shields.io/badge/MySQL-Database-4479A1?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Platform-Arduino%20IDE-green?style=for-the-badge" />

</div>

<br/><br/>

<h2>📌 Project Overview</h2>
<p>
The <strong>ESP32_PHPMYSQL_2_CENSOR</strong> project demonstrates how to collect sensor data using an ESP32 
microcontroller and store it in a remote MySQL database through a PHP-based REST API.  
This project is ideal for IoT beginners, university assignments, monitoring systems, and real-time data logging applications.
</p>

<h2>🧩 System Architecture</h2>
<ul>
  <li><strong>ESP32</strong> reads data from two sensors</li>
  <li>Sends values via <strong>HTTP POST</strong> request</li>
  <li><strong>PHP API</strong> receives data, validates, and inserts into MySQL</li>
  <li><strong>MySQL database</strong> stores the sensor logs</li>
</ul>

<br/>

<h2>📡 Hardware Requirements</h2>
<ul>
  <li>ESP32 Development Board</li>
  <li>Two sensors (e.g., DHT11, DHT22, Ultrasonic, or Analog sensors)</li>
  <li>USB cable</li>
  <li>Wi-Fi connection</li>
  <li>Server with PHP + MySQL</li>
</ul>

<br/>

<h2>🛠 Software Requirements</h2>
<ul>
  <li>Arduino IDE (with ESP32 board installed)</li>
  <li>PHP 7 / 8</li>
  <li>MySQL / MariaDB</li>
  <li>Web hosting or localhost (XAMPP / Laragon)</li>
</ul>

<br/>

<h2>📥 1. Clone the Repository</h2>
<pre>
git clone https://github.com/PVegananda/ESP32_PHPMYSQL_2_CENSOR
cd ESP32_PHPMYSQL_2_CENSOR
</pre>

<br/>

<h2>🛠 2. ESP32 Arduino Setup</h2>
<p>Edit WiFi credentials and API endpoint in the ESP32 code:</p>

<pre>
// Example configuration
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

String apiUrl = "http://yourserver.com/api/insert.php";
</pre>

<p>Upload the sketch to the ESP32 using Arduino IDE.</p>

<br/>

<h2>💾 3. PHP API Setup</h2>
<p>Create a folder on your server and upload files:</p>

<pre>
/api
  ├── insert.php
  ├── db_config.php
</pre>

<p>Example <strong>insert.php</strong> structure:</p>
<pre>
<?php
include 'db_config.php';

$sensor1 = $_POST['sensor1'];
$sensor2 = $_POST['sensor2'];

$query = "INSERT INTO sensor_data(sensor1, sensor2) VALUES('$sensor1', '$sensor2')";
mysqli_query($conn, $query);

echo "OK";
?>
</pre>

<br/>

<h2>🗄 4. MySQL Database Structure</h2>

<p>Create database:</p>
<pre>CREATE DATABASE esp32_data;</pre>

<p>Create table:</p>
<pre>
CREATE TABLE sensor_data (
  id INT AUTO_INCREMENT PRIMARY KEY,
  sensor1 VARCHAR(50),
  sensor2 VARCHAR(50),
  timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
</pre>

<br/>

<h2>🌐 5. Data Flow Example</h2>
<ol>
  <li>ESP32 reads Sensor 1 & Sensor 2</li>
  <li>ESP32 sends HTTP POST → <code>insert.php</code></li>
  <li>PHP validates & inserts data into MySQL</li>
  <li>Database logs each entry with timestamp</li>
</ol>

<br/>

<h2>📊 6. Example Output</h2>
<pre>
Sensor1: 28.5°C  
Sensor2: 70.2%  
Status: Data stored successfully
</pre>

<br/>

<h2>📚 Features</h2>
<ul>
  <li>Real-time IoT data logging</li>
  <li>Simple and clean PHP API</li>
  <li>Supports any type of analog/digital sensor</li>
  <li>Optimized for low-power ESP32 devices</li>
  <li>Expandable for dashboards or mobile apps</li>
</ul>

<br/>

<h2>🔧 Troubleshooting</h2>
<ul>
  <li>⚠️ <strong>ESP32 not connecting?</strong> → Check WiFi credentials.</li>
  <li>⚠️ <strong>Database not updating?</strong> → Check API URL & file permissions.</li>
  <li>⚠️ <strong>HTTP error?</strong> → Enable CORS or check server firewall.</li>
  <li>⚠️ <strong>Slow connection?</strong> → Use lightweight hosting or VPS.</li>
</ul>

<br/>

<h2>📄 License</h2>
<p>This project is open-source and free for learning, modification, and expansion.</p>

<br/>

<div align="center">
  <h3>✨ Build Your Own IoT Monitoring System With ESP32 + PHP + MySQL</h3>
</div>
