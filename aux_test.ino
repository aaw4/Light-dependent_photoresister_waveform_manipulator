//aux test code
//Square wave
//EECS 388 team


const int aux = 13;
void setup()
{
  pinMode(aux, OUTPUT);
  
}

void loop()
{
  //This will create a 100hz square wave
  digitalWrite(aux, HIGH);
  delay(5); //ms
  digitalWrite(aux, LOW);
  delay(5); //ms
}
