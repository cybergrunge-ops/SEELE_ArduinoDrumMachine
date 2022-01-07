#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

int value = 0; int addr = 0; const int outPin = 13;
const int buttonPin5 = 5; int buttonState5 = 0;
const int buttonPin6 = 6; int buttonState6 = 0;
const int buttonPin7 = 7; int buttonState7 = 0;
const int buttonPin8 = 8; int buttonState8 = 0;
int a = 100; int i = 0;int b = 1;int c = 1;int d = 1;int e = 1;int f = 1; int z = 0;
int currentsequence=0; int optionselect = 1;
int menuselect = 1; int ClearScreen = 1;
int lowOsc = 100; int midOsc = 900; int highOsc = 400;
int space = 50; int globalParam = 1; int otherParameter = 25;
int currentstep = 0; int loopLength = 14;
int letssave1 = 0; int letssave2 = 0; int letssave3 = 0; int letssave4 = 0;
int mem1; int mem2; int mem3; int mem4;
  int seq1[17] =  {9,8,7,6,3,1,1,4,1,0,1,1,2,6,6,6};
  int seq2[17] =  {1,2,1,1,3,1,1,4,1,0,2,1,2,6,2,6};
  int seq3[17] =  {3,2,1,0,3,2,1,0,3,2,1,0,3,2,1,0};
  int seq4[17] =  {1,1,1,1,3,1,1,4,1,0,1,1,2,6,6,6};

void setup() {int r=0; int addr=0;
  lcd.init(); lcd.backlight();
  Serial.begin(9600);
  Serial.println();  
Serial.print("EEPROM read 1");Serial.println();
  for(addr=0;addr<16;addr++) {mem1 = EEPROM.read(addr);Serial.print(mem1);}Serial.println();
Serial.print("EEPROM read 2");Serial.println();
  for(addr=17;addr<33;addr++){mem2 = EEPROM.read(addr);Serial.print(mem2);}Serial.println();
Serial.print("EEPROM read 3");Serial.println();
  for(addr=33;addr<49;addr++){mem3 = EEPROM.read(addr);Serial.print(mem3);}Serial.println();
Serial.print("EEPROM read 4");Serial.println();
  for(addr=49;addr<65;addr++){mem4 = EEPROM.read(addr);Serial.print(mem4);}Serial.println();
Serial.println();  
  pinMode(buttonPin7, INPUT); //otherParameter select"
  pinMode(buttonPin6, INPUT); //"otherParameter change"
  pinMode(buttonPin5, INPUT); //"menu select"
  pinMode(buttonPin8, INPUT); //unused right now
      pinMode(13, OUTPUT);//audio output
}

int dOsc1(int decaytime) {  a=1; for(a=1; a<799900/decaytime;a=a+otherParameter) {    
    delayMicroseconds(1 + a*5); digitalWrite(outPin, HIGH);    
    delayMicroseconds(1 + a*5); digitalWrite(outPin, LOW);} a = 1;}
int osc1(int pitch) {  f=1; for(f=1; f<1599000/pitch; f=f+otherParameter) {
    delayMicroseconds(pitch); digitalWrite(outPin, HIGH);    
    delayMicroseconds(pitch); digitalWrite(outPin, LOW);  } f = 1;}
int osc2(int pitch) {  f=1; for (f=1; f<1599000/pitch;f=f+otherParameter) {    
    delayMicroseconds(pitch); digitalWrite(outPin, HIGH);    
    delayMicroseconds(pitch/2); digitalWrite(outPin, LOW);} f = 1;}    
int noiseGen1(int lowlimit) {  c=1; for (c=1; c<1999000/lowlimit;c=c+otherParameter) {    
    delayMicroseconds(random(1, lowlimit)); digitalWrite(outPin, HIGH);    
    delayMicroseconds(random(1, lowlimit)); digitalWrite(outPin, LOW);} c=1;}
int noiseGen2(int decaytimeB) {  c=1; for(c=1;c<999000/decaytimeB; c=c+otherParameter) {    
    delayMicroseconds(random(10, c/2)); digitalWrite(outPin, HIGH);    
    delayMicroseconds(random(10, c/2)); digitalWrite(outPin, LOW);} c=1;}

int getsoundset(int currentCharV, int stepvalue, int spacevalue,int mode, int currentstep){
    if (currentCharV == 0) {if(mode==1){lcd.setCursor(stepvalue, 0); lcd.print('0');} else{}  noiseGen1(330+globalParam);  delay(spacevalue);    } else {}  
    if (currentCharV == 1) {if(mode==1){lcd.setCursor(stepvalue, 0); lcd.print('1');} else{}  dOsc1(890+globalParam);      delay(spacevalue);    } else {} 
    if (currentCharV == 2) {if(mode==1){lcd.setCursor(stepvalue, 0); lcd.print('2');} else{}  dOsc1(944+globalParam);      delay(spacevalue);    } else {}
    if (currentCharV == 3) {if(mode==1){lcd.setCursor(stepvalue, 0); lcd.print('3');} else{}  noiseGen2(366+globalParam);  delay(spacevalue);    } else {} 
    if (currentCharV == 4) {if(mode==1){lcd.setCursor(stepvalue, 0); lcd.print('4');} else{}  noiseGen2(200+globalParam);  delay(spacevalue);    } else {}
    if (currentCharV == 5) {if(mode==1){lcd.setCursor(stepvalue, 0); lcd.print('5');} else{}  noiseGen1(230+globalParam);  delay(spacevalue);    } else {} 
    if (currentCharV == 6) {if(mode==1){lcd.setCursor(stepvalue, 0); lcd.print('6');} else{}  noiseGen1(2130+globalParam); delay(spacevalue);    } else {}  
    if (currentCharV == 7) {if(mode==1){lcd.setCursor(stepvalue, 0); lcd.print('7');} else{}  osc1(highOsc); delay(spacevalue);     } else {}  
    if (currentCharV == 8) {if(mode==1){lcd.setCursor(stepvalue, 0); lcd.print('8');} else{}  osc1(lowOsc*20); delay(spacevalue);   } else {}  
    if (currentCharV == 9) {if(mode==1){lcd.setCursor(stepvalue, 0); lcd.print('9');} else{}  osc2(midOsc); delay(spacevalue);      } else {}  
    if(menuselect==0){ lcd.setCursor(14, 0); lcd.print(currentstep+1);}
    //tells us which step we are editing in edit mode

if(letssave1==1){ Serial.print("EEPROM write");Serial.println();
  int addr=0; for(addr==0;addr<16;addr++){
  int val = seq1[addr]; EEPROM.write(addr, val); Serial.print(val);
      if (addr==15){addr=0; letssave1=0; Serial.println();break;} }}
if(letssave2==1){ Serial.print("EEPROM write");Serial.println();
  int addr=16; int i=-1; for(addr==16;addr++;){i++;
  int val = seq2[i]; EEPROM.write(addr, val); Serial.print(val);
      if (addr==32){addr=0;i=0; letssave2=0; Serial.println();break;} }}
if(letssave3==1){ Serial.print("EEPROM write");Serial.println();
  int addr=32; int i=-1; for(addr==32;addr++;){i++;
  int val = seq3[i]; EEPROM.write(addr, val); Serial.print(val);
      if (addr==48){addr=0;i=0; letssave3=0; Serial.println();break;} }}      
if(letssave4==1){ Serial.print("EEPROM write");Serial.println();
  int addr=48; int i=-1; for(addr==48;addr++;){i++;
  int val = seq4[i]; EEPROM.write(addr, val); Serial.print(val);
      if (addr==64){addr=0;i=0; letssave4=0; Serial.println();break;} }}



  int menuselector = digitalRead(buttonPin5);
  if(menuselector==HIGH) {menuselect=menuselect+1;} //flip thru menus
//loop editor 
    if (menuselect==0) {
      //lets read the buttons right away
        buttonState6 = digitalRead(buttonPin6); 
        buttonState7 = digitalRead(buttonPin7);
        lcd.setCursor(0, 0); lcd.print("Editing Step:");
        for(z=0;z<loopLength;z++){lcd.setCursor(z,1); lcd.print(seq1[z]);}
        // this just shows the pattern
        if(buttonState7==HIGH){seq1[currentstep] = seq1[currentstep] +1;}
        if(buttonState6==HIGH){currentstep = currentstep+1;}
    }
        
//playback menu without functions for buttons set up yet
    if (menuselect==1) 
     { optionselect=0;
        buttonState6 = digitalRead(buttonPin6); 
        buttonState7 = digitalRead(buttonPin7);
        if(buttonState6==HIGH){optionselect=optionselect+1;} //up
        if(buttonState7==HIGH){optionselect=optionselect-1;} //down
        lcd.setCursor(0, 1); lcd.print("Load");
     if(optionselect==1) {lcd.setCursor(5,1); lcd.print(">1"); currentsequence = 1;} else {lcd.setCursor(5,1); lcd.print(" 1");}
     if(optionselect==2) {lcd.setCursor(7,1); lcd.print(">2"); currentsequence = 2;} else {lcd.setCursor(7,1); lcd.print(" 2"); }
     if(optionselect==3) {lcd.setCursor(9,1); lcd.print(">3"); currentsequence = 3;} else {lcd.setCursor(9,1); lcd.print(" 3"); }
     if(optionselect==4) {lcd.setCursor(11,1); lcd.print(">4"); currentsequence = 4;} else {lcd.setCursor(11,1); lcd.print(" 4");}
    }

// osc editor menu, functions not set up yet....
    if (menuselect==2){ 
        buttonState6 = digitalRead(buttonPin6); 
        buttonState7 = digitalRead(buttonPin7);
        if(buttonState6==HIGH){optionselect=optionselect+1;} //select
        lcd.setCursor(0, 1); lcd.print("Load");
      if(optionselect==1) {lcd.setCursor(0,0); lcd.print("F3>>"+String(lowOsc/100));if(buttonState7==HIGH){lowOsc=lowOsc+5;}else{} if(buttonState8==HIGH){lowOsc=lowOsc-5;}else{} } else { lcd.setCursor(0,0); lcd.print("F3: "+String(lowOsc/100));}
      if(optionselect==2) {lcd.setCursor(7,0); lcd.print("F2>>"+String(midOsc/100));if(buttonState7==HIGH){midOsc=midOsc+5;}else{} if(buttonState8==HIGH){midOsc=midOsc-5;}else{}} else { lcd.setCursor(7,0); lcd.print("F2: "+String(midOsc/100));}
      if(optionselect==3) {lcd.setCursor(0,1); lcd.print("F1>>"+String(highOsc/100));if(buttonState7==HIGH){highOsc=highOsc+5;}else{} if(buttonState8==HIGH){highOsc=highOsc-5;}else{}} else { lcd.setCursor(0,1); lcd.print("F1: "+String(highOsc/100));}
      if(optionselect==4) {lcd.setCursor(12,1); lcd.print("Oscs");} else {lcd.setCursor(12,1); lcd.print("Oscs");}
      
      
      }

// EEPROM menu not relavent right now either
    if (menuselect==3){
      if(optionselect==1) {lcd.setCursor(0,0); lcd.print(">Save 1");if(buttonState7==HIGH){letssave1=1;}else{};} else { lcd.setCursor(0,0); lcd.print("Save 1");} 
      if(optionselect==2) {lcd.setCursor(8,0); lcd.print(">Save 2");if(buttonState7==HIGH){letssave2=1;}else{};} else { lcd.setCursor(8,0); lcd.print("Save 2");} 
      if(optionselect==3) {lcd.setCursor(0,1); lcd.print(">Save 3");if(buttonState7==HIGH){letssave3=1;}else{};} else { lcd.setCursor(0,1); lcd.print("Save 3");} 
      if(optionselect==4) {lcd.setCursor(8,1); lcd.print(">Save 4");if(buttonState7==HIGH){letssave4=1;}else{};} else { lcd.setCursor(8,1); lcd.print("Save 4");} }   
    
// time menu
    if (menuselect==4){
      //6 is change 7 is select
      if(buttonState7==HIGH){optionselect=optionselect+1;}
      if(buttonState6==HIGH){loopLength=loopLength+1;}
      if(optionselect==1){lcd.setCursor(0,0); lcd.print("speed>" + String(space));if(buttonState7==HIGH){space=space+5;}else{};if(buttonState8==HIGH){space=space-5;}else{};} else {lcd.setCursor(0,0); lcd.print("speed:" + String(space));}
      if(optionselect==2){lcd.setCursor(11,0); lcd.print("null:>_]");} else {lcd.setCursor(9,0); lcd.print("null:__ ");}
      if(optionselect==3){lcd.setCursor(0,0); lcd.print("??>" + String(otherParameter)+"]"); if(buttonState7==HIGH){otherParameter=otherParameter+5;}else{}; if(buttonState8==HIGH){otherParameter=otherParameter-5;}else{}; } else {lcd.setCursor(0,1); lcd.print("??:" +String(otherParameter));}
      if(optionselect==4){lcd.setCursor(6,1); lcd.print("length>" +String(loopLength));  if(buttonState7==HIGH){loopLength=loopLength+1;}else{}; if(buttonState8==HIGH){loopLength=loopLength-5;}else{}; } else {lcd.setCursor(7,1); lcd.print("length:" +String(loopLength));}
      }
if(menuselect==5) {lcd.setCursor(0,0); lcd.print("CGSeq V0.1 - by");lcd.setCursor(0,1); lcd.print("cybergrunge.net");}

}//end of our step clock tasks

void loop() { int i = 0;
  buttonState5 = 0; buttonState6 = 0; buttonState7 = 0; buttonState8 = 0;
if(currentstep>loopLength) {currentstep=0;}
if(seq1[currentstep]>9) {seq1[currentstep]=0;}
if(loopLength>16) {loopLength=0;}
if(menuselect>5) {menuselect=0;}

  if (ClearScreen == 1) { lcd.clear();} else {}//clear screen if option enabled.
  

  
 // int selectparam = digitalRead(buttonPin7);
  //if(menuselector==HIGH) {menuselect=menuselect+1;} //change param  
 // int changeparam = digitalRead(buttonPin6);
  //if(menuselector==HIGH) {menuselect=menuselect+1;} //select param
  


  
//if we are NOT in edit mode, let it "render" the loop in menu 1 and play it with getsoundset
    if(menuselect!=0){ for (i = 0; i < loopLength; i++) {int currentChar = seq1[i]; getsoundset(currentChar,i,space,menuselect,currentstep);}}

//if we ARE in edit mode, lets do something different. 
    if(menuselect==0){ for (i = 0; i < loopLength; i++) {int currentChar = seq1[i]; getsoundset(currentChar,i,space,menuselect,currentstep);}}
        
    //just to be safe???
  i=0;
}
