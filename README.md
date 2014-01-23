HomeAlarmRemotePebble
=====================

Home Alarm Remote for Raspberry Pi and Pebble Watch

Requirements: Raspberry Pi with Webiopi installed. 

Allows you to control two GPIO pins on a Raspberry Pi to arm and disarm your home alarm. 

Each press of a button brings the user specified GPIO high for 2 seconds and then drops it back down to low. 

Top button is Arm, middle button is Disarm, and bottom button is unassigned (reserved for future use). When you press a button you will get one of two vibrations:

  -One vibration means communication with phone Pebble app was successful.

  -Two vibrations means communication with phone Pebble app failed. Make sure Pebble app is running on the phone. The       iPhone sometimes terminates the Pebble app if it has been running in the background for too long so make sure to reopen   the app to allow communication.

This is a proof of concept and while it works perfectly fine (I currently use it to arm and disarm my house alarm every day), I plan to add more features in the future.



