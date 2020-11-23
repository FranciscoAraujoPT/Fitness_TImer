# Fitness Timer
The Fitness Timer is a basic graphic interface based in c. Its main purpose is to count time up and down and allow the user to choose
between known time modes, ex: Tabata, simple timer, stopwatch... Besides that, it also features an option to show the current time of the computer like a clock.

## Packages Required
If you have not alredy installed, please install before compiling the program using the following command: 
```
sudo apt-get install build-essential libgtk-3-dev
```
```
sudo apt-get install libvlc-dev
```

## Compiling
To compile the programe use your favourite compiler follow by:
```
Timer.c -o "Fitness Timer" `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -lvlc
```
## Support
If you have any questions or you like to suggest something, don't hesitate in sending me a message or an email.
up201806326@fe.up.pt
