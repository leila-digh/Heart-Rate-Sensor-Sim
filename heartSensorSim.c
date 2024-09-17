/*****************************************************************************/
/*  This program accepts user-inputed int heart rate in the range of 0 to 255*/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include <math.h>

void getInput(int*);

int getHeartRate(int heartBPM, unsigned short *heartRate);
void prepareHeartRate(int sensorFunction, unsigned short *heartRate);
void presentHeartRate(unsigned short *heartRate);

short bitSet(unsigned short, int);
int bitRead(unsigned short, int);
short bitClear(unsigned short, int);

void printAsBinary8(unsigned short);
void printAsBinary16(unsigned short);

int main(){
    unsigned short heartRate = 0; //output
    int heartBPM = 0; //input
    int sensorFunction = 0;
    getInput(&heartBPM);
    sensorFunction = getHeartRate(heartBPM, &heartRate);
    prepareHeartRate(sensorFunction,&heartRate);
    presentHeartRate(&heartRate);
    


    return 0;
}

void getInput(int *heartBPM){
    printf("Welcome\n");
    printf("Please input your heart BPM\n");
    printf("(must be between 0 and 255)\n");
    scanf("%d",heartBPM);
    while(getchar() != '\n');
}


/* Function:  getHeartRate
  Purpose:   obtains the heart rate data of the person using the device and
checks that the input values are within the legal range
  Parameters:
    in:  heartBPM: The heart rate data, which is a positive value of up to 255
    out:  *heartRate: This parameter contains the output of the heart rate sensor.
    return: 0 – the request was completed correctly
            1 – the data is out of the range
*/
int getHeartRate(int heartBPM, unsigned short *heartRate){
    if(heartBPM>=0 && heartBPM <= 255){
        unsigned short temp = (unsigned short)heartBPM;
        temp = temp<<3;
        *heartRate = temp;
        return 0;
    }else{ //out of range
        return 1;
    }
}



/* Function:  prepareHeartRate
  Purpose:   print an array
  Parameters:
    in:     array to print
    return: void
*/
void prepareHeartRate(int sensorFunction, unsigned short *heartRate){

    //Set Parity bit 15 and rest bit (bit 1)
    if(sensorFunction == 1){
        *heartRate = bitSet(*heartRate, 15); //illegal input
        *heartRate = bitSet(*heartRate, 1); //requires resetting 
    }

    //Set Abnormal HeartRate (2, 11 and 12)
    if((*heartRate >>3) < 50){ 
        *heartRate = bitSet(*heartRate, 2);
        *heartRate = bitSet(*heartRate, 11);
        *heartRate = bitSet(*heartRate, 12);
    }else if((*heartRate >>3) > 165){
        *heartRate = bitSet(*heartRate, 2);
        *heartRate = bitSet(*heartRate, 12);
    }
}

/* Function:  presentHeartRate
  Purpose:   Present the data to the user
  Parameters:
    in:     heartRate
    return: void
*/
void presentHeartRate(unsigned short *heartRate){
    int isHigh =0;
    int isLow = 0;
    int isHR = 0;
    int isCorrect = bitRead(*heartRate,0);
    int toRest = bitRead(*heartRate,1);
    int isAbn = bitRead(*heartRate,2);
    unsigned char bpm = *heartRate >>3;
    int bit11 = bitRead(*heartRate,11);
    int bit12 = bitRead(*heartRate,12);
    if(bit11 == 0 && bit12 == 1){
        isHigh =1;
    }else if (bit11 == 1 && bit12 == 1){
        isLow = 1;
    }else if(bit11 == 0 && bit12 == 0){
        isHR = 1;
    }
    
    int isNormal = bitRead(*heartRate,15);

    printf("\n\n");
    printf("Heart Rate Sensor Information:\n");
    printf("The output of the heart rate sensor is 0x%X = ", *heartRate);
    printAsBinary16(*heartRate);
    if(isCorrect==0){
        printf("The value of bit 0 is 0, which indicates the device is CORRECT reading.\n");
    }else if(isCorrect==0){
        printf("The value of bit 0 is 1, which indicates the device has an INCORRECT reading.\n");
    }
    if(toRest == 0){
        printf("The value of bit 1 is 0, which indicates the sensor is NOT required to reset.\n");
    }else if(toRest == 1){
        printf("The value of bit 1 is 1, which indicates the sensor is REQUIRED to be RESET.\n");
    }
    if(isAbn == 0){
        printf("The value of bit 2 is 0, which indicates heart rate is NORMAL.\n");
    }else if(isAbn == 1){
        printf("The value of bit 2 is 1, which indicates an ABNORMAL heart rate has been detected.\n");
    }
    printf("The value of bits 3 to 10 is 0x%X, which indicates the heart rate is %d bpm.\n",bpm,bpm);
    if(isHigh == 1){
        printf("The value of bits 11 to 12 is 2, which indicates a HIGH heart rate.\n");
    }else if(isLow ==1){
        printf("The value of bits 11 to 12 is 3, which indicates a LOW heart rate.\n");
    }else if(isHR == 1){
        printf("The value of bits 11 to 12 is 0, which indicates a NORMAL heart rate.\n");
    }
    if(isNormal == 0){
        printf("The value of bit 15 is 0, which indicates a NORMAL input.\n");
    }else{
        printf("The value of bit 15 is 1, which indicates your input is NOT normal.\n");
    }

}


int bitRead(unsigned short bitInput, int bitNum){
    //int bitVal;
    return ((bitInput & (1 << bitNum)) >> bitNum);
    //return 0;
}


short bitSet(unsigned short bitInput, int bitNum){
    return bitInput | (1 << bitNum);
}

short bitClear(unsigned short bitInput, int bitNum){
    return bitInput & (~(1 << bitNum));
}


void printAsBinary8(unsigned short n) {
    for (int i=7; i>=0; i--) {
        if ((int)(n/pow(2,i)) > 0) {
            printf("1");
            n = n - pow(2,i);
        }
        else
            printf("0");
    }
    printf("\n");
}


void printAsBinary16(unsigned short n) {
    for (int i=15; i>=0; i--) {
        if ((int)(n/pow(2,i)) > 0) {
            printf("1");
            n = n - pow(2,i);
        }
        else
            printf("0");
    }
    printf("\n");
}