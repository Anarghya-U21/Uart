# Uart
UART communication:
UART stands for Universal Asynchronous Receiver-Transmitter.
These kinds of interfaces are used to achieve asynchronous serial communication between devices. The transmission speed and the data format are configurable.
There are 4 main pins that may be used on a UART interface:
    RX, the pin that will receive data from another device
    TX, the pin that will transmit data to another device
    RTS, request-to-send
    CTS, clear-to-send
This project explains how 2 UARTs can communicate with each other on the same board
Connect UART1_RXD to UART3_TXD and UART1_TXD to UART3_RXD.
Run the code to enable communication between 2 UARTS based on the Dipswitch status and also observe the baud rate changes.
