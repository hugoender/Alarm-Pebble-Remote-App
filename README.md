HomeAlarmRemotePebble
=====================

**Home Alarm Remote for Raspberry Pi and Pebble Watch**

**Requirements:** Raspberry Pi with Webiopi installed. 
_________________________
***Update:*** After numerous requests, I have made the source code available. Now you can fork it, improve upon it, and then submit a pull request! I will review all pull requests and if yours gets pushed to the master branch, I will credit you on the app configuration page :) 

There is plenty that could be improved upon in this app so it should not be too hard to make it better.

Some fields in the code are commented out (i.e. IP Address, GPIO #) and you need to provided your own values for them otherwise the code will not work.
_________________________

Allows you to control two GPIO pins on a Raspberry Pi to arm and disarm your home alarm. 

Each press of a button brings the user specified GPIO high for 2 seconds and then drops it back down to low. 

You can specify the IP address of your Raspberry Pi and the port number that you set in Webiopi (default is 8050) in the configuration page of the app. You can also specify the GPIO pin numbers your setup uses (NOTE: this app uses the BCM numbering scheme not the header numbering!)

Top button is Arm, middle button is Disarm, and bottom button is unassigned (reserved for future use). When you press a button you will get one of two vibrations:
-One vibration means communication with phone Pebble app was successful.
-Two vibrations means communication with phone Pebble app failed. Make sure Pebble app is running on the phone. The       iPhone sometimes terminates the Pebble app if it has been running in the background for too long so make sure to reopen   the app to allow communication.

This is a proof of concept and while it works perfectly fine (I currently use it to arm and disarm my house alarm every day), I plan to add more features in the future.

Feel free to contact me with any questions at: endr42@gmail.com
