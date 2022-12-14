
#include <SPI.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>

#define SS_PIN 12
#define RST_PIN 14

#define bt1 27
#define bt2 26
#define bt3 25
#define bt4 33

LiquidCrystal_I2C lcd(0x27,16,2);
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];


uint8_t card[5][22][4]={{{0x03,0xE2,0x26,0xBC},//sword
                         {0x43,0x7F,0x1D,0xBC},
                         {0x23,0xCA,0x2B,0xBC},
                         {0xC3,0xEF,0x25,0xBC},
                         {0x43,0x81,0x1D,0xBC},
                         {0xC3,0xF3,0x20,0xBC},
                         {0x73,0x2B,0x27,0xBC},
                         {0x83,0x02,0x2D,0xBC},
                         {0x93,0x8D,0x29,0xBC},
                         {0x63,0x0D,0x1B,0xBC},
                         {0x73,0xA3,0x1B,0xBC},
                         {0xA3,0xF9,0x1D,0xBC},
                         {0xE3,0xA6,0x20,0xBC},
                         {0x83,0xB7,0x23,0xBC}},
                         
                        {{0x83,0xFF,0x2E,0xBC},//cup
                         {0x93,0x2A,0x23,0xBC},
                         {0xE3,0x14,0x20,0xBC},
                         {0xE3,0x58,0x20,0xBC},
                         {0x63,0x4C,0x2E,0xBC},
                         {0xC3,0xF1,0x20,0xBC},
                         {0x53,0x89,0x2C,0xBC},
                         {0xC3,0xED,0x25,0xBC},
                         {0x53,0x01,0x2F,0xBC},
                         {0xF3,0xD3,0x22,0xBC},
                         {0xD3,0x38,0x1D,0xBC},
                         {0x23,0xC9,0x1F,0xBC},
                         {0xF3,0xD1,0x22,0xBC},
                         {0xB3,0xED,0x25,0xBC}},
                         
                        {{0x03,0xA4,0x2E,0xBC},//penny
                         {0x03,0xD2,0x22,0xBC},
                         {0xB3,0x9F,0x1B,0xBC},
                         {0xA3,0x03,0x1D,0xBC},
                         {0x93,0xB7,0x23,0xBC},
                         {0x53,0x29,0x2A,0xBC},
                         {0x43,0xA2,0x2E,0xBC},
                         {0x13,0xA4,0x2E,0xBC},
                         {0xD3,0x46,0x2C,0xBC},
                         {0xD3,0x7E,0x1B,0xBC},
                         {0xD3,0x2F,0x1B,0xBC},
                         {0x43,0xA5,0x1B,0xBC},
                         {0xA3,0xFB,0x1D,0xBC},
                         {0xD3,0xAD,0x20,0xBC}},
                        
                        {{0xD3,0xE2,0x29,0xBC},//wand
                         {0xB3,0x4F,0x29,0xBC},
                         {0xF3,0xC5,0x1F,0xBC},
                         {0x63,0x4E,0x2E,0xBC},
                         {0x83,0x2B,0x1E,0xBC},
                         {0x53,0x87,0x2C,0xBC},
                         {0x23,0xCC,0x2B,0xBC},
                         {0xD3,0xE4,0x29,0xBC},
                         {0x43,0x7B,0x1B,0xBC},
                         {0x63,0x2D,0x1E,0xBC},
                         {0x33,0x4E,0x1B,0xBC},
                         {0xD3,0x3A,0x1D,0xBC},
                         {0x23,0xBC,0x1F,0xBC},
                         {0xE3,0xD3,0x22,0xBC}},
                         
                        {{0xB3,0xEF,0x25,0xBC},//major
                         {0x83,0xB8,0x23,0xBC},
                         {0xC3,0xFB,0x1B,0xBC},
                         {0x93,0xD9,0x1B,0xBC},
                         {0xE3,0x56,0x20,0xBC},
                         {0x83,0x0B,0x1B,0xBC},
                         {0xD3,0xF4,0x23,0xBC},
                         {0x73,0x04,0x2D,0xBC},
                         {0xE3,0x12,0x20,0xBC},
                         {0xE3,0xBB,0x1E,0xBC},
                         {0x03,0x84,0x26,0xBC},
                         {0xD3,0xAD,0x1D,0xBC},
                         {0x93,0xC7,0x1F,0xBC},
                         {0x43,0x70,0x23,0xBC},
                         {0x43,0x2B,0x2A,0xBC},
                         {0x43,0x48,0x26,0xBC},
                         {0xD3,0xF6,0x23,0xBC},
                         {0xE3,0xAB,0x1D,0xBC},
                         {0xD3,0x48,0x2C,0xBC},
                         {0x93,0xB8,0x23,0xBC},
                         {0x73,0x29,0x27,0xBC},
                         {0x23,0xFC,0x28,0xBC}}};

uint8_t card_val[78][4];


int flag_card=0;
int flag_card2=2;
int flag_card_val;

int cards;
float degree;
int flag_cards;

int suits=0;
int number=0;
float score=0;

int button_val=0;
int button_val1=0;
int button_val2=0;

int button_flag=1;

int player=0;
int multiple=0;

int player_cards[4];

int card_start;
int card_end;

void setup() { 
  Serial.begin(115200);

  

  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 4; i++) {
    key.keyByte[i] = 0xFF;
  }

  pinMode(bt1,INPUT_PULLUP);
  pinMode(bt2,INPUT_PULLUP);
  pinMode(bt3,INPUT_PULLUP);
  pinMode(bt4,INPUT_PULLUP);
  
  //Wire.begin();     
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Tarot Dealer");
  Serial.println("Tarot Dealer");
  delay(2000);
  lcd.clear();

  
}
 
void loop() {
  button_scan(4);//????????????

  if(button_flag==1){
    if(button_val==0){
      Serial.println("1 : gaming");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("1 : gaming");
    }
    else if(button_val==1){
      Serial.println("2 : shuffle");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("2 : shuffle");
    }
    else if(button_val==2){
      Serial.println("3 : scoring");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("3 : scoring");
    }
    
    else if(button_val==3){
      Serial.println("4 : rules");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("4 : rules");
    }
    button_flag=0;
  }

  
  switch(button_val1){
    case 1:
      Serial.println("1 : gaming");
      gaming();      
    break;
    case 2:
      Serial.println("2 : shuffle");
      shuffle();
    break;
    case 3:
      Serial.println("3 : scoring");
      scoring();
    break;
    case 4:
      Serial.println("4 : rules");
    break;  

  }
}

void choose2(){
  while(button_val1==0){
    button_scan(1);//????????????
    
    if(button_flag==1){
      Serial.println("continue");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("continue");
      button_flag=0;
    }
  }
  button_val=0;
  button_val1=0;
  button_flag=1;
}
void choose4(){  
  while(button_val1==0){
    button_scan(2);//????????????
    if(button_flag==1){
      if(button_val==0){
        Serial.println("1 : continue");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("1 : continue");
      }
      else if(button_val==1){
        Serial.println("2 : exit");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("2 : exit");
      }
      button_flag=0;
    }
    if(button_val1==2){
      return;
    }
  }
  button_val=0;
  button_val1=0;
  button_flag=1;
}
void choose(){  
  while(button_val1==0){
    button_scan(2);//????????????
    if(button_flag==1){
      if(button_val==0){
        Serial.println("1 : continue");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("1 : continue");
      }
      else if(button_val==1){
        Serial.println("2 : exit");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("2 : exit");
      }
      button_flag=0;
    }
    if(button_val1==2){
      return;
    }
  }
  button_val=0;
  button_val1=0;
  button_flag=1;
}

void guard(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("guard");
  delay(1000);
  for(int i=0;i<player;i++){
    while(button_val1==0){
      button_scan(5);
      if(button_flag==1){          
        if(button_val==0){
          multiple=0;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("player ");
          lcd.print(i+1);
          lcd.setCursor(0,1);
          lcd.print("pass");
          Serial.println("pass");
        }
        else if(button_val==5){
          multiple=0;
          lcd.clear();
          lcd.print("player ");
          lcd.print(i+1);
          lcd.setCursor(0,1);
          lcd.print("full hand");
          Serial.println("full hand");
        }
        else{ 
          if(button_val==1){
            multiple=1;
          }
          else if(button_val==2){
            multiple=2;
          }
          else if(button_val==3){
            multiple=4;
          }
          else if(button_val==4){
            multiple=6;        
          }
          lcd.clear();
          lcd.print("player ");
          lcd.print(i+1);
          lcd.setCursor(0,1);
          lcd.print("x");
          lcd.print(multiple);
          Serial.print("x");
          Serial.println(multiple);
        }
        button_flag=0;
      }
      switch(button_val1){
        case 1:
          multiple=0;
          Serial.println("pass");
        break;
        case 2:
          multiple=1;
          Serial.print("x");
          Serial.println(multiple);
        break;
        case 3:
          multiple=2;
          Serial.print("x");
          Serial.println(multiple);
        break;
        case 4:
          multiple=4;
          Serial.print("x");
          Serial.println(multiple);
        break;
        case 5:
          multiple=6;
          Serial.print("x");
          Serial.println(multiple);
        break;
        
      }
    }
    button_val=0;
    button_val1=0;
    button_flag=1;
  }
}

void players(){
  button_val=0;
  button_val1=0;
  player=0;
  multiple=0;
  button_flag=1;
  //players
  while(button_val1==0){
    button_scan(2);
    if(button_flag==1){          
      if(button_val==0)player=3;
      else if(button_val==1)player=4;
      else if(button_val==2)player=5;
      lcd.setCursor(0,1);
      Serial.print(player);
      Serial.println(" player");
      lcd.print(player);
      lcd.print(" player");
      button_flag=0;
    }
    switch(button_val1){
      case 1:
        player=3;
      break;
      case 2:
        player=4;  
      break;
      case 3:
        player=5; 
      break;     
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(player);
  lcd.print(" player");
  Serial.print(player);
  Serial.println(" player");
  button_val=0;
  button_val1=0;
  button_flag=1;
}





void choose3(){
  
}

//button_val ????????????0~num
//button_val1 ????????????
//button_val2 lcd flag
void button_scan(int num){   
  if(digitalRead(bt1)!=1){
    while(digitalRead(bt1)!=1){
      delay(10);
    }
    if(button_val<num)button_val++;
  }
  else if(digitalRead(bt2)!=1){
    while(digitalRead(bt2)!=1){
      delay(10);
    }
    if(button_val>0)button_val--;
  }
  else if(digitalRead(bt3)!=1){
    while(digitalRead(bt3)!=1){
      delay(10);
    }
    button_val1=button_val+1;
  }
  else if(digitalRead(bt4)!=1){
    while(digitalRead(bt4)!=1){
      delay(10);
    }
  }
  if(button_val!=button_val2){
    button_flag=1;
  }
  button_val2=button_val;
}


void dealing(){
  //server 0 degree
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("set zero point");
  Serial.println("set zero point");
  //code
  delay(1000);
  //deal
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("dealing");
  Serial.println("dealing");
  delay(1000);
  //code
  flag_cards=0;
  if(player==3||player==4)cards=72;
  else if(player==5)cards=75;
  while(cards!=flag_cards){
    for(int i=1;i<=player;i++){
      degree=360-((360/player)*i);
      ++flag_cards;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("dealing");
      lcd.setCursor(0,1);
      lcd.print(flag_cards);
      lcd.print(" ");
      lcd.print(i);
      lcd.print(" ");
      lcd.print((int)degree);
      lcd.print(" ");
      
      Serial.print(flag_cards);
      Serial.print(" ");
      Serial.print(i);
      Serial.print(" ");
      Serial.println((int)degree);
      delay(500);
      //rotate
    }
  }
  delay(1000);
  choose2();
  while(flag_cards!=78){
    for(int i=1;i<=player;i++){
      //dogs
      if(flag_cards==78)break;
      degree=360-((360/player)*i);
      ++flag_cards;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("dealing");
      lcd.setCursor(0,1);
      lcd.print(flag_cards);   
      lcd.print(" ");
      lcd.print(i);
      lcd.print(" ");
      lcd.print((int)degree);
      lcd.print(" ");
      
      Serial.print(flag_cards);
      Serial.print(" ");
      Serial.print(i);
      Serial.print(" ");
      Serial.println((int)degree);
      delay(500);
    }
  }
  delay(1000);
  button_val=0;
  button_val1=0;
  button_flag=1;
}


void rfid_scan(){
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  //Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  //Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    card_start=millis();
    flag_card2=0;
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
      card_val[flag_card_val][i]=rfid.uid.uidByte[i];
      flag_card_val++;
    }
  }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}





void card_type(){
  for(int i=0;i<5;i++){
    for(int j=0;j<22;j++){
      flag_card=0;
      for(int k=0;k<4;k++){
        if(nuidPICC[k]==card[i][j][k]){
          flag_card++;        
          if(flag_card==4&&flag_card2==0){
            lcd.clear();
            lcd.print("score");
            lcd.setCursor(0,1);
            if(i==0){
              lcd.print("sword ");
              lcd.print(j+1);
              Serial.print("sword");
              Serial.println(j+1);
              suits=1;
              number=j+1;
            }
            else if(i==1){
              lcd.print("cup ");
              lcd.print(j+1);
              Serial.print("cup");
              Serial.println(j+1);
              suits=2;
              number=j+1;
            }
            else if(i==2){
              lcd.print("penny ");
              lcd.print(j+1);
              Serial.print("penny");
              Serial.println(j+1);
              suits=3;
              number=j+1;
            }
            else if(i==3){
              lcd.print("wand ");
              lcd.print(j+1);
              Serial.print("wand");
              Serial.println(j+1);
              suits=4;
              number=j+1;
            }
            else if(i==4){
              lcd.print("major ");
              lcd.print(j);
              Serial.print("major");
              Serial.println(j);
              suits=5;
              number=j;
            }  
            flag_card2=1;
          }
        }
      }
    }
  }
}



void score_point(){
    if(flag_card2==1){
    if(suits==1||suits==2||suits==3||suits==4){
      if(number==14){
        score+=3.5;
      }
      else if(number==13){
        score+=3.5;
      }
      else if(number==12){
        score+=2.5;
      }
      else if(number==11){
        score+=1.5;
      }
      else{
        score+=0.5;
      }  
    }
    else if(suits==5){
      if(number==0||number==1||number==21){
        score+=0.5;
      }
      else{
        score+=0.5;
      }
    }
    lcd.setCursor(7,0);
    lcd.print(score);
    Serial.println(score);
    flag_card2++;
  }
}



void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}


void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}




void shuffle(){
  flag_cards=0;      
  do{  
    degree=(360/5)*random(4);
    if(player_cards[(int)degree/72]==18)continue;
    ++flag_cards;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("dealing");
    lcd.setCursor(0,1);
    lcd.print(flag_cards);
    lcd.print(" ");
    lcd.print((int)degree/72+1);
    lcd.print(" ");
    lcd.print((int)degree);
    lcd.print(" ");
    
    Serial.print(flag_cards);
    Serial.print(" ");
    Serial.print((int)degree/72+1);
    Serial.print(" ");
    Serial.println((int)degree);
    delay(500);
  
    player_cards[(int)degree/72]++;
    //rotate          
    
  }
  while(flag_cards<72);
  while(flag_cards!=78){
    for(int i=1;i<=4;i++){
      //dogs
      if(flag_cards==78)break;
      degree=360-((360/5)*1);
      ++flag_cards;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("dealing");
      lcd.setCursor(0,1);
      lcd.print(flag_cards);
      lcd.print(" ");
      lcd.print("5");
      lcd.print(" ");
      lcd.print((int)degree);
      lcd.print(" ");
      
      Serial.print(flag_cards);
      Serial.print(" ");
      Serial.print("5");
      Serial.print(" ");
      Serial.println((int)degree);
      delay(500);
    
    }
  }
  for(int i=0;i<4;i++){
    Serial.print(player_cards[i]);
    Serial.print(" ");
  }
  Serial.println("");
  delay(1000);
  button_val=0;
  button_val1=0;
  button_flag=1;
}

void scoring(){
  while(true){
    rfid_scan();
    card_type();
    score_point();
    card_end=millis()-card_start;
    Serial.println(card_end);
    if(card_end>6000){
      card_start=millis();
     
      choose();
      
    }
    if(button_val1==2){
      button_val=0;
      button_val1=0;
      button_flag=1;
      return;
    }
  }
}

void gaming(){
  players();
  dealing();   
  choose();
  if(button_val1==2){
    button_val=0;
    button_val1=0;
    button_flag=1;
    break;
  }
  guard();
}
