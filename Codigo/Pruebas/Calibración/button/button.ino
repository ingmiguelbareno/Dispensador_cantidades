// Inicializacion de las variables 

int up_button    =48;
int down_button  =50;
int left_button  =51;
int right_button =49;
int start_button =38;
int stop_button =39;

int up_reading    = 0;
int down_reading  = 0;
int left_reading  = 0;
int right_reading = 0;
int start_reading = 0;
int stop_reading = 0;

void setup() {
  Serial.begin(9600);
  pinMode(up_button,INPUT_PULLUP);
  pinMode(down_button,INPUT_PULLUP);
  pinMode(left_button, INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(start_button, INPUT_PULLUP);
  pinMode(stop_button, INPUT_PULLUP);
}

void loop() {

  up_reading    = digitalRead(up_button);
  down_reading  = digitalRead(down_button);
  left_reading  = digitalRead(left_button);
  right_reading = digitalRead(right_button);
  start_reading = digitalRead(start_button);
  stop_reading = digitalRead(stop_button);

  Serial.print("Arriba: ");
  Serial.print(up_reading);
  Serial.print("  ");
  Serial.print("Abajo: ");
  Serial.print(down_reading);
  Serial.print("  ");
   Serial.print("Izquierda: ");
  Serial.print(left_reading);
  Serial.print("  ");
   Serial.print("Derecha: ");
  Serial.print(right_reading);
  Serial.print("  ");
   Serial.print("START: ");
  Serial.print(start_reading);
  Serial.print("  ");
  Serial.print("STOP: ");
  Serial.print(stop_reading);
  Serial.print("  ");
  Serial.println("");

  delay(400);

  

}
