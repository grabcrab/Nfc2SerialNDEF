esptool.exe --port COM39 --baud 921600 write_flash 0x00000000 bootloader.bin
esptool.exe --port COM39 --baud 921600 write_flash 0x00008000  partitions.bin
esptool.exe --port COM39 --baud 921600 write_flash 0x00010000 firmware.bin
pause
