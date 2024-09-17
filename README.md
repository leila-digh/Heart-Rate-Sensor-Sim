# Heart Rate Sensor Sim
This project simulates how a heart rate sensor would work in a wearable device. It prompts the user to input a heart rate reading and encodes the information into a 16-bit number. Information such as if the heart rate is normal, if the input is valid and if the sensor is reading correctly.

These are instructions on how to interpret the output
###### Bits 0-2
	Bit 0 - 0 indicates that the device reading is correct
	Bit 1 - 0 indicates that the sensor is not required to reset
	Bit 2 - 0 indicates that a normal heart rate has been detected
###### Bits 3-10
	Set to the binary value of the heart rate
###### Bit 11-12
	Indicates the type of abnormal heart rate (if bit 2 is set to 1)
	Set to 2 (10) indicates a high heart are (above 165)
	Set to 3 (11) indicates a low heart rate (less than 50)
###### Bits 13-14 
    (unused)
###### Bit 15 (parity bit) 	
    A value of 1 indicates illegal input

###### This project demonstrates my understanding of;
	1. Bitwise Operations
	2. Pointers
	3. Error Checking
 	4. Programming Conventions

Example:
```
Please input your heart BPM
(must be between 0 and 255)
>> 170
0001010101010100
```


###### Interprating the output
    0 00 10 10101010 100
>Bit 0 has the value of 0 indicating that the device is reading correctly
>
>Bit 1 has the value of 0 indicating that the sensor is not required to reset
>
>Bit 2 has the value of 1 indicating that an abnormal hear rate has been detected
>
>Bits 3-10 have the vaule of 170 in binary (10101010)
>
>Bit 15 has the value of 0 indicating that the input is valid

### How to compile and run
1. Save the file to your computer
2. Open the command line/terminal and navigate to the directory you have the file saved in
3. Enter the following commands to compile and run the program:
   ```
   gcc -o heartRateSensorSim heartRateSensorSim.c
   ./heartRateSensorSim
   ```
4. Follow the instructions in terminal.

