# Setting

1. Connect Network

Input your network SSID and Password

```c
const char *ssid = "";     // input SSID here
const char *password = ""; // input Password here
```

2. Connect Ambient for visualization

[https://ambidata.io/ch/channels.html](https://ambidata.io/ch/channels.html)

Make private Ambient channel

<img src="https://github.com/mono0423/futon-public/blob/master/readme/1.png" width="600">

Input Channel ID and Write Key

<img src="https://github.com/mono0423/futon-public/blob/master/readme/2.png" width="600">

```c
const unsigned int channelId = 0; // input Ambient channel ID here
const char *writeKey = "";        // input Ambient writeKey here
```
