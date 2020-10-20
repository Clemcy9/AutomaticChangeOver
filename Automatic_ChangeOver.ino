//changeOver relay variables
int RL1, RL2;

//engine kick starter relay
int RL3,RL4;

//nepa and gen sensor pin
int genSensor, nepaSensor;

bool checkStartEngine(){
  if(digitalRead(genSensor)){
    return true;
  }else{
    return false;
  }
}

bool checkNepa(){
  if(digitalRead(nepaSensor)){
    return true;
  }else{
    return false;
  }
}

bool startEngine(){
  int kickTimes =0;
  Serial.println("Starting Engine");
  digitalWrite(RL3,HIGH); //turns key to on position
  delay(2000);
  crank: digitalWrite(RL4,HIGH); //crank engine
  kickTimes++;
  delay(5000);
  digitalWrite(RL4,LOW);
  if(!checkStartEngine()){
    if(kickTimes<3){
      goto crank;
    }else if(kickTimes>3){
      Serial.println("Unable to start Engine");
      return false;
    }
  }else if(checkStartEngine()){
    Serial.println("Engine Started");
    return true;
  }
  
}

bool stopEngine(){
  digitalWrite(RL3,LOW); //turn key to off position
  if(!checkStartEngine()){
    Serial.println("Engine has been turned off");
    return true;
  }else{
    return false;
  }
}

void changeOver(int source){
  if(source==1){
    Serial.println("Changing over to Gen");
    digitalWrite(RL1,LOW); //normally closed state of the relay
    digitalWrite(RL2,LOW);
  }else if(source == 2){
    Serial.println("Changing over to Nepa");
    digitalWrite(RL1,HIGH);
    digitalWrite(RL2,HIGH);
  }
}

void autoFunction(){
  if(checkNepa()){
    if(checkStartEngine()){
      stopEngine();
    }
    changeOver(2); //change over to nepa
  }else{
    delay(30000); //wait for 30 secs
    startEngine();
    delay(30000);
    changeOver(1); //change over to nepa
  }
  
}
void setup() {
  // put your setup code here, to run once:
  changeOver(1); //changeOver to gen at first
}

void loop() {
  // put your main code here, to run repeatedly:

} 
