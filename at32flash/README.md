# at32flash
Flash program for AT32 using the AT serial bootloader, based on [stm32flash](https://github.com/stm32duino/stm32flash).

at32flash 0.1 is a release with these highlights:
- Support for **AT32F435** beside the STM32 MCUs

## Features
UART and I2C transports supported
device identification
write to flash/ram
read from flash/ram
auto-detect Intel HEX or raw binary input format with option to force binary
flash from binary file
save flash to binary file
verify & retry up to N times on failed writes
start execution at specified address
software reset the device when finished if -R is specified
resume already initialized connection (for when reset fails, UART only)
GPIO signalling to enter bootloader mode (hardware dependent)


## Usage synopsis:
```
Usage: ./at32flash [-bvngfhc] [-[rw] filename] [tty_device | i2c_device]
    -a bus_address  Bus address (e.g. for I2C port)
    -b rate     Baud rate (default 57600)
    -m mode     Serial port mode (default 8e1)
    -r filename Read flash to file (or - stdout)
    -w filename Write flash from file (or - stdout)
    -C      Compute CRC of flash content
    -u      Disable the flash write-protection
    -j      Enable the flash read-protection
    -k      Disable the flash read-protection
    -o      Erase only
    -e n        Only erase n pages before writing the flash
    -v      Verify writes
    -n count    Retry failed writes up to count times (default 10)
    -g address  Start execution at specified address (0 = flash start)
    -S address[:length] Specify start address and optionally length for
                        read/write/erase operations
    -F RX_length[:TX_length]  Specify the max length of RX and TX frame
    -s start_page   Flash at specified page (0 = flash start)
    -f      Force binary parser
    -h      Show this help
    -c      Resume the connection (don't send initial INIT)
            *Baud rate must be kept the same as the first init*
            This is useful if the reset fails
    -R      Reset device at exit.
    -i GPIO_string  GPIO sequence to enter/exit bootloader mode
            GPIO_string=[entry_seq][:[exit_seq]]
            sequence=[[-]signal]&|,[sequence]
```

## GPIO sequence:
    The following signals can appear in a sequence:
      Integer number representing GPIO pin
      'dtr', 'rts' or 'brk' representing serial port signal
    The sequence can use the following delimiters:
      ',' adds 100 ms delay between signals
      '&' adds no delay between signals
    The following modifiers can be prepended to a signal:
      '-' reset signal (low) instead of setting it (high)

## Examples:
```
    Get device information:
        ./at32flash /dev/ttyS0
      or:
        ./at32flash /dev/i2c-0

    Write with verify and then start execution:
        ./at32flash -w filename -v -g 0x0 /dev/ttyS0

    Read flash to file:
        ./at32flash -r filename /dev/ttyS0

    Read 100 bytes of flash from 0x1000 to stdout:
        ./at32flash -r - -S 0x1000:100 /dev/ttyS0

    Start execution:
        ./at32flash -g 0x0 /dev/ttyS0

    GPIO sequence:
    - entry sequence: GPIO_3=low, GPIO_2=low, 100ms delay, GPIO_2=high
    - exit sequence: GPIO_3=high, GPIO_2=low, 300ms delay, GPIO_2=high
        ./at32flash -i '-3&-2,2:3&-2,,,2' /dev/ttyS0
    GPIO sequence adding delay after port opening:
    - entry sequence: delay 500ms
    - exit sequence: rts=high, dtr=low, 300ms delay, GPIO_2=high
        ./at32flash -R -i ',,,,,:rts&-dtr,,,2' /dev/ttyS0
```

## Bug reports and patches
Please file bugs and post patches here in GitHub.
