# UART communication

## INTRODUCTION
* UART stands for Universal Asynchronous Receiver-Transmitter.
* These kinds of interfaces are used to achieve asynchronous serial communication between devices. 
* The transmission speed and the data format are configurable.
* There are 4 main pins that may be used on a UART interface:
    1. RX-the pin that will receive data from another device,
    2. TX-the pin that will transmit data to another device,
    3. RTS-request-to-send,
    4. CTS-clear-to-send
* This project is about controlling UARTs and setting Baud Rates using dip switch.Two UARTs are used i.e UART1 and UART3 in imx6 SBC board. 
* Uart2_test.c is the file which contains the application code.
* Makefile is used to compile the application.
* Patch file is provided to apply the changes made to the dip switch driver.
* In dip switch driver, in ioctl, added the controls to get the status of all the 4 dip switches in the board. 
* Added polling function to get the status change of dip switch whenever user changes the status of the switch.
* This project explains how 2 UARTs can communicate with each other on the same board.
* Connect UART1_RXD to UART3_TXD and UART1_TXD to UART3_RXD.
* Run the code to enable communication between 2 UARTS based on the Dipswitch status and also observe the baud rate changes.

### REQUIREMENTS
* Before compiling the application using Makefile, cross compiler should be set as export CROSS_COMPILE=/opt/poky/1.8/sysroots/-pokysdk-linux/usr/bin/arm-poky-    
  linux-gnueabi/ export SDKTARGETSYSROOT=/opt/poky/1.8/sysroots/cortexa9hf-vfp-neon-poky-linux-gnueabi/
* Patch file for the dip switch driver should be applied after the basic customization patch

### INSTALLATIONS
* Cross compiler should be set up in /opt/poky.


