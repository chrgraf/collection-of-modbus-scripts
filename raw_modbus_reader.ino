//very simple modbus-sniffer
//attach your max[3]485 towards your ESP32 serial2-ports (16/17)
//source https://microdigisoft.com/data.store/projects/Sketches/ESP32-Modbus.ino
//this is a slightly modified version to read 8 words
//use at own risk
//caveat: buffer_delay needs to be tuned. my queries arrive in 1sec interval, so I set this to 500ms. if set wrong, then this script will output incorrect data
//        improving this is a todo
//Output
/*
10:52:31.740 -> Serial Data received On:

10:52:31.740 -> Modbus Buffer[0]=11
10:52:31.740 -> Modbus Buffer[1]=1
10:52:31.784 -> Modbus Buffer[2]=3
10:52:31.784 -> Modbus Buffer[3]=0
10:52:31.784 -> Modbus Buffer[4]=11
10:52:31.784 -> Modbus Buffer[5]=0
10:52:31.784 -> Modbus Buffer[6]=5
10:52:31.784 -> Modbus Buffer[7]=0
*/


#include <SoftwareSerial.h>
// RS485 setup with ESp32
#define RE_DE 18             // Connect RE terminal with 32 of ESP
#define buffer_delay 500     // if this value does not fit, then this sketch will print incorrect data..
#define len 8
const byte ModReadBuffer[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
byte BufferValue[len];
//using hw-serial2
//SoftwareSerial mod(26, 27); // RX=26 , TX =27

void setup() {
  Serial.begin(74880);
  Serial2.begin(9600,SERIAL_8N1);
  //mod.begin(9600);// modbus configuration
  pinMode(RE_DE, OUTPUT);
  
}


void loop() {
  byte val1;
  while (Serial2.write(ModReadBuffer, sizeof(ModReadBuffer)) == 8) {
    val1 = ModbusData();
    delay(buffer_delay);            // my data arrives in 1 second interval. so I made query shortr (500ms)
  }
}
byte ModbusData(){
  byte i;
  digitalWrite(RE_DE,HIGH);
  
  delay(10);
  if(Serial2.write(ModReadBuffer,sizeof(ModReadBuffer))==8){
    digitalWrite(RE_DE,LOW);
    
    for(i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    BufferValue[i] = Serial2.read();
    }
    if(BufferValue[1]!=255 && BufferValue[2]!=255 ){
    Serial.println("Serial Data received On:"); 
    Serial.print("Modbus Buffer[0]="); 
    Serial.println(BufferValue[0],DEC);
    Serial.print("Modbus Buffer[1]="); 
    Serial.println(BufferValue[1],DEC);
    Serial.print("Modbus Buffer[2]="); 
    Serial.println(BufferValue[2],DEC);
    Serial.print("Modbus Buffer[3]="); 
    Serial.println(BufferValue[3],DEC);
    Serial.print("Modbus Buffer[4]="); 
    Serial.println(BufferValue[4],DEC);
        Serial.print("Modbus Buffer[5]="); 
    Serial.println(BufferValue[5],DEC);
        Serial.print("Modbus Buffer[6]="); 
    Serial.println(BufferValue[6],DEC);
        Serial.print("Modbus Buffer[7]="); 
    Serial.println(BufferValue[7],DEC);
     Serial.println("");}
   // }
  }
  return BufferValue[8];
}
 
