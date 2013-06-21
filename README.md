WorkerB
=======

This is my latest project, the “Worker Bee”. It is an ATMega32U4-based Arduino compatible board running at 8Mhz, 
specially designed for low-power battery operation. There is a slot on the board to fit a 2.4Ghz nRF24L01 breakout 
module (not included, optional); Power to that slot is controlled via a MOSFET, so that the MCU is in control and 
can power the nRF24L01 whenever/if necessary and save power.

The board can be powered via a single AAA battery using an optional LTC3525 boost regulator, a CR2032 battery or 
any other 2.6-5.5V source (via the on-board MCP1700 for voltages >3.3V or directly at the VCC in)


http://harizanov.com/product/workerb/
