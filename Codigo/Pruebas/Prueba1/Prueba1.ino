//Codigo Dispensador de agua
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0X27,16,2);


#define Arriba 0
#define Abajo 1
#define izquierda 2
#define derecha 3
#define enter 4
#define paro 5

#define RangoSuperrior 200.00
#define RangoInferior 1

#define Digito1  0
#define Digito2  1
#define Digito3  2
#define Decimal1 3
#define Decimal2 4

#define CantidadBotones 6
int PinBotones[CantidadBotones]={3, 6, 7, 9, 10, 11};                                //Pines de los botones 
boolean EstadoBotones[CantidadBotones]= {true, true, true, true, true, true};        //Estado inicial de los botones
boolean EstadoAnteriorBotones[CantidadBotones]={true, true, true, true, true, true}; //Estado Anterior
boolean Curso=true;                                                                  //Cursor

#define CantidadIndicador 5 //Cantidad de digitos a desplazar
int CantidadIndicadorColumna= 5; // Cantidad de columnas
int IndicadoActual =0;   //Posiccion inicial del indicador
int ValorInicial[CantidadIndicador]= {0,0,0,0,0};  //Inicializacion de los digitos 
#define Incremento 1 //incremento del indicador
int RangoIndicador[2][CantidadIndicador]={ {9,9,9,9,9}, {0,0,0,0,0}};//Valor minimo 0 Valor maximo 9
boolean DibujarPantalla= true;

float TiempoPasado;
float FrecuenciaRefresco=50;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  for(int i=0; i< CantidadBotones; i++)
  {
    pinMode(PinBotones[i],INPUT_PULLUP);
  }

}

void loop() {
  ActuaizarBotones();//Actualizar las posiciones de los botones y las acciones
  MostrarPantalla(); //Muestra la pantalla
}

//Rutinas 
void MostrarPantalla()
{
  for(int i = 0 ; i < CantidadIndicador; i++) //Mueve el indicador por las posiciones en un array
  {
    if(ValorIndicador[i] != ValorAnteriorIndicador[i]) //Si el valor actual es diferente a la posicion inicial del boton ( se realiza accion)
    {
      DibujarPantalla = true;
      ValorAnteriorIndicador[i] = ValorIndicador[i]; //Se actualiza indicador
    }
  }

  if (millis()> TimpoPasado + FrecuenciaRefresco) //Tiempo de refresco pantalla
  {
    TiempoPasado=millis(); //corre millis
    if (DibujarPantalla)
    {
      lcd.clear();
      int X=0;
      int Y=0;
      for (int i=0; i<CantidadIndicador; i++)//Pociciona el indicador
      {
        Y=i % CantidadIndicadorColumna;
        X=i < CantidadIndicadorColumna ? 0 : 10;
        lcd.setCursor(X, Y);
        if (Indicadorctual == i && Cursor)
        {
          Serial.print(">");
          lcd.print(">");
        }
        else
        {
          Serial.print(" ");
          lcd.print(" ");
        }
        //Muestra las variables 
        Serial.print(Lable[i]);
        Serial.print(":");
        Serial.print(ValorIndicador[i]);
        lcd.print(Lable[i]);
        lcd.print(":");
        lcd.print(ValorIndicador[i]);

        //Si se PRECIONA ENTER SE COLOCA "<<" INDICA QUE ENTRO AL MENU
        if (IndicadorActual == i && !Cursor)
        {
          Serial.print("<<");
          lcd.print("<<");
        }
        else
        {
            Serial.print(" ");
        }
        Serial.println();
        }
      }
    }
  }
}

void ActuaizarBotones()
{
  //lee el estado de los botones
  for (int i =0; i < CantidadBotones; i++)
  {
    EstadoBotones[i] = digitalRead(PinBotones[i] ==0 ? true: false;
  }
  //
  for (int i =0; i < CantidadBotones; i++)
  {
    if (EstadoBotones[i] != EstadoAnteriorBotones[i])
    {
      EstadoAnteriorBotones[i] = EstadoBotones[i];
    //      Serial.print("Cambio ");
    //      Serial.print(i);
    //      Serial.print( :);
    //      Serial.print(EstadoBotones[i]);
      if (EstadoBotones[i])
      {
        DibujarPantalla=true;
        //Mueve los botones en la pantalla deacuerdo a las columnas del display
        if (Cursor)
        {
          switch (i)
          {
            case Arriba:
              if (IndicadorActual % CantidadIndicadorColumna !=0)
              {
                IndicadrActual--;
              }
            break;
            case Abajo:
               IndicadorActual++;
              if (IndicadorActual % CantidadIndicadorColumna == 0)
              {
                IndicadrActual--;
              }
            break;
            case Derecha:
              if (IndicadorActual <=CantidadIndicadorColumna)
              {
                IndicadorActual += CantdadIndcadorColumna;
              }
            break;
            case Izquierda:
              if (IndicadorActual >= CantidadIndicadorColumna)
              {
                IndicadorActual -= CantidadIndicadorColumna;
              }
            break;
            case Enter:
              Cursor = !Cursor;
            break;
          }
          //Muestra Estado actual
          if (IndicadorActual >= CantiadIndicador)
          {
            IndicadorActual = CantidadIndicador -1 ;
          }
        }
      }
    }
  }
}
