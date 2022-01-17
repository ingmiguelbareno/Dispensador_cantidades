/*
 * El programa muestra a travez del puerto serial la cantidad de pulsos, para encontrar la
 * constante k es necesario realizar varias mediciones de pulsos con volumenes distintos y 
 * tabuarlos en el archivo excel, para promediarlo
 */

volatile long NumPulso; 
//Variable para a cantidad de pulsos recibidos 
int PinSensor =2;       //Sensor conectado al pin 2

//Funcion de interrupcion 
void ContarPulsos ()
{
  NumPulsos++; //Imcremento de la variable pulsos
}

void setup() {
  Serial.begin(9600); 
  pinMode(PinSensor, INPUT); 
  attachInterrupt(0,ContarPulsos,RISING);//(Interrupción 0(Pin2),función,Flanco de subida)
  interrupts();    //Habilitamos las interrupciones
}

void loop() {
  //-----Enviamos por el puerto serie---------------
  Serial.print ("Numero de Pulsos = "); 
  Serial.println (NumPulsos); 
  delay(100);

}
