# Robotlabb
Sumorobot Labb


## Utvecklingsmiljö

### Atom + PlatformIO
  * Installera atom https://atom.io/.  
  * Installera plugin platformio-ide https://github.com/platformio/platformio-atom-ide
  * Kör atom i ett projekt.  
	    cd targetting_robot
			atom .	

### Arduino IDE

Hämta Arduino IDE genom nedladdningslänk: https://www.arduino.cc/download_handler.php?f=/arduino-1.8.2-linux64.tar.xz.

	tar xvfJ arduino-1.8.2-linux64.tar.xz

	cd arduino-1.8.2
	./install.sh

#### Teensy

	wget https://www.pjrc.com/teensy/td_136/TeensyduinoInstall.linux64
	wget https://www.pjrc.com/teensy/49-teensy.rules

	sudo cp 49-teensy.rules /etc/udev/rules.d/
	chmod 755 TeensyduinoInstall.linux64
	./TeensyduinoInstall.linux64

### Möjliggör bygge från kommandoraden

Från http://hardwarefun.com/tutorials/compiling-arduino-sketches-using-makefile

	git clone https://github.com/sudar/Arduino-Makefile

	sudo apt-get install libdevice-serialport-perl
	sudo apt-get install libyaml-perl

Lägg in i `~/.bashrc`:

	bexport ARDUINO_DIR=`cd ~/dev/arduino-1.8.2; pwd`
	export ARDMK_DIR=`cd ~/dev/Arduino-Makefile; pwd`
	export AVR_TOOLS_DIR=`cd ~/dev/arduino-1.8.2/hardware/tools/avr; pwd`


### Emacs

Addera melpa arkivet:

	(add-to-list 'package-archives
		'("melpa" . "https://melpa.org/packages/"))

Installera arduino-mode från melpa.

Använd normala byggkommandon (`M-x compile`) för att bygga från den Makefile som ligger i projektet.
