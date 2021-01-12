bool lightOn = false;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  // make the pushbutton's pin an input:
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  float fCoord = 0.0;
  // print out the state of the button:
  if(Serial.available())
  {
    char c ;
    c = Serial.read();
    Serial.print(c);
    if (c)
    {
      if(c == 'X')
      {
        fCoord = Serial.parseFloat(SKIP_ALL);//Get the floating point number for X 
        Serial.println(fCoord);
        lightOn = true;
      }
      else if(c == 'Z')
      {
        lightOn = false;
      }
      c = NULL;
    }
  }
  if(lightOn)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    //Serial.println("on");
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    //Serial.println("off");
  }
  delay(1000);        // delay in between reads for stability
}