//motor driver variables for driving wheels
int IN1 = 5;
int IN2 = 6;
int IN3 = 10;
int IN4 = 8;

//define analog ports for enable pins
int ENA = 11;
int ENB = 9;

//define ports for sonar sensors
//left side sensors
int SLT = 2;
int SLE = 3;
//center sensors
int SCT = 4;
int SCE = 7;
//right side sensors
int SRE1 = 13;
int SRT = 12;


//variables for the sonar sensor calculations
float distance;
unsigned long duration;

//for Esp meesaging
String msg;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);

    // Motor Driver pins
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  //pins for sonar trigger and echo
  pinMode(SLT , OUTPUT);
  digitalWrite(SLT, LOW);
  pinMode(SLE , INPUT);

  pinMode(SCT , OUTPUT);
  digitalWrite(SCT, LOW);
  pinMode(SCE , INPUT);

  pinMode(SRT , OUTPUT);
  digitalWrite(SRT, LOW);
  pinMode(SRE1 , INPUT);

  //These Are the commands for the ESP module
    sendSetupCommand("AT+RST");   
  sendSetupCommand("AT+CWMODE=3");
  sendSetupCommand("AT+CWJAP=\"Chamins' zen\",\"123456789\"");   // hotspot user and password
  //sendSetupCommand("AT+CWJAP=\"USER NAME\",\"PASSSWORD\"");
  
  sendSetupCommand("AT+CIPMUX=1");
  sendSetupCommand("AT+CIPSERVER=1,8080");
  //sendSetupCommand("AT+CIPSERVER=1,PORT"); 
}

float sonarLeft(){
    //send signal to trigger  
  digitalWrite( SLT, HIGH );
  
  //delaye for 50 microseconds
  delayMicroseconds(50);

  //then switch off the trigger
  digitalWrite( SLT, LOW );

  //get duartion for echo (returns in microseconds)
  duration = pulseIn( SLE, HIGH );
  
  distance = duration/58.0;

  //print values on monitor
  Serial.print("Left Sonar: ");
  Serial.print(distance);
  Serial.print(" cm\n");
  return distance;
  delay(1000);  
}
float sonarCenter(){
    //send signal to trigger  
  digitalWrite( SCT, HIGH );
  
  //delaye for 50 microseconds
  delayMicroseconds(50);

  //then switch off the trigger
  digitalWrite( SCT, LOW );

  //get duartion for echo (returns in microseconds)
  duration = pulseIn( SCE, HIGH );
  
  distance = duration/58.0;

  //print values on monitor
  Serial.print("Center Sonar: ");
  Serial.print(distance);
  Serial.print(" cm\n");
  return distance;
  delay(1000);  
}
float sonarRight(){
    //send signal to trigger  
  digitalWrite( SRT, HIGH );
  
  //delaye for 50 microseconds
  delayMicroseconds(50);

  //then switch off the trigger
  digitalWrite( SRT, LOW );

  //get duartion for echo (returns in microseconds)
  duration = pulseIn( SRE1, HIGH );
  
  distance = duration/58.0;

  //print values on monitor
  Serial.print("Right Sonar: ");
  Serial.print(distance);
  Serial.print(" cm\n");
  return distance;
  delay(1000);  
}

int count =0;

void loop() {
  // put your main code here, to run repeatedly:

  //ESP Message receiver
    if(Serial1.available()){
    String message=Serial1.readStringUntil('\n');
    Serial.println(message);
    String command=extract(message);
    process(command);
  }
  

  //analogWrite(ENA, 128);

  //Forward(100);
  //Backward(200);
  //TurnLeft(50);
  //TurnRight(50);
  
  //motor1Rotate(100);
  //motor2Rotate(50);
  
  //TurnLeftDouble(100);
  //TurnRightDouble(50);

  //call sonar reading methods
  //sonarLeft();
  //sonarCenter();
  //sonarRight();
  
  //sendData();
}

// sends a specific command to the ESP module
void sendSetupCommand(String command){
  //set wifi mode to access point
  do{
    Serial1.println(command);
    delay(1000);
    msg=receiveData();
  }while(msg.indexOf("OK")==-1);
  Serial.println(msg);
  delay(3000);
}



String extract(String message){
  if(message.indexOf("+IPD")>=0){
    int start=message.indexOf(':');
    if(start<0){
      return "";
    }
    String cmd= message.substring(start+1);
    Serial.println(cmd);
    return cmd;
  }
  return "";
}

//process the received command
void process(String s){
  if(s=="") return;
  for(int i=0; i<s.length(); i++)
  {
    if(s[i] == 'f'){   // forward function
        Serial.println("forward activated");
        Forward(150);
    }
    else if(s[i] == 'b'){  //backward function
        Serial.println("backward activated");
        Backward(150);
    }
    else if(s[i] == 's'){
        Forward(0);
    }
    else if(s[i] == 'l'){   //left turn function 
      Forward(0); 
        TurnLeft(150);
        delay(1000);
        Forward(0);
    }
    else if(s[i] == 'r'){   //right turn function
      Forward(0);
        TurnRight(150);
        delay(1000);
        Forward(0);
    }
      
  }
  sendData();
  // this will call when some data recieved.So sonar data will be send to the local application 
}


void sendData()
{
    
    String data="xxxx";     //sonarRight()+"#"+sonarCenter()+"#"+sonarLeft();
    int ii=0;
     while(1)
     {
      unsigned int l=data.length();
      Serial.print("AT+CIPSEND=0,");
      Serial1.print("AT+CIPSEND=0,");
      Serial.println(l+2);
      Serial1.println(l+2);
      delay(100);
      Serial.println(data);
      Serial1.println(data);
      while(Serial1.available())
      {
        //Serial.print(Serial.read());
        if(Serial1.find("OK"))
        {
          ii=11;
          break;
        }
      }
      if(ii==11)
      break;
      delay(1000);
     }
}

void motor1Rotate(int spd){
  if(spd > 0){
    
    analogWrite(ENA, spd);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }else if(spd == 0){
    analogWrite(ENA, 0);
  }else{
    
    analogWrite(ENA, -1*spd);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
}



void motor2Rotate(int spd){
  if(spd > 0){
     
    analogWrite(ENB, spd);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }else if(spd == 0){
    analogWrite(ENB, 0);
  }else{
    analogWrite(ENB, -1*spd);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
}





void Forward(int spd){
  motor2Rotate(spd);
  motor1Rotate(spd);
  Serial.println("Forward"); 
}

void Backward(int spd){
  motor1Rotate(-1*spd);   
  motor2Rotate(-1*spd);
  Serial.println("Backward"); 
  
}

void TurnLeft(int spd){
  //motor1Rotate(spd-20);   
  motor2Rotate(spd);
  
  Serial.println("Left");
}

void TurnRight(int spd){
  motor1Rotate(spd);   
  //motor2Rotate(spd-20);
  Serial.println("Right");
}


void TurnLeftDouble(int spd){
  motor1Rotate(-1*spd);   
  motor2Rotate(spd);
  Serial.println("Left Double");
}

void TurnRightDouble(int spd){
  motor1Rotate(spd);   
  motor2Rotate(-1*spd);
  Serial.println("Right Double");
}

