## *Visualize soil moisture using ESP32*

### Architecture

`Soil Moisture Sensor` -- `ESP32` <--(Local Network)-- `Prometheus` on Docker 
<br>
<br>
### How to use
#### 1/ Create `password.h` in the same directory as `ESP32Agri.ino`

password.h
```
#pragma once
const char* ssid = "YOUR_SSID";
const char* password = "WIFI_PASSWORD";
```

Do not include `password.h` in your commit. (basically, `password.h` should be ignored by .gitignore)
<br>
<br>
#### 2/ Upload the `data` directory to your ESP32.

Using `earlephilhower/arduino-littlefs-upload` might be a good option.
<br>
<br>
`earlephilhower/arduino-littlefs-upload`

https://github.com/earlephilhower/arduino-littlefs-upload/releases
<br>
<br>
#### 3/ Write `ESP32Agri.ino` to your ESP32.

You can see the status page on `http://<IP address of ESP32>/status`


![ESP32Agri1](https://github.com/user-attachments/assets/cb749c82-d3e8-4a84-b86b-1cb02b2249ce)

#### 4/ (Optional) Spin up a Promethus container on your laptop.

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

