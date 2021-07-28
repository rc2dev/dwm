# dwm - dynamic window manager

Build of dwm by [Rafael Cavalcanti](https://rafaelc.org).

dwm is an extremely fast, small, and dynamic window manager for X.

## Third party patches

- alwayscenter
- bar height
- cyclelayouts
- fixborders
- noborder
- restartsig
- scratchpad
- sticky
- swallow
- systray
- vanitygaps

## My own patches

- Add class to systray. This allows adding rules for it on compton.
- Make layout symbol toggle between tiling and monocle.
- Move colors to separate file. Add file with default colors.
- Complement to `vanitygaps` patch: Allow toggling smartgaps on runtime.
- Complement to `vanitygaps` patch: Add gaps to monocle.
- Complement to `vanitygaps` patch: Add `vanitygaps.c` to `Makefile`, so changes are detected.
- Complement to `noborder` patch: Draw borders if gaps are enabled.
- Complement to `sticky` patch: Ignore sticky flag if fullscreen.
  Sticking a full screen window is not useful and prevents from switching tags (see commit e04a608).
- Key and mouse binds, window rules, aesthetics.

## Requirements

In order to build dwm you need the Xlib header files.

## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm

## Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
