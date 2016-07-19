# Mynewt BLE GPIO Control 

![Sample image](/images/FullSizeRender.jpg?raw=true "Android application and Mynewt application working together")

### Overview

This project uses an Android device to control the digital GPIO of nRF52dk over Bluetooth Low Energy. If you don't have an Android device, there are computer applications such as LightBlue which can mimic our Android app. 

### Setup
First, make sure you have newt installed on your computer. Here is the link to the [newt quick start guide](http://mynewt.apache.org/quick-start/) and the [Blinky project](http://mynewt.apache.org/develop/os/tutorials/nRF52/) for the nRF52dk.

I recommend doing some of the sample apps (e.g. Blinky) before diving into this project to familiarize yourself with newt tools and the core Mynewt OS.

### Clone This Project
```
git clone https://github.com/bgiori/blegpio.git
```

### Build and Run the Application
First make sure your board is plugged into your computer through a MicroUSB cable. Now build the and load the boot loader onto our nRF52dk.
```
$ newt build nrf52dk_boot 
$ newt load nrf5dk_boot
```
Next, run the blegpio app.
```
newt run blegpio 0.0.0
```
After the app builds and loads onto our device, you should see GDB start and prompt you. Whenever you initially run our app, you should always reset the board first by running the monitor reset command. After the board has been reset, we run the app using continue.
```
(gdb) monitor reset
Resetting target
(gdb) continue
Continuing.
```
**Note**: If you're having trouble connecting to the board or controlling the GPIO, your best bet is to quit gdb and reset the board.

### Wire Your LED
In order to notice the GPIO changes let's wire an LED into the board from Pin 22 and Pin 23. Use the Image below as a guide if you are new to using bread boards.

![LED Diagram](/images/gpiocontroller.png?raw=true "Sample Wired LED")

Sample LED circuit. Pins 22 and 23 wired to the positive side of LED through a resistor.

### Download the Android Application
If you have an Android device (phone or tablet) which has BLE functionality, download our Mynewt BLE GPIO Client from the Google Play Store. 

If you don't have access to an Android device but have a Mac running OSX, you can download LightBlue to use as your BLE client.

### Connect to the Board
If your app runs fine, its time to connect your Android to the board using Bluetooth LE. Start the app and chose the ble-gpio device name from the list of devices. Now you should see the GPIO control panel.

![Device Control Screen](/images/device-2016-07-19-112718.png?raw=true "Device Control Screen")

### Initialize GPIO Pins
A digital GPIO pin (labeled by number on the board) can be either an input or an output and must be initialized as such. Currently, the nRF52dk board support package does not support reinitializing GPIO so once a pin has been set it cannot be reinitialized (unless you reset the board).

To initialize a GPIO pin, press the Initialize New GPIO button and enter the desired attributes into the dialog.

![Init New GPIO](/images/device-2016-07-19-113410.png?raw=true "Initialize New GPIO Dialog")

The switch next to the direction selector serves a dual purpose based on whether you choose Input or Output:

Input
* ON: Pull-up input
* OFF: Pull-down input

Output
* ON: Initial value HIGH
* OFF: Initial value LOW

Let's initialize Pin 22, as an Output pin with a HIGH initial value. Press Initialize and you should see your LED turn on! Next initialize Pin 23 to a pull-down input and you should see the pin show up in the list with a HIGH value. 

You can toggle an output value using the switch on the right side of its list item. If you toggle Pin 22 you should also see the value of Pin 23 change after a short delay.

### Resources
The code for Android application can be found on github: https://github.com/bgiori/mynewt-ble-gpio-client-android

If you'd like to learn more about newt, Mynewt OS, or the nimBLE stack, take a look at the [Mynewt documentation](http://mynewt.apache.org/develop/os/introduction/).
