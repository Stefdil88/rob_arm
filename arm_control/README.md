# Installation

## Upload the ino file to the Arbotix
 * Create a folder called `ros`
 * Create symlink in the folder `ros` to all files in `arbotix_firmware/src`
 * Clone the git repository with the arbotix libraries: https://github.com/vanadiumlabs/arbotix.git
 * Go to the `sketchbook/libraries` folder of the Arduino software
 * Create symlinks to all folders in `<arbotix git repo>/libraries`
 * Board installation for Arduino 1.0.5
  * Go to `<arduino install directory>/hardware` and create a symlink to `<arbotix git repo>/hardware/arbotix`
 * Board installation for Arduino 1.6.x (does currently not work, see Troubleshooting)
  * Go to `<arduino install directory>/hardware` and create a new folder called `arbotix`
  * Open the folder `arbotix`
  * Create a symlink to `<arbotix git repo>/hardware/arbotix` with the name `avr`, so that the resulting folder structure is  `<arduino install directory>/hardware/arbotix/avr/<files and folders>`

# Troubleshooting

## INO compilation error in Arduino software

### exec: "-w": executable file not found in $PATH

    Board arbotix:avr:arbotix doesn't define a 'build.board' preference. Auto-set to: AVR_ARBOTIX
    Board arbotix:avr:arbotixrx doesn't define a 'build.board' preference. Auto-set to: AVR_ARBOTIXRX
    exec: "-w": executable file not found in $PATH
    Error compiling for board ArbotiX.
    
 * The arbotix files to currently not work with version 1.6.7 and 1.6.8. Use Arduino 1.0.5