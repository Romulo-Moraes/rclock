<div align="center">
    <img width=500" src="./assets/Project image.png">
    <h1></h1>
    <h3>A digital terminal clock written for POSIX systems, fully customizable with colors and datetime features</h3>
</div>

<img src="./assets/Rclock.png">
Rclock is a highly customizable digital clock for terminal interfaces written in C that runs on POSIX platforms, the included features of the clock are change the color of the components, optionally hide the date and the seconds, set a custom date and so on...

## Features
<ul>
    <li>Set a color to the clock</li>
    <li>Set a color to the date</li>
    <li>Set a color for each digit individually</li>
    <li>Set a color to the clock colons</li>
    <li>Set a color only for the digits</li>
    <li>Use a custom date format</li>
    <li>Set a custom hour</li>
    <li>Set a custom minute</li>
    <li>Set a custom second</li>
    <li>Set a custom time using the format xx:xx:xx</li>
    <li>Set a custom day</li>
    <li>Set a custom month</li>
    <li>Set a custom year</li>
    <li>Set a custom date using the format DD/MM/YYYY</li>
    <li>Hide the seconds</li>
    <li>Hide the date</li>
</ul>

# Table of contents
[Technical informations]()

[Installing the Rclock]()

[Running the program for the first time]()

[Configuring a new color to the clock]()

[Configuring a custom date]()

[Configuring a custom date format]()

[Configuring a custom time]()

[Making the clock smaller]()

[Development documentation]()

## Technical informations
This software was built using the following technologies
<ul>
    <li>C programming language</li>
    <li>Meson build system</li>
    <li>Ncurses library</li>
    <li>Anemone library</li>
</ul>


# Installing the Rclock
This software requires the following technologies to be installed in your machine:

### A compiler for the C language
The compiler used for developing the project was the GCC 13.2.1. Using the same compiler and the same version or newer is advisable.

### The meson build system
The meson build system documentation can be found on this link: https://mesonbuild.com/Getting-meson.html

### Ncurses library
The Ncurses library is also necessary to run the Rclock. This library is part of POSIX, so a Linux system typically has this library by default.

### Anemone library
The Anemone is a library used for command-line argument parsing, 

# Running the program for the first time
Once succesfully installed, the Rclock executable is globally visible and can already be ran. To call the executable just type the following command on terminal:

> $ rclock

Running this command, the digital clock should be visible on screen with the default configurations.

# Configuring a new color to the clock
One of the most attractive features of the Rclock is the hability of set new colors for each component, there's a variety of command-line flags that can define new colors for each piece of the clock,