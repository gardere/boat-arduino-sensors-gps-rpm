# Boat Dashboard - Arduino Sensors + GPS Reader


In order for our system to report the same values as displayed by the traditional analog dashboard, we have to read and process the signal reported by the existing sensors/senders.


## Possible alternative solution

A possible alternative (not explored here) could have been to replace the existing sensors with digital ones (if that even exist), but that would involve even more research, costs (some of these sensors could possibly in the hundreds if not thousands of dollars), and a lot of rewiring (I don't know about you, but I am not super keen on doing anything with the fuel tank for that matter).


## Existing senders

### Resistive sensors

The most common and simple to deal with, the senders report a different resistance depending on the value they are reporting. For instance, a typical american water temperature sender with a range from 100 to 250 Farenheit degrees would have a resistance of 450 ohms when the temp is 100F, 99 ohms when water temperature is 175F and 29.6 when it reaches 250 degrees.

Other than the water temperature, I also have resistor based senders for my fuel tank level and oil pressure.



### Tachometer

The tachometer is a bit more basic. Basically, it is a simple wire connected to the ignition coil.
Every time a spark is generated (and if you are holding this coil) you will get a shock. Well, I assume you will, because I did not really try. 
To measure the RPM of your engine, you "simply" need to count these shocks over a certain period of time, divide by the number of expected sparks per rev of your engine (for a 4 cylinders engine, it should be 4)  and extrapolate from this period to have a value per minute: for instance if you had 352 sparks over 3 seconds, the value is 352 / 4 / 3 * 60 = 1760 RPM


### Speed

When it comes to the speed, I have a small issue. Traditionally, speed on a boat is obtained a Pitot sensor. It is the same technology as used on planes, only here it is the water pressure (instead of air) that "tells" you how fast you are going. I could not easily (and cheaply) get my hands on the required component (a transducer) to get this value.
Instead I opted for a GPS module Neo6 (they go for $10). In addition to my speed, I can also now report my position and get the time (without having to add a RTC clock to my system).


## Welcome to Arduino

To read these sensors values, we are going to use an Arduino board. It is a real-time environment, able to read analog values, offer a lot of inputs and low consumption.
These values as they are read are converted to meaningful values and send over the Arduino serial bus to the other end (our Raspberry PI) for further processing and displaying.

### Resistor readings

In order to convert our resistor values to voltages (our board can only read the latter) we have to use a simple construct called a voltage dividor (See *Reading Resistive sensors* section on [this page](https://learn.sparkfun.com/tutorials/voltage-dividers/all)) and feed the ouput to our Arduino.
Because we know the values of our other resistors used in the divider, we can infer the value of our resistive sensor using a simple calcultation.
Before that, we also need to convert the Arduino analog inputs readings to actual voltage. It is a simple operation: Arduino inputs have a 10 bits resolution, that is they return a value between 0 (0V) and 1024 (5V on a 5V Arduino / 3.3V on 3.3V version).

### Tachometer

When it comes to reading the number of impulses on this wire, it gets slightly more involved than reading a resitor. Because the signal coming from the coil can be relatively high voltage, it need to be brought down to an acceptable level. To do this, we are using an opto coupler (thus isolating the high current circuit from our Arduino board) and a couple of diodes to make the (very noisy) coil signal look a bit more digital (more details on the actual circuit [here](http://blog.gardere.io/2018/05/el-taco.html)).

### GPS

To read the NMEA sentences coming out of our GPS module, we are going to use an existing Arduino library: [TinyGPS++](http://arduiniana.org/libraries/tinygpsplus/)

### Voltage



## Sending data

Every so often, the values measured are reported over serial port using a custom protocol.
Basically, we output a few dataset:
* raw readings: a string starting  with `RAW ` followed by space separated values, for instance `RAW 130 152 496 655 722`. These are our analog input values (0-1024)
* converted readings: starting with `RDG` and followed by the same values as above albeit converted to actual resistance values (but for the first value which is our voltage), for instance `RDG 12.75 27 265 1844 62160`
* GPS: string starting with `GPS` and followed by longitude, latitude, speed, course, number of satellites, hdop (GPS related value that related to the accuracy) and date/time  `GPS 151.5 -33.0 70 180 8 0 2022,12,31,14,52,21,32`
* Tachometer: a simple sentence starting with `RPM ` and followed by the current value, for instance `RPM 4900` (yep, we are flying!)