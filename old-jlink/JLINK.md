# Instructions for JLINK Configuration
(Dismissed, not valid with latest version of tool-jlink package)

## 1. Add AT .FLM Files
Copy the `.platformio\packages\tool-jlink\Devices\AT\AT32F4xx` folder from Github here to your .platformio folder.

## 2. AT MCU Configurations
Add the following lines to the `JLinkDevices.xml` file under `.platformio/packages/tool-jlink/`

```
 <!--    -->
  <!-- AT32 -->
  <!--    -->
  <!-- AT32F403 -->
  <Device>
   <ChipInfo Vendor="AT" Name="AT32F403AxCx" WorkRAMAddr="0x20000000" WorkRAMSize="0x38000" Core="JLINK_CORE_CORTEX_M4" />
   <FlashBankInfo Name="QSPI Flash" BaseAddr="0x08000000" MaxSize="0x040000" Loader="Devices/AT/AT32F4xx/AT32F403A_256.FLM" LoaderType="FLASH_ALGO_TYPE_CMSIS" />
  </Device>  
  <Device>
   <ChipInfo Vendor="AT" Name="AT32F403AxEx" WorkRAMAddr="0x20000000" WorkRAMSize="0x38000" Core="JLINK_CORE_CORTEX_M4" />
   <FlashBankInfo Name="QSPI Flash" BaseAddr="0x08000000" MaxSize="0x080000" Loader="Devices/AT/AT32F4xx/AT32F403A_512.FLM" LoaderType="FLASH_ALGO_TYPE_CMSIS" />
  </Device>  
  <Device>
   <ChipInfo Vendor="AT" Name="AT32F403AxGx" WorkRAMAddr="0x20000000" WorkRAMSize="0x38000" Core="JLINK_CORE_CORTEX_M4" />
   <FlashBankInfo Name="QSPI Flash" BaseAddr="0x08000000" MaxSize="0x100000" Loader="Devices/AT/AT32F4xx/AT32F403A_1024.FLM" LoaderType="FLASH_ALGO_TYPE_CMSIS" />
  </Device>  
  <!-- AT32F435 -->
  <Device>
   <ChipInfo Vendor="AT" Name="AT32F435xCx" WorkRAMAddr="0x20000000" WorkRAMSize="0x80000" Core="JLINK_CORE_CORTEX_M4" />
   <FlashBankInfo Name="QSPI Flash" BaseAddr="0x08000000" MaxSize="0x040000" Loader="Devices/AT/AT32F4xx/AT32F435_256.FLM" LoaderType="FLASH_ALGO_TYPE_CMSIS" />
  </Device>  
  <Device>
   <ChipInfo Vendor="AT" Name="AT32F435xGx" WorkRAMAddr="0x20000000" WorkRAMSize="0x80000" Core="JLINK_CORE_CORTEX_M4" />
   <FlashBankInfo Name="QSPI Flash" BaseAddr="0x08000000" MaxSize="0x100000" Loader="Devices/AT/AT32F4xx/AT32F435_1024.FLM" LoaderType="FLASH_ALGO_TYPE_CMSIS" />
  </Device>  
  <Device>
   <ChipInfo Vendor="AT" Name="AT32F435xMx" WorkRAMAddr="0x20000000" WorkRAMSize="0x80000" Core="JLINK_CORE_CORTEX_M4" />
   <FlashBankInfo Name="QSPI Flash" BaseAddr="0x08000000" MaxSize="0x400000" Loader="Devices/AT/AT32F4xx/AT32F435_4032.FLM" LoaderType="FLASH_ALGO_TYPE_CMSIS" />
  </Device> 
  <!-- AT32F425 -->
  <Device>
   <ChipInfo Vendor="AT" Name="AT32F425x6x" WorkRAMAddr="0x20000000" WorkRAMSize="0x05000" Core="JLINK_CORE_CORTEX_M4" />
   <FlashBankInfo Name="QSPI Flash" BaseAddr="0x08000000" MaxSize="0x008000" Loader="Devices/AT/AT32F4xx/AT32F425_32.FLM" LoaderType="FLASH_ALGO_TYPE_CMSIS" />
  </Device>     
  <Device>
   <ChipInfo Vendor="AT" Name="AT32F425x8x" WorkRAMAddr="0x20000000" WorkRAMSize="0x05000" Core="JLINK_CORE_CORTEX_M4" />
   <FlashBankInfo Name="QSPI Flash" BaseAddr="0x08000000" MaxSize="0x010000" Loader="Devices/AT/AT32F4xx/AT32F425_64.FLM" LoaderType="FLASH_ALGO_TYPE_CMSIS" />
  </Device>  
```

## 3. Use JLINK upload in the Project
In the `platformio.ini` file in the Project folder, use this configuration line:
```
upload_protocol = jlink
```

# How to Configure JLINK for a new Board
To configure a new board use the `.json` template file from another AT32 board, then in the `debug` section you can configure the `jlink_device` as one of the followings:

```
AT32F403AxCx, AT32F403AxEx, AT32F403AxGx
AT32F435xCx, AT32F435xGx, AT32F435xMx
```
Example:
```
...
 "debug": {
    "default_tools": [
      "stlink"
    ],
    "jlink_device": "AT32F435xGx",
    "openocd_extra_args": [
      "-c",
      "reset_config none"
    ],
    "openocd_target": "stm32f4x",
    "svd_path": "STM32F435xx.svd"
  },
...
```