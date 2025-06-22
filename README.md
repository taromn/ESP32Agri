Visualize soil moisture using ESP32


![ESP32Agri1](https://github.com/user-attachments/assets/cb749c82-d3e8-4a84-b86b-1cb02b2249ce)


### How to use
**1/ create `password.h` in the same directory as `ESP32Agri.ino`**

password.h
```
#pragma once
const char* ssid = "YOUR_SSID";
const char* password = "WIFI_PASSWORD";
```

**2/ upload the 'data' directory to your ESP32.**

using `earlephilhower/arduino-littlefs-upload` might be a good option.
<br>
<br>
`earlephilhower/arduino-littlefs-upload`

https://github.com/earlephilhower/arduino-littlefs-upload/releases
<br>
<br>
**3/ write ESP32Agri.ino to your ESP32.**

<br>
<br>

### Disclaimer

The developer of this program assumes no responsibility for any problems, damages, or disadvantages that may occur as a result of the use, execution, or reference of any content (including but not limited to code, documentation, instructions, and all other files) contained within this repository.

