void setup() {

pinMode(LED_BUILTIN, OUTPUT);
Serial.begin(9600);
   }
void loop() {

if (Serial.available()){
  char data;
  data=Serial.read();
  Serial.println(data);

  if (data =='o'){
    digitalWrite(LED_BUILTIN,HIGH);
    delay(2000); 
  }

  else if(data =='c'){
    digitalWrite(LED_BUILTIN  ,LOW);
    delay(2000);
  }
}
  
}
