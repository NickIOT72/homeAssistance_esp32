# IOT Project: Home Assistance with ESP32

This project consist in the applicattion of a prototype of home automation system using ESP32 with HTTP and MQTT protocol

## How it works
    1. The system start reading the EEPROM memory. It verifies if there are WiFi
     Credentials saved. if so, the system goes to STATION MODE (), else it will go
     to AP MODE (2).
    2. On AP MODE, the system initialize the server as "ESP32_NETWORK" with the DNS
     "homeesp32.local".
    3. User must connect the device (PC or Smartphone) to this network and then on 
     browser set the the dns route. It wiil open the "WiFi Manager Page". User must
     select one of the SSIDs scanned by ESP32 , set password and press connect. After
     that, ESP32 will save the WiFi credentials and reset. It could happen 3 events:
      3.1. Connection was made succesfully, in that case blue led will stay ON and
      ESP32 starts as STATION MODE(4).
      3.2. Connection is trying to connect, so the blue led will blink 0.1 seconds
      3.3. Connection failed, so ESP32 will back to AP MODE (2)
    4. On STATION MODE, user must connect device (PC o Smartphone) to the same network
     that ESP32 is connected. After that, on browser set the same dns route, it will
     redirect to the "Dashboard Page". On this user can monitor the temperature, humidity
     and Water Tank Level, and control Lamp status and Fan Cooler speed. Additionally,
     user can view the events occurred during sessio (update of monitored parameters, 
     status changing of Lamp and Fan Cooler ).
    5. For STATION MODE, user can access to AWS stablished inside of Firmware, on over
      there control and monitor the system remotely also, without require to the 
      user to be connected to the same network as ESP32.
    6. In case the WiFi shut down or ESP32 disconnets from network, it restart the 
      system (1)

## Requirements
    1. Hardware
      * ESP32
      * DHT11 temperauture and humidity sensor (1)
      * DS18b20 temperaure sensor (1)
      * Resistance 5k (1)
      * Resistance 1k (2)
      * 2n2222 Transistor (1)
      * Fan cooler 12V (1)
      * XL6009 buck boost converter (1)

    2. Software tools
      * VS Code 
      * PlatformIO

## Circuit

## Web Pages

## Support
* [Getting Started with Amazon AWS IoT Core using ESP32 || Creating Thing, Policy & Certificates] (https://www.youtube.com/watch?v=idf-gGXvIu4)


