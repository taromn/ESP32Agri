## *Visualize soil moisture using ESP32*

### Architecture

`Soil Moisture Sensor` -- `ESP32` <--(Local Network)-- `Prometheus` on Docker 
<br>
<br>

### Key Features

- **Reads soil mositure** (analogPin, 32) and blinks Red or Blue depending on the analog value 
```
const int analogPin = 32;  // sensor pin
const int drypin = 25;  // LED pin that blinks when soil is dry
const int moistpin = 26;  // LED pin that blinks when soil is moist
```

- ESP32 **provides web UI** `http://<IP address of ESP32>/status`, where you can check the current status of the soil

<p align="center">
<img src="https://github.com/user-attachments/assets/cb749c82-d3e8-4a84-b86b-1cb02b2249ce" alt="ESP32Agri_status" width="70%">
</p>

- ESP32 exposes **Prometheus metrics** via its own http server. 
- (Optionally) you can **spin up a Prometheus container** on your laptop to monitor ESP32.

### How to use
#### 1/ get your own ESP32. change pin numbers if needed

In `ESP32Agri.ino`:
```
// if needed, change these pins to your own pin numbers
const int analogPin = 32;  // sensor pin
const int drypin = 25;  // LED pin that blinks when soil is dry
const int moistpin = 26;  // LED pin that blinks when soil is moist
```

#### 2/ Create `password.h` in the same directory as `ESP32Agri.ino`

password.h
```
#pragma once
const char* ssid = "YOUR_SSID";
const char* password = "WIFI_PASSWORD";
```

Do not include `password.h` in your commit. (basically, `password.h` should be ignored by .gitignore)
<br>
<br>
#### 3/ Upload the `data` directory to your ESP32.

Using `earlephilhower/arduino-littlefs-upload` might be a good option.
<br>
<br>
`earlephilhower/arduino-littlefs-upload`

https://github.com/earlephilhower/arduino-littlefs-upload/releases
<br>
<br>
#### 4/ Write `ESP32Agri.ino` to your ESP32.

You can see the status page on `http://<IP address of ESP32>/status`



#### 5/ (Optional) Spin up a Promethus container on your laptop.

Prepare a laptop that is connected to the same network as ESP32.

Set the IP address of ESP32 in `prometheus/prometheus.yml`
```
      - targets: ['<ip_address>:80']
        labels:
          group: 'dev'
```

then

```
docker compose up -d
```

<br>
<br>

As a result, you can see soil moisture metrics on `http://localhost:9090`

### Disclaimer

The developer of this program assumes no responsibility for any problems, damages, or disadvantages that may occur as a result of the use, execution, or reference of any content (including but not limited to code, documentation, instructions, and all other files) contained within this repository.

