//Codigo Dispensador de agua
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3F,16,2);  //

//Estados 
#define S_D1    0
#define S_D2    1
#define S_D3    2
#define S_D4    3
#define S_D5    4
#define S_start 5
#define S_stop  6

uint8_t state = S_D1 ;//Estado Actual, inicializado en el primer digito 

//variables 

int relay = 10;//variable rele

uint8_t d1 =0;
uint8_t d2 =0;
uint8_t d3 =0;
uint8_t d4 =0;
uint8_t d5 =0;

float set        = 000.00;
float count      = 000.00;
int   incremento = 0;


//Botones    
#define BTN_UP    0
#define BTN_DOWN  1
#define BTN_LEFT  2
#define BTN_RIGHT 3

#define BTN_GREEN 4
#define BTN_RED   5

#define C_Button 6

uint8_t pin_Button   [C_Button] = {44, 46, 48, 50, 38, 39};  
boolean button_State [C_Button] ; //Ultimo estado conocido de los botones

uint8_t rising_Edge(int btn)
{
  uint8_t d_Read = digitalRead(pin_Button[btn]);
  uint8_t result= button_State[btn] != d_Read && d_Read == 1;
  button_State[btn] = d_Read;
  return result;
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  for(int i=0; i< C_Button; i++)
    {
    pinMode(pin_Button[i],INPUT_PULLUP);
    }

  for(int i=0; i< C_Button; i++)
    {
    button_State[i] = HIGH;
    }

    pinMode(relay,OUTPUT);

//VALIDACION EPROM
}//void setup()

/////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  printHome();

     if(rising_Edge(BTN_GREEN))
      {
        state=S_start;
      }
 
  switch(state)
  {
    case S_D1:////////////////////
      if(rising_Edge(BTN_LEFT))
      {
        state=S_D2;
        break;
      }
      
      if(rising_Edge(BTN_RIGHT))
      {
        state=S_D5;
        break;
      }

      if(rising_Edge(BTN_UP))
      {
        if(d1<9)
        {
        d1++;
        }
        else
        {
        d1=0;
        }
        break;
      }

      if(rising_Edge(BTN_DOWN))
      {
        if(d1>0)
        {
        d1--;
        }
        else
        {
        d1=9;
        }
        break;
      }
    break;//case S_D1

    case S_D2:////////////////////
      if(rising_Edge(BTN_LEFT))
      {
        state=S_D3;
        break;
      }
      
      if(rising_Edge(BTN_RIGHT))
      {
        state=S_D1;
        break;
      }

      if(rising_Edge(BTN_UP))
      {
        if(d2<9)
        {
        d2++;
        }
        else
        {
        d2=0;
        }
        break;
      }

      if(rising_Edge(BTN_DOWN))
      {
        if(d2>0)
        {
        d2--;
        }
        else
        {
        d2=9;
        }
        break;
      }
    break;//case S_D2

    case S_D3:////////////////////
      if(rising_Edge(BTN_LEFT))
      {
        state=S_D4;
        break;
      }
      
      if(rising_Edge(BTN_RIGHT))
      {
        state=S_D2;
        break;
      }

      if(rising_Edge(BTN_UP))
      {
        if(d3<9)
        {
        d3++;
        }
        else
        {
        d3=0;
        }
        break;
      }

      if(rising_Edge(BTN_DOWN))
      {
        if(d3>0)
        {
        d3--;
        }
        else
        {
        d3=9;
        }
        break;
      }
    break;//case S_D3

    case S_D4:////////////////////
    if(rising_Edge(BTN_LEFT))
      {
        state=S_D5;
        break;
      }
      
      if(rising_Edge(BTN_RIGHT))
      {
        state=S_D3;
        break;
      }

      if(rising_Edge(BTN_UP))
      {
        if(d4<9)
        {
        d4++;
        }
        else
        {
        d4=0;
        }
        break;
      }

      if(rising_Edge(BTN_DOWN))
      {
        if(d4>0)
        {
        d4--;
        }
        else
        {
        d4=9;
        }
        break;
      }
    break;//case S_D4
    
    case S_D5:////////////////////
    if(rising_Edge(BTN_LEFT))
      {
        state=S_D1;
        break;
      }
      
      if(rising_Edge(BTN_RIGHT))
      {
        state=S_D4;
        break;
      }

      if(rising_Edge(BTN_UP))
      {
        if(d5<9)
        {
        d5++;
        }
        else
        {
        d5=0;
        }
        break;
      }

      if(rising_Edge(BTN_DOWN))
      {
        if(d5>0)
        {
        d5--;
        }
        else
        {
        d5=9;
        }
        break;
      }
    break;//case S_D5

    case S_start:////////////////////
     if (count<set)
     {
      do 
      {
      contador();
      printHome();
      }
      while(count < set);
     }
     else
     {
      state=S_D1;
      break;
      
     }
    break;//case S_start

    case S_stop:////////////////////
    break;//case S_stop
  }//switch case

}//void loop
/////////////////////////////////////////////////////////////////////////////////////////////

//Funcion dibujar 
void printHome()
{
  lcd.clear();
  lcd.setCursor(0,0);
   
  lcd.print("Variable:");
  lcd.setCursor(0,1);
  lcd.print("Actual:");

  lcd.setCursor(10,0);
  lcd.print(d1);
  lcd.print(d2);
  lcd.print(d3);
  lcd.print(".");
  lcd.print(d4);
  lcd.print(d5);
  
 
  set=(d1*100)+(d2*10)+(d3)+(d4*0.1)+(d5*0.01);
  lcd.setCursor(10,1);
  lcd.print(count);

    switch(state)//Blink
  {
    case S_D1:
    lcd.setCursor(10,0);
    lcd.blink();
    break;
    case S_D2:
    lcd.setCursor(11,0);
    lcd.blink();
    break;
    case S_D3:
    lcd.setCursor(12,0);
    lcd.blink();
    break;
    case S_D4:
    lcd.setCursor(14,0);
    lcd.blink();
    break;
    case S_D5:
    lcd.setCursor(15,0);
    lcd.blink();
    break;
    case S_start:
    lcd.noBlink();
    break;
    case S_stop:
    lcd.noBlink();
    break;
  }

  delay(100);  
}

void contador()
{
  incremento++;
  count=count+(incremento*0.01);
}
