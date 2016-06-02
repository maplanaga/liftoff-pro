Warrning: I returned my LP Pro, so unless I buy another one at some point this project can be considered abandoned. Maybe check out [what others are doing with the custom firmware](https://github.com/dvhdr/launchpad-pro/network). [This one](https://github.com/jrcurtis/subsequencely) looks great.

# Liftoff Pro

Custom firmware for Launchpad Pro controller that aims to enable a nice standalone workflow, similar to how the device works with Ableton Live.

It has the following features:

## Working:

- isomorphic "in key" scale keyboard: not completed but already fun to use. Right now poly aftertouch is always on.

## Partial:

- session mode: play, create and select clips (that don't really do much other than store scale settings yet)
- quick mute / solo / volume etc: The UI is there but it doesn't do anything.
- clock: the 'click' button blinks with the internal clock pulse, super useful right?

## Planned:

- Drum / Melodic / CC Sequencer: We'll see how viable this is with the limited memory on the device.
- User / Programmer Mode: Would be nice if you could still use external apps with the Launchpad while this firmware is installed
- Custom Scales
- Chromatic Keyboard Mode
- Live Recording
- Clip Operations: delete, duplicate, double lenght etc
- tap tempo, sync to external, set tempo manually
- Documentation: I'm literally the worst

# Getting Started

A compiled .syx version can be found in the release folder. Skip to 'Uploading to a Launchpad Pro' to find out how to install it.

This repository includes the stuff needed to build the firmware from [https://github.com/dvhdr/launchpad-pro](https://github.com/dvhdr/launchpad-pro). The instructions below are taken from the original release.

# Installation
This project uses [Vagrant](https://www.vagrantup.com/) to manage the build environment. As such, you need to:

1. Clone this repository on your host computer (if using the command line, make sure you `git clone --recursive`).
2. Install [Vagrant](https://www.vagrantup.com/)
3. Install [VirtualBox](https://www.virtualbox.org/wiki/Downloads)
4. Open a command prompt, and navigate to the project directory
5. Type `vagrant up`, hit enter and grab a beverage of your choice.  Maybe two - it is building a lovely fresh development machine just for you!

If you have a poor internet connection, ummm, find a better one :)

# Building
Once your new "box" is up and running, you can build the app in one of two ways.  In the spirit of experimentation, we've created a full Eclipse development environment for you to use.  However, you might prefer to do things on the command line.

#  To use the command line interface:
1. SSH into the Vagrant "box" by doing `vagrant ssh`
2. At the command prompt, simply type `make`

# Uploading to a Launchpad Pro
Now you've got some nice new code to run! To upload it to your Launchpad Pro, you'll need a sysex tool for your host platform (I'd love to get it working from the virtual machine, but that's for later).  I recommend [Sysex Librarian](http://www.snoize.com/SysExLibrarian/) on OS X, and [MIDI OX](http://www.midiox.com/) on Windows.  On Linux, I'll bet you already have a tool in mind.

I won't describe how to use these tools, I'm sure you already know - and if you don't, their documentation is superior to mine!  Here's what you need to do:

1. Unplug your Launchpad Pro
2. Hold the "Setup" button down while connecting it to your host via USB (ensure it's connected to the host, and not to a virtual machine!)
3. The unit will start up in "bootloader" mode
4. Send your launchpad_pro.syx file to the device MIDI port - it will briefly scroll "upgrading..." across the grid.
5. Wait for the update to complete, and for the device to reboot!

Tip - set the delay between sysex messages to as low a value as possible, so you're not waiting about for ages while the firmware uploads!

# Bricked it!
Don't worry - even if you upload toxic nonsense to the device, you cannot brick it - the bootloader is stored in a protected area of flash.  If your new firmware doesn't boot, you'll get stuck at step (3) above, or with a crashed unit. Simply repeat the above process with the shipping firmware image (resources/Launchpad Pro-1.0.154.syx) to restore your unit to the factory defaults.  Better yet, fix the bugs :)

# Debugging
We decided not to support or encourage using a hardware debugger, as opening a Launchpad Pro to fit a debugging header can easily damage the FSR (force sensitive resistor) sheet.

Instead, you're going to have to do things the old fashioned way - by blinking LEDs or sending MIDI messages (though hopefully no need for a 'scope!).  For what it's worth, that's the way I've developed this version of the firmware - dogfooding all the way ;)

If do you want to debug interactively (and of course you do), you can use the simple command-line simulator located in the `/tools` directory.  It is compiled and ran as part of the build process, so it serves as a very basic test of your app before it is baked into a sysex dump.  If you want to test particular button presses or MIDI messages, just modify it to send those messages to your app, and debug away.  Yes, it's rudimental - wiring it up to the device over MIDI for interactive testing would be fab!

To debug the simulator interactively in Eclipse:

1. Click the down arrow next to the little "bug" icon in the toolbar
2. Choose "Debug configurations..."
3. Right click "C/C++ Application" and choose "New...:
4. Under "C/C++ Application" click Browse... and locate the simulator binary at `/vagrant/build/simulator`
5. Hit "Debug"!

# The Hardware
The Launchpad Pro is based around an ARM Cortex M3 from STMicroelectronics.  Specifically, an [STM32F103RBT6](http://www.st.com/web/catalog/mmc/FM141/SC1169/SS1031/LN1565/PF164487).  It's clocked at 72MHz, and has 20k RAM (I'm not sure how much of this we're using in the open build yet - should be a fair amount left but I haven't measured it).  The low level LED multiplexing and pad/switch scanning consume a fair bit of CPU time in interrupt mode, but have changed a little in the open firmware library (so again, I don't have measurements for how many cycles they're using).

It has 128k of flash memory, but I'm pretty sure we won't be exposing all of it as part of this API (dangerously easy to corrupt things!).  Current thinking is to expose a few pages for use by apps, though this would still introduce risks (accidentally wearing out sectors, for example).  To be continued...

# Vagrant tips
When you're done developing, simply type `vagrant suspend` to halt your VM without destroying it - this will make `vagrant up` a lot quicker next time.  If you're really finished, `vagrant destroy` will completely remove the VM from your system (but not any of your code).

If you only want to build using the command line, you might want to run your Vagrant box headless, which you can do by modifying the Vagrantfile: `vb.gui = false`.  You can also add more CPUs, RAM etc. if you want.

If prefer, you can install the gcc-arm toolchain on your local machine, or you might already have it.  You can find all you need [here](http://gnuarmeclipse.livius.net/).

It appears that VirtualBox does not yet work on Windows 10.

If your connection drops out while updating the Vagrant box, you can get stuck, unable to `vagrant up`.  To resolve, you need to delete the temp file - `~/vagrant.d/tmp`.

# Firmware development tips
OK - we're not going to need to use the MISRA rules, but there are a few things to avoid.  Dynamic memory allocation is a no (well it will work, but it's best avoided). Floating point will work, but it's implemented in software and will be slooooow.   C++ ought to work, but you'll definitely want to avoid exceptions and RTTI!
