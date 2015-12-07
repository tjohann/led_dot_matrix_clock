LED-Dot-matrix based clock
===============

This is my LED-Dot-matrix based clock.  


Preparation (toolchain)
-------------------

Clone the toolchain repo into your home directory:

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







