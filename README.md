LED-Dot-matrix based clock
===============

This is my LED-Dot-matrix based clock. The purpose of this repo is to collect all software components into one place. The project has a lot different programs and daemons. 

     tempd -> a temperature daemon
     matrixd -> a daemon to controll the led-dot-matrix
     ...



Preparation (toolchain)
-------------------

To crossbuild the software on your linux host you need a toolchain. I already provide one for armel/arm926 devices. To get it, you have to clone the sdk repo into your home directory and follow the instructions.

Clone toolchain repo:

        git clone https://github.com/tjohann/arm926_sdk.git


After cloning, "source" the env file to set the necessary environment variables. You can either set this to run automatically via a .bashrc entry as outlined below..

        # setup the arm926 environment
        if [ -f ~/arm926_sdk/armel_env ]; then
            . ~/arm926_sdk/armel_env 
        fi


.. or do it manually everytime you want to work with the sdk. 

        . ./armel_env

To download and install the toolchain, type

        make get_toolchain


Now you should have a working cross compiler for the clock.


Preparation (hardware)
-------------------

See https://github.com/tjohann/arm926_sdk for images and hardware details!


Create sd-card image
-------------------

See https://github.com/tjohann/arm926_sdk/docs/howto_sdcard.txt


Usage
-------------------

t.b.d.







