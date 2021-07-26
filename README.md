# taghub 

This application collects information advertised by compatible BLE beacons
and publishes periodically to the Particle Cloud.
This version was tested on the Argon device 
and is designed to work with Eddystone or iBeacon-compatible tags.

The taghub collects data advertised by
intermittently nearby tags and forwards it to the Particle Cloud. 



### To Build & Flash with Particle Workbench (vscode)

This application may be built with Device OS version 2.1.0 (LTS) and above.

1. Clone this repository 
2. Init & Update Submodules `git submodule update --init --recursive`
3. Open Particle Workbench
4. Run the `Particle: Import Project` command, follow the prompts, to select this project's `project.properties` file and wait for the project to load
5. Run the `Particle: Configure Workspace for Device` command and select a compatible Device OS version and the `argon` platform when prompted ([docs](https://docs.particle.io/tutorials/developer-tools/workbench/#cloud-build-and-flash))
6. Connect your argon  device to your computer with a usb cable
7. Compile & Flash using Workbench


### To Build & Flash with Particle CLI

This application may be built with Device OS version 2.1.0 (LTS) and above.

1. Clone this repository 
2. Init & Update Submodules `git submodule update --init --recursive`
3. Cloud build (for argon board) with CLI :
`particle compile --target 2.1.0 argon --saveTo taghub_argon.bin`

4. Connect your Argon device t to your computer with a micro usb cable
5. Use the CLI to flash the device using dfu:
`particle usb dfu && particle flash --usb taghub_argon.bin`


