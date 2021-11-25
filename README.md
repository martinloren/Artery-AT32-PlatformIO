# Artery-AT32-PlatformIO
 PlatformIO platform and framework for Artery AT32 MCU

Released specifically for latest MCU AT32F403A with Visual Studio Code & PlatformIO.

## Instructions
1) Copy the folders under .platformio in your .platformio folder (ie: C:\Users\(username)\.platformio)
2) Open Visual Studio Code, you should see AT32 Platform among the available platforms
3) Open one of the example folder and try to compile / upload

# Upload on MCU
1) For now it is implemented a custom bootloader based on serial bootloader
2) Set the serial port in the file platformio.ini in the project folder
3) Run the Upload


# AT32F403A on Bluepill PCB
You can replace the MCU on the Bluepilll board with the AT32F403A. It is pin fully compatible.
Just need to replace BOOT0 resistor from the present value of 100K with the value of 10K. This will allow the MCU to enter in Bootloader mode and flash it via UART1.