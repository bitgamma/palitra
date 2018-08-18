# Palette

Palette is a simple USB device which is thought to be placed on the side of a graphic tablet while doing image editing in order to have easy access to the most frequently used shortcuts. Of course it can be used in other contexts as well.

The project is based around a PIC18F14K50 chip because it supports USB (using an external crystal) and can be powered from 5v without external components. I also had a couple of them lying around, which made the choice obvious.

There is currently one prototype built on veroboard, but the device can be made much smaller with a custom PCB design.

## TODO

1) Make a cross-platform program to configure the device (Java + libusb?)
2) Design product apperance, special care must be taken to make the buttons pleasant to use
3) Draw schematics
4) Draw PCB
5) Measure and improve power usage
6) Manufacturing
