//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//#define DEBUG 
#ifdef DEBUG
#define BEBUG_TEST(x) {x}
#else
#define BEBUG_TEST(x)
#endif


int bpok = 3; /////Entrées/Sorties Digitales ( Variables --> Broches)/////////
int bph = 4;
int bpb = 5;
int PRES= 10;
int bpback = 6;
int Pompe1 = 7;
int Pompe2 = 8;
int LedPompe1 = 9;
int LedPompe2 = 11;
int LedVerte = 12;
int LedRouge = 13;
int Buzz = 2;

int ietat = 0; ////////Variables Globales/////////
int BPOK = 0;
int BPOKavant = 0;
int BPH = 0;
int BPHavant = 0;
int BPB = 0;
int BPBavant = 0;
int BPBACK = 0;
int BPBACKavant = 0;
int Mesure1;
int Mesure2;
int Seuil1_1;
int Seuil2_1;
int Seuil1_2;
int Seuil2_2;
int SeuilAlerte1;
int SeuilAlerte2;
int NbSondes = 1; 
int i_B0 = 0;
int Cpt = 1;
int Cpt2 = 0;


void BlkOK(void);// Fonction Blink OK // void B_2_1(void);// void B_2_2(void);//void B_4_1(void);//void B_4_2(void);//void B_6_1(void);//void B_6_2(void);//void B_0(void);
void RESET(void);// Fonction RESET Système //void A_9(void);
void CPT_1(void);// Fonction comptage bouton /1 //void B_0(void);
void CPT_5(void);// Fonction comptage bouton /5 //void B_3_1(void);//void B_3_2(void);
void SavingNbSens1(void);//void A_0_1(void); ////// Fonctions : Actions de Mealy///////
void SavingNbSens1_1(void);
void Aff_Val2(void);//void A_0_2(void);
void SavingValS1_1(void);//void A_1_1(void);
void SavingValS1_2(void);//void A_1_2(void);
void Aff_Hyst_D1(void);//void A_2_1(void);
void Aff_Hyst_D2(void);//void A_2_2(void);
void Calc_S2_1(void);//void A_3_1(void);
void Calc_S2_2(void);//void A_3_2(void);
void Aff_LevelA1(void);//void A_4_1(void);
void Aff_LevelA2(void);//void A_4_2(void);
void Saving_SA1(void);//void A_5_1(void);
void Saving_SA2(void);//void A_5_2(void);
void Aff_Val1(void);//void A_6_1(void);
void Aff_Val1_Val2(void);//void A_6_2(void);
void HIGH_OUT1(void);//void A_7_1_1(void);
void HIGH_OUT2(void);//void A_7_1_2(void);
void Clear_LCD(void);//void A_7_2_1(void);//void A_7_2_2(void);
void LOW_OUT1(void);//void A_8_1(void);
void LOW_OUT2(void);//void A_8_2(void);
void HIGH_RETRO(void);
void LOW_RETRO(void);



                 ////// Fonctions : Actions de Moore ////////
void Aff_Mesure1(void);//void B_1_1(void);//void B_5_1(void);//void B_5_2(void);
void Aff_Mesure1_2(void);
void Aff_Mesure2(void);//void B_1_2(void);//void B_7_1(void);
void Aff_Mesure12(void);//void B_7_2(void);
void Aff_WATER1(void);//void B_8_1(void);
void Aff_WATER2(void);//void B_8_2(void);
void Aff_WATERLEVEL1(void);//void B_9(void);
void Aff_WATERLEVEL2(void);//void B_9(void);

void setup() ////// Initialisation des entrées/sorties et LCD
{
  pinMode(bpok, INPUT_PULLUP);
  pinMode(bph, INPUT_PULLUP);
  pinMode(bpb, INPUT_PULLUP);
  pinMode(bpback, INPUT_PULLUP);
  pinMode(PRES, OUTPUT);
  pinMode(Pompe1, OUTPUT);
  pinMode(Pompe2, OUTPUT);
  pinMode(LedPompe1, OUTPUT);
  pinMode(LedPompe2, OUTPUT);
  pinMode(LedVerte, OUTPUT);
  pinMode(LedRouge, OUTPUT);
  pinMode(Buzz, OUTPUT);
  digitalWrite(PRES,HIGH);
  digitalWrite(Pompe1,LOW);
  digitalWrite(Pompe2,LOW);
  Serial.begin(9600);
  lcd.init();                     
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Init...");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nb Sensors : ");
  digitalWrite(LedRouge, HIGH);
  
}


void loop() //////////////////////////////////////////Début Boucle Infinie////////////////////////////////// 
{
Mesure1 = analogRead(A0);
Mesure2 = analogRead(A1);
BPOKavant = BPOK;
BPOK = digitalRead(bpok);
BPHavant = BPH;
BPH = digitalRead(bph);
BPBavant = BPB;
BPB = digitalRead(bpb);
BPBACKavant = BPBACK;
BPBACK = digitalRead(bpback);
       BEBUG_TEST(
               Serial.print(Mesure1);
               Serial.print("  ");
               Serial.println(NbSondes);
              );
switch(ietat) /////// Switch de calcul d'état
{
  case 0 :
       if(BPOK < BPOKavant)
       {
        SavingNbSens1();
        ietat = 1;  
       }break;
  case 1 :
       if(BPOK < BPOKavant)
       {
        SavingValS1_1();
        ietat = 2;
       }break;
  case 2 :
       if(BPOK < BPOKavant)
       {
        Aff_Hyst_D1();
        ietat = 3;
        break;
       }
       if(BPBACK < BPBACKavant)
       {
        SavingNbSens1_1();
        ietat = 1;
       }break;
  case 3 :
       if(BPOK < BPOKavant)
       {
        Calc_S2_1();
        ietat = 4;
       }break;
  case 4 :
       if(BPOK < BPOKavant)
       {
        Aff_LevelA1();
        ietat = 5;
        break;
       }
       if(BPBACK < BPBACKavant)
       {
        Aff_Hyst_D1();
        ietat = 3;
       }break;
  case 5 :
       if(BPOK < BPOKavant)
       {
        Saving_SA1();
        ietat = 6;
       }break;
  case 6 :
       if((BPOK < BPOKavant)&&(NbSondes == 1))
       {
        Aff_Val1();
        ietat = 7;
        break;
       }
       if((BPOK < BPOKavant)&&(NbSondes == 2))
       {
        Aff_Val2();
        ietat = 11;
        break;
       }
       if(BPBACK < BPBACKavant)
       {
        Aff_LevelA1();
        ietat = 5;
       }break;
  case 7 :
        if(Mesure1 > SeuilAlerte1)
       {
        HIGH_RETRO();
        Cpt2 = 0;
        Clear_LCD();
        ietat = 9;
        break;
       }
        if( Mesure2 > SeuilAlerte2 && NbSondes == 2 )
       {
        HIGH_RETRO();
        Cpt2 = 0;
        Clear_LCD();
        ietat = 91;
        break;
       }
       if(Mesure1 <= Seuil1_1)
       {
        HIGH_RETRO();
        Cpt2 = 0;
        HIGH_OUT1();
        ietat = 8;
        break;
       }
       if(Mesure2 <= Seuil1_2 && NbSondes == 2 )
       {
        HIGH_RETRO();
        Cpt2 = 0;
        HIGH_OUT2();
        ietat = 81;
        break;
       }
       if(Cpt2 > 300040 || BPOK < BPOKavant)
       {
        HIGH_RETRO();
        Cpt2 = 0;
        ietat = 7;
        break;
       }
        if(Cpt2 > 40)
       {
        LOW_RETRO();
        ietat = 7;
       }break;
  case 8 :
       if(Mesure1 >= Seuil2_1 && NbSondes == 1 )
       {
        Aff_Val1();
        LOW_OUT1();
        ietat = 7;
        break;
       }
        if( Mesure1 >= Seuil2_1 && NbSondes == 2 )
       {
        Aff_Val1_Val2();
        LOW_OUT1();
        ietat = 7;
       }break;
  case 9 :
       if(BPOK < BPOKavant)
       {
        RESET();
       }break;
  case 11 :
       if(BPOK < BPOKavant)
       {
        SavingValS1_2();
        ietat = 21;
       }break;
  case 21 :
       if(BPOK < BPOKavant)
       {
        Aff_Hyst_D2();
        ietat = 31;
        break;
       }
       if(BPBACK < BPBACKavant)
       {
        Aff_Val2();
        ietat = 11;
       }break;
  case 31 :
       if(BPOK < BPOKavant)
       {
        Calc_S2_2();
        ietat = 41;
       }break;
  case 41 :
       if(BPOK < BPOKavant)
       {
        Aff_LevelA2();
        ietat = 51;
        break;
       }
       if(BPBACK < BPBACKavant)
       {
        Aff_Hyst_D2();
        ietat = 31;
       }break;
  case 51 :
       if(BPOK < BPOKavant)
       {
        Saving_SA2();
        ietat = 61;
       }break;
  case 61 :
       if(BPOK < BPOKavant)
       {
        Aff_Val1_Val2();
        ietat = 7;
        break;
       }
       if(BPBACK < BPBACKavant)
       {
        Aff_LevelA2();
        ietat = 51;
       }break;
  case 81 :
       if(Mesure2 >= Seuil2_2)
       {
        Aff_Val1_Val2();
        LOW_OUT2();
        ietat = 7;
       }break;
  case 91 :
       if(BPOK < BPOKavant)
       {
        RESET();
       }break;
}
switch(ietat)  ////// Switch d'écriture sorties
{
  case 0 : CPT_1();
           BlkOK();break;
  case 1 : Aff_Mesure1();break;
  case 2 : BlkOK();break;
  case 3 : CPT_5();
           BlkOK();break;
  case 4 : BlkOK();break;
  case 5 : Aff_Mesure1();break;
  case 6 : BlkOK();break;
  case 7 : 
        if(NbSondes == 1)
        {
          Aff_Mesure1_2();
          Cpt2++;
          break;
        }
        if(NbSondes == 2)
        {
          Aff_Mesure12();
          Cpt2++;
        }break; 
  case 8 : Aff_WATER1();break;
  case 9 : Aff_WATERLEVEL1();break;
  case 11 : Aff_Mesure2();break;
  case 21 : BlkOK();break;
  case 31 : CPT_5();
            BlkOK();break;
  case 41 : BlkOK();break;
  case 51 : Aff_Mesure2();break;
  case 61 : BlkOK();break;
  case 81 : Aff_WATER2();break;
  case 91 : Aff_WATERLEVEL2();break;

}
delay(75);
}///////////////////////////////// Fin de boucle infinie///////////////////////////////

////////////////////////////////Codage des fonctions///////////////////////////////////

void SavingNbSens1(void)
{
  NbSondes = Cpt;
    Cpt = 0;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Value 1 : ");
tone(Buzz,500,50);
}

void SavingNbSens1_1(void)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Value 1 : ");
tone(Buzz,500,50);
}
void Aff_Val2(void)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Value 2 : ");
tone(Buzz,500,50);
}
void SavingValS1_1(void)
{
  Seuil1_1 = Mesure1;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Saved value1: ");
lcd.setCursor(13,0);
lcd.print(Seuil1_1);
tone(Buzz,500,50);

}
void SavingValS1_2(void)
{
  Seuil1_2 = Mesure2;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Saved value2: ");
lcd.setCursor(13,0);
lcd.print(Seuil1_2);
tone(Buzz,500,50);
}
void Aff_Hyst_D1(void)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("HysteresisD1: ");
tone(Buzz,500,50);
Cpt = 0;
}
void Aff_Hyst_D2(void)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("HysteresisD2: ");
tone(Buzz,500,50);
Cpt = 0;
}
void Calc_S2_1(void)
{
Seuil2_1 = Seuil1_1 + Cpt;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("S1:");
lcd.print(Seuil1_1);
lcd.print(" S2:");
lcd.print(Seuil2_1);
tone(Buzz,500,50);

}
void Calc_S2_2(void)
{
Seuil2_2 = Seuil1_2 + Cpt;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("S1:");
lcd.print(Seuil1_2);
lcd.print(" S2:");
lcd.print(Seuil2_2);
tone(Buzz,500,50);

}
void Aff_LevelA1(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Level Alert1:");
  tone(Buzz,500,50);
}
void Aff_LevelA2(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Level Alert2:");
  tone(Buzz,500,50);
}
void Saving_SA1(void)
{
  SeuilAlerte1 = Mesure1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Level Alert1:");
  lcd.print(SeuilAlerte1);
  tone(Buzz,500,50);
}
void Saving_SA2(void)
{
  SeuilAlerte2 = Mesure2;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Level Alert2:");
  lcd.print(SeuilAlerte2);
  tone(Buzz,500,50);
}
void Aff_Val1(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Value 1: ");
  tone(Buzz,500,50);
}
void Aff_Val1_Val2(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Value 1: ");
  lcd.setCursor(0,1);
  lcd.print("Value 2: ");
  tone(Buzz,500,50);
}
void HIGH_OUT1(void)
{
  digitalWrite(Pompe1,HIGH);
  digitalWrite(LedPompe1, HIGH);
  lcd.clear();
  i_B0 = 0;
}
void HIGH_OUT2(void)
{
  digitalWrite(Pompe2,HIGH);
  digitalWrite(LedPompe2, HIGH);
  lcd.clear();
  i_B0 = 0;
}
void Clear_LCD(void)
{
  lcd.clear();
  i_B0 = 0;
}
void LOW_OUT1(void)
{
  digitalWrite(Pompe1,LOW);
  digitalWrite(LedPompe1,LOW);
}
void LOW_OUT2(void)
{
  digitalWrite(Pompe2,LOW);
  digitalWrite(LedPompe2,LOW);
}
void HIGH_RETRO(void)
{
  lcd.backlight();
  tone(Buzz,500,50);
}
void LOW_RETRO(void)
{
  lcd.noBacklight();
  
}


/////////////////////////////////////////////////////////////////////////////////Moore

void Aff_Mesure1(void)
{
  lcd.setCursor(13,0);
  lcd.print("    ");
  lcd.setCursor(13,0);
  lcd.print(Mesure1);
  BlkOK();
  }
 void Aff_Mesure1_2(void)
{
  digitalWrite(LedRouge, LOW);
  digitalWrite(LedVerte, HIGH);
  lcd.setCursor(13,0);
  lcd.print("    ");
  lcd.setCursor(13,0);
  lcd.print(Mesure1);
  }
void Aff_Mesure2(void)
{
  lcd.setCursor(13,0);
  lcd.print("    ");
  lcd.setCursor(13,0);
  lcd.print(Mesure2);
  BlkOK();
  }
void Aff_Mesure12(void)
{
  digitalWrite(LedRouge, LOW);
  digitalWrite(LedVerte, HIGH);
  lcd.setCursor(13,0);
  lcd.print("    ");
  lcd.setCursor(13,0);
  lcd.print(Mesure1);
  lcd.setCursor(13,1);
  lcd.print("    ");
  lcd.setCursor(13,1);
  lcd.print(Mesure2);
}
void Aff_WATER1(void)
{
   if(i_B0 == 0)
  {
  lcd.setCursor(0,0);
  lcd.print(" > WATERING 1 <");
  tone(Buzz,600,100);
  }
  if(i_B0 == 4)
  {
  lcd.clear();  
  }
  if(i_B0 == 8)
  {
    i_B0 = -1;
  }
  i_B0++;
}
void Aff_WATER2(void)
{
   if(i_B0 == 0)
  {
  lcd.setCursor(0,0);
  lcd.print(" >> WATERING 2 <<");
  tone(Buzz,600,100);
  }
  if(i_B0 == 4)
  {
  lcd.clear();  
  }
  if(i_B0 == 8)
  {
    i_B0 = -1;
  }
  i_B0++;
}
void Aff_WATERLEVEL1(void)
{
   digitalWrite(LedVerte, LOW);
   if(i_B0 == 0)
  {
  lcd.setCursor(0,0);
  lcd.print("! WATER LEVEL 1!");
  digitalWrite(LedRouge, HIGH);
  digitalWrite(LedPompe1,HIGH);
  tone(Buzz,900,100);
  }
  if(i_B0 == 4)
  {
  lcd.clear();
  digitalWrite(LedRouge, LOW);
  digitalWrite(LedPompe1,LOW); 
  tone(Buzz,500,100); 
  }
  if(i_B0 == 8)
  {
    i_B0 = -1;
  }
  i_B0++;
}
void Aff_WATERLEVEL2(void)
{
   digitalWrite(LedVerte, LOW);
   if(i_B0 == 0)
  {
  lcd.setCursor(0,0);
  lcd.print("! WATER LEVEL 2!");
  digitalWrite(LedRouge, HIGH);
  digitalWrite(LedPompe2,HIGH);
  tone(Buzz,900,100);
  }
  if(i_B0 == 4)
  {
  lcd.clear();
  digitalWrite(LedRouge, LOW);
  digitalWrite(LedPompe2,LOW);
  tone(Buzz,500,100);   
  }
  if(i_B0 == 8)
  {
    i_B0 = -1;
  }
  i_B0++;
}

///////////////////////////////////////////////////////////////////////

void BlkOK(void)
{
   if(i_B0 == 0)
  {
  lcd.setCursor(3,1);
  lcd.print("PUSH >> OK");
  }
  if(i_B0 == 4)
  {
  lcd.setCursor(10,1);
  lcd.print("    ");    
  }
  if(i_B0 == 8)
  {
    i_B0 = -1;
  }
  i_B0++;
}
void CPT_1(void)
{
  if((BPH < BPHavant)&&(Cpt < 2))
  {
    Cpt = Cpt + 1;
  }
  if((BPB < BPBavant)&&(Cpt > 0))
  {
    Cpt = Cpt - 1;
  }
  lcd.setCursor(13,0);
  lcd.print("  ");
  lcd.setCursor(13,0);
  lcd.print(Cpt);
  
}
void CPT_5(void)
{
  if((BPH < BPHavant)&&(Cpt < 100))
  {
    Cpt = Cpt + 5;
  }
  if((BPB < BPBavant)&&(Cpt > 0))
  {
    Cpt = Cpt - 5;
  }
  lcd.setCursor(13,0);
  lcd.print("  ");
  lcd.setCursor(13,0);
  lcd.print(Cpt);
  
}
void RESET(void)
{
  digitalWrite(PRES,LOW);
}
