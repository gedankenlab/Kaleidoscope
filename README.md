# Kaleidoglyph

Flexible firmware for Arduino-powered keyboards.

This package contains the "core" of Kaleidoglyph and an [example firmware "Sketch."](https://github.com/keyboardio/Kaleidoglyph/blob/master/examples/Kaleidoglyph/Kaleidoglyph.ino)

If you're just getting started with the Keyboardio Model 01, the [introductory docs are here](https://github.com/keyboardio/Kaleidoglyph/wiki/Keyboardio-Model-01-Introduction) and the source for the basic firmware package is here: https://github.com/keyboardio/Model01-Firmware. It's probably a good idea to start there, learn how to modify your keymap and maybe turn some modules on or off, and then come back to the full repository when you have more complex changes in mind.

# Getting Started

Pick a directory to work in, you'll need to clone multiple repositories. We'll assume you picked `$HOME/kaleidoglyph`, if you chose another adapt the commands below accordingly.

## Setup the Arduino IDE

Setup the Arduino IDE on your system. Make sure you install at least version 1.6, since older version may not support all required features.

* On Linux, follow the instructions [on the wiki](https://github.com/keyboardio/Kaleidoglyph/wiki/Install-Arduino-support-on-Linux).
* On macOS, install using [homebrew](http://brew.sh/) [cask](https://caskroom.github.io/) with `brew cask install arduino` or download the application from [the official website](https://www.arduino.cc/en/Main/Software) and move it to your `/Applications` folder.

## Install the Kaleidoglyph Hardware Definitions

```sh
# you'll need to know your arduino sketchbook directory

# on macOS the default is
SKETCHBOOK_DIR=$HOME/Documents/Arduino
# on Linux the default is
SKETCHBOOK_DIR=$HOME/Arduino

# go to your kaleidoglyph directory
cd $HOME/kaleidoglyph
# then clone the hardware definitions
git clone --recursive https://github.com/keyboardio/Arduino-Boards.git
# and make them available to the arduino environment
mkdir -p $SKETCHBOOK_DIR/hardware/keyboardio
ln -s $HOME/kaleidoglyph/Arduino-Boards $SKETCHBOOK_DIR/hardware/keyboardio/avr
```

## Clone and Build the Kaleidoglyph Firmware

```sh
# go to your keyboardio directory
cd $HOME/kaleidoglyph
# then clone the firmware repository
git clone https://github.com/keyboardio/Kaleidoglyph.git
# and build your firmware!
cd Kaleidoglyph
make
```

<3 jesse

[![Build
Status](https://travis-ci.org/keyboardio/Kaleidoglyph.svg?branch=master)](https://travis-ci.org/keyboardio/Kaleidoglyph)
