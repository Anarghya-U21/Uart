# Uart
UART communication:
UART stands for Universal Asynchronous Receiver-Transmitter.
These kinds of interfaces are used to achieve asynchronous serial communication between devices. The transmission speed and the data format are configurable.
There are 4 main pins that may be used on a UART interface:
    RX-the pin that will receive data from another device,
    TX-the pin that will transmit data to another device,
    RTS-request-to-send,
    CTS-clear-to-send
This project explains how 2 UARTs can communicate with each other on the same board.
Connect UART1_RXD to UART3_TXD and UART1_TXD to UART3_RXD.
Run the code to enable communication between 2 UARTS based on the Dipswitch status and also observe the baud rate changes.
This project is about controlling UARTs and setting Baud Rates using dip switch.Two UARTs are used i.e UART1 and UART3 in imx6 SBC board. In dip switch driver, in ioctl, added the controls to get the status of all the 4 dip switches in the board. Added polling function to get the status change of dip switch whenever user changes the status of the switch. Uart2_test.c is the file which contains the application code. Makefile is used to compile the application. Before compiling cross compiler should be set as export CROSS_COMPILE=/opt/poky/1.8/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/ export SDKTARGETSYSROOT=/opt/poky/1.8/sysroots/cortexa9hf-vfp-neon-poky-linux-gnueabi/. Patch file should be applied after the basic customization patch.
