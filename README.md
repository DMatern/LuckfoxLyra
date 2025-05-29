# LuckfoxLyra
Information on Luckfox Lyra Linux Board, Programming, and use in applications

# Hardware Infroamtion:
GPIO (https://wiki.luckfox.com/Luckfox-Lyra/Buildroot/Lyra-pinout/GPIO/)
I2C  (https://wiki.luckfox.com/Luckfox-Lyra/Buildroot/Lyra-pinout/I2C)
SPI  (https://wiki.luckfox.com/Luckfox-Lyra/Buildroot/Lyra-pinout/SPI)

# Software Information:

default user directory:  /root/
my code test directory:  /root/dev/

> Program Process:

WSL Required Libraries - 
  ARM Gcc Plugin - sudo apt install gcc-arm-linux-gnueabihf
  
Usw WSL and VSCode with WSL plugin to develop code. 
Once developed, when inside WSL CLI use gcc to compile the program below

  arm-linux-gnueabihf-gcc -o my_program my_program.c

Once compiles, use Windows PC to move binary file created to SD card and move to Lyra.
Copy file from SD card to appropret directory and the run code

  ./my_program

> Mount SD Card:

Create Directory: sudo mkdir /mnt/sdcard
Mount SD Card:    sudo mount /dev/mmcblk0p1 /mnt/sdcard
Verify Device:    df -h


# GPIO:

pin = bank * 32 + number
number = group * 8 + X
pin = bank * 32 + (group * 8 + X)

For example, calculating the pin number for GPIO1_B1: 1×32+(1×8+1)=41

GPIO pin numbers are labeled in the pin diagram, which can be directly used or calculated using the method below:
GPIO has 5 banks: GPIO0~GPIO4, each bank is divided into 4 groups, with a total of 32 pins: A0~A7, B0~B7, C0~C7, D0~D7
GPIO pins are named as GPIO{bank}_{group}{X}, such as:

GPIO0_A0 ~ A7 
GPIO0_B0 ~ B7 
GPIO0_C0 ~ C7 
GPIO0_D0 ~ D7 
   
GPIO1_A0 ~ A7 
.... 
GPIO1_D0 ~ D7
.... 
GPIO4_D0 ~ D7
  
> Controlling GPIO via Sysfs

root@luckfox:/home/luckfox# ls /sys/class/gpio
export  gpio41  gpiochip0  gpiochip128  gpiochip32  gpiochip509  gpiochip64  gpiochip96  unexport

cd /sys/class/gpio/gpio41
root@luckfox:/sys/class/gpio/gpio41# ls
active_low  device  direction  edge  power  subsystem  uevent  value**

Export GPIO to User Space:
echo 41 > /sys/class/gpio/export  

Unexport GPIO from User Space:
echo 41 > /sys/class/gpio/unexport 

> Controlling GPIO Levels
Set Direction

root@luckfox:/sys/class/gpio/gpio41# pwd   # Ensure you're in the target GPIO directory
/sys/class/gpio/gpio41

echo out > direction                      # Set GPIO as output
echo in > direction                       # Set GPIO as input

Control GPIO Level Using the value Attribute

Output
echo 1 > value
echo 0 > value

Input
cat value        

Pinout:
![Luckfox-Lyra-B-details-inter-en-1d9e0fe6eaee6066d7f3d849631feb83](https://github.com/user-attachments/assets/36579058-8897-4174-884e-39b7014ae2d0)
