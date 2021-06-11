> tag name: kairos

# Kairos webassembly custom libc

> WIP: Not stable at this time. This project is meant to be a custom c library or libc implemented within webassembly. This is a toy project that I am going to be using with my current operating system called IsmenaOS.

## Usage

`make KAIROS_CC=/path/to/wasm/supporting/c/compiler`

This will create a `sysroot` folder depending on where you run the command from, but this is assumed to created within the same repo.

To have the `sysroot` created in a different location:

`make KAIROS_CC=/path/to/wasm/supporting/c/compiler --sysroot=/path/to/new/sysroot ...`