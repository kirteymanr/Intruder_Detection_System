#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>


const char* ssid = "Sarvjit";
const char* password = "999999999";

String msg;

#define BOTtoken "5567383577:AAGo8PNoJWE2s3N4Xts8iFyjd0m83GTFC9g"  // your Bot Token (Get from Botfather)

#define CHAT_ID "603890797" //My Chat ID
//#define CHAT_ID "5872773767"  //Ma'am Chat ID

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


bool is_con = 0 ;
//int row[] = {A0, A1, A2, A3, A4, A5, A6}U

int Threshold = 600;

int rowNo = 7;
int columnNo = 6;
//int row[] = { 26, 25, 33, 32, 35, 34, 39} ;//{A0, A1, A2, A3, A4, A5, A6} ; // {5, 4, 3, 2} ;
//int column[] = {0, 13, 12, 14, 27, 0 } ; //{A0, A1, A2, A3, A4, A5, A6} ;
int row[] = { 4, 16, 17, 5, 18, 3, 15 } ;//{A0, A1, A2, A3, A4, A5, A6} ; // {5, 4, 3, 2} ;
int column[] = {0, 39, 34, 35, 32, 0 } ; //{A0, A1, A2, A3, A4, A5, A6} ;

const int IND_LED = 2 ;
//int pinCount = 4 ;
int step_cnt = 0 ;

bool match_1 = 0 ;
bool match_2 = 0 ;

const byte rownum = 7;
const byte columnnum = 6;

int matrix [rownum] [columnnum] =  {0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,};

int key_1 [rownum] [columnnum] =   {0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 1, 1, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,};

int key_2 [rownum] [columnnum] =   {0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 1, 1, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,};

/*
int key_1 [rownum] [columnnum] =   {1, 0, 0, 0, 0, 1,
                                    1, 0, 0, 0, 0, 1,
                                    1, 0, 1, 1, 0, 1,
                                    1, 0, 0, 0, 0, 1,
                                    1, 0, 0, 0, 0, 1,
                                    1, 0, 0, 0, 0, 1,
                                    1, 0, 0, 0, 0, 1,};

int key_2 [rownum] [columnnum] =   {1, 0, 0, 0, 0, 1,
                                    1, 0, 0, 0, 0, 1,
                                    1, 0, 0, 0, 0, 1,
                                    1, 0, 0, 0, 0, 1,
                                    1, 0, 1, 1, 0, 1,
                                    1, 0, 0, 0, 0, 1,
                                    1, 0, 0, 0, 0, 1,};
*/                                   
                                    
void setup() {
  // put your setup code here, to run once:
  btStop();
  Serial.begin(115200);
  for (int rowPin = 0; rowPin < rowNo; rowPin++) {
    pinMode(row[rowPin], OUTPUT);
    //pinMode(column[thisPin], INPUT);
  }
  pinMode(IND_LED, OUTPUT);

  digitalWrite(IND_LED, LOW);
/////////WiFi///////////////

  // set the local name peripheral advertises

  Serial.println("Welcome");

    // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
     digitalWrite(IND_LED, HIGH);
     delay(300);
     digitalWrite(IND_LED, LOW);
     delay(300);
  }

  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "*********************************************\n*                                                                          *\n*    Welcome to Design for IoT Systems.    *\n*            Intrusion Detection System             *\n*            by KIRTEYMAN & SARVJIT              *\n*                                                                          *\n*********************************************", "");
  
  digitalWrite(IND_LED, LOW);
  delay(300);
  digitalWrite(IND_LED, HIGH);
  delay(1000);
  digitalWrite(IND_LED, LOW);
/*
  for (int rowPin = 0; rowPin < rowNo; rowPin++)
  {
    digitalWrite( row[rowPin], HIGH ) ;
  }
*/  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  WiFi.mode(WIFI_OFF);
  delay(500);
  read_mat();
  print_mat();
  //delay(500);
  delay(50);
  Serial.print( "With Key 1: ");
  Serial.println( compareArray(matrix,key_1));
  if(! compareArray(matrix,key_1) )
  {
    match_1 = 1;
    digitalWrite(IND_LED, HIGH);
    //delay(300);
    
    delay(3000);
    read_mat();
    digitalWrite(IND_LED, LOW);
    delay(100);
    //print_mat();
    Serial.print( "With Key 2: ");
    Serial.println( compareArray(matrix,key_2));
    if(! compareArray(matrix,key_2) )
    {
      match_2 = 1;
      Serial.println("************************************************************************************");
      Serial.println("Match Found");
      Serial.println("************************************************************************************");

      Serial.println("Authentication Successfull");
      
      digitalWrite(IND_LED, HIGH);
      delay(300);
      digitalWrite(IND_LED, LOW);
      delay(300);
      digitalWrite(IND_LED, HIGH);
      delay(300);
      digitalWrite(IND_LED, LOW);
      delay(300);
      digitalWrite(IND_LED, HIGH);
      delay(300);
      digitalWrite(IND_LED, LOW);

      //WiFi.mode(WIFI_ON);
      //delay(2000);
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) 
      {
        Serial.print(".");
        digitalWrite(IND_LED, HIGH);
        delay(300);
        digitalWrite(IND_LED, LOW);
        delay(300);
      }
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      
      msg = "Authentication Successfull";
      bot.sendMessage(CHAT_ID, msg, "");
      
      digitalWrite(IND_LED, LOW);
      delay(300);
      digitalWrite(IND_LED, HIGH);
      delay(1000);
      digitalWrite(IND_LED, LOW);
      
      WiFi.mode(WIFI_OFF);
      
      //delay(300);
      delay(8000);
      match_1 = 0;
      match_2 = 0;
    }
    else
    {
      step_cnt ++ ;
      Serial.println("************************************************************************************");
      Serial.print("Foot Step Detected : ") ;
      Serial.println(step_cnt) ;
      Serial.println("************************************************************************************");

      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) 
      {
        Serial.print(".");
        digitalWrite(IND_LED, HIGH);
        delay(300);
        digitalWrite(IND_LED, LOW);
        delay(300);;
      }
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      
      msg = "Intruder Detected at Door Step";
      bot.sendMessage(CHAT_ID, msg, "");

      digitalWrite(IND_LED, LOW);
      delay(300);
      digitalWrite(IND_LED, HIGH);
      delay(1000);
      digitalWrite(IND_LED, LOW);
      
      WiFi.mode(WIFI_OFF);
      //delay(2000);
      //while ( check_nearby(rowPin, columnPin) ) ;
      match_1 = 0;
      
    }
  }
  else
  {
    Serial.println("Match Not Found");
  
  

  
    for( int rowPin = 0; rowPin < rowNo; rowPin++ )
    {
       digitalWrite(row[rowPin], HIGH);
       for (int columnPin = 1; columnPin < columnNo - 1; columnPin++) {
         if ( columnPin == 0 || columnPin == 5 )
         {
          break;
         }
         Serial.print(rowPin) ;
         Serial.print(",") ;
         Serial.print(columnPin) ;
         Serial.print(":\t") ;
         Serial.print( digitalRead(column[columnPin]) ) ;
         delay(10) ;
         Serial.print("\t") ;
         
       while ( analogRead (column[columnPin]) > Threshold )
         {
            
            Serial.print("Current HIGH Pin : ");
            Serial.print(rowPin);
            Serial.print(",");
            Serial.println(columnPin);
            
            
             
            Serial.print ("Pin ");
            Serial.print (rowPin);
            Serial.print (",");
            Serial.print (columnPin - 1);
            Serial.print (" Status : ");
            
            
            //Serial.print("Checking Around. ");
            //Serial.println (check_nearby(rowPin, columnPin));
  
            if ( check_nearby(rowPin, columnPin) )
            {
              step_cnt ++ ;
              Serial.println("************************************************************************************");
              Serial.print("Foot Step Detected : ") ;
              Serial.println(step_cnt) ;
              Serial.println("************************************************************************************");

              WiFi.mode(WIFI_STA);
              WiFi.begin(ssid, password);
              while (WiFi.status() != WL_CONNECTED) 
              {
                Serial.print(".");
                digitalWrite(IND_LED, HIGH);
                delay(300);
                digitalWrite(IND_LED, LOW);
                delay(300);
              }
              Serial.println("");
              Serial.println("WiFi connected");
              Serial.print("IP address: ");
              Serial.println(WiFi.localIP());
      
              msg = "Intruder Detected at Door Step";
      
              bot.sendMessage(CHAT_ID, msg, "");
              
              digitalWrite(IND_LED, LOW);
              delay(300);
              digitalWrite(IND_LED, HIGH);
              delay(1000);
              digitalWrite(IND_LED, LOW);
              
              //delay(2000);
              
              WiFi.mode(WIFI_OFF);
              
              while ( check_nearby(rowPin, columnPin) ) ;
            }
            else
            {
              Serial.println();
            }
         }
       }
       
      digitalWrite(row[0], LOW);
      digitalWrite(row[1], LOW);
      digitalWrite(row[2], LOW);
      digitalWrite(row[3], LOW);
      digitalWrite(row[4], LOW);
      digitalWrite(row[5], LOW);
      digitalWrite(row[6], LOW);
       
      Serial.println();
    }
  } 
    Serial.println("----------------------------------------------------------");
}

int check_nearby(int rowPin, int columnPin)
{
  int status1 = 0, status2 = 0, status3 = 0, status4 = 0 ;

  if( (rowPin - 1) > -1 )
  {
    status1 = check_status( (rowPin - 1) , columnPin);
    /*
    Serial.print ("Pin ");
    Serial.print (rowPin - 1);
    Serial.print (",");
    Serial.print (columnPin);
    Serial.print (" Status : ");
    Serial.println (status1);
    */
    digitalWrite(row[0], LOW);
    digitalWrite(row[1], LOW);
    digitalWrite(row[2], LOW);
    digitalWrite(row[3], LOW);
    digitalWrite(row[4], LOW);
    digitalWrite(row[5], LOW);
    digitalWrite(row[6], LOW);
  }

  else status1 = 0;


  if ( (rowPin + 1) < (rowNo + 1) )
  {
    status2 = check_status( (rowPin + 1) , columnPin);
    /*
    Serial.print ("Pin ");
    Serial.print (rowPin + 1);
    Serial.print (",");
    Serial.print (columnPin);
    Serial.print (" Status : ");
    Serial.println (status2);
    */
    digitalWrite(row[0], LOW);
    digitalWrite(row[1], LOW);
    digitalWrite(row[2], LOW);
    digitalWrite(row[3], LOW);
    digitalWrite(row[4], LOW);
    digitalWrite(row[5], LOW);
    digitalWrite(row[6], LOW);
  }

  else status2 = 0;

  
  if( columnPin - 1 > -1 )
  {
    status3 = check_status(rowPin, (columnPin - 1) );
    /*
    Serial.print ("Pin ");
    Serial.print (rowPin);
    Serial.print (",");
    Serial.print (columnPin - 1);
    Serial.print (" Status : ");
    Serial.println (status3);
    */
    digitalWrite(row[0], LOW);
    digitalWrite(row[1], LOW);
    digitalWrite(row[2], LOW);
    digitalWrite(row[3], LOW);
    digitalWrite(row[4], LOW);
    digitalWrite(row[5], LOW);
    digitalWrite(row[6], LOW);
  }
  
  else status3 = 0;

  
  if ( (columnPin + 1) < columnNo )
  {
    status4 = check_status(rowPin, (columnPin + 1) );
    /*
    Serial.print ("Pin ");
    Serial.print (rowPin);
    Serial.print (",");
    Serial.print (columnPin + 1);
    Serial.print (" Status : ");
    Serial.println (status4);
    */
    digitalWrite(row[0], LOW);
    digitalWrite(row[1], LOW);
    digitalWrite(row[2], LOW);
    digitalWrite(row[3], LOW);
    digitalWrite(row[4], LOW);
    digitalWrite(row[5], LOW);
    digitalWrite(row[6], LOW);
  }

  else status4 = 0;

  //digitalWrite(row[rowPin], HIGH);
  //int pinStatus = digitalRead(column[columnPin]);
  
    digitalWrite(row[0], LOW);  
    digitalWrite(row[1], LOW);
    digitalWrite(row[2], LOW);
    digitalWrite(row[3], LOW);
    digitalWrite(row[4], LOW);
    digitalWrite(row[5], LOW);
    digitalWrite(row[6], LOW);
  return (status1 || status2 || status3 || status4);
}

int check_status(int rowPin, int columnPin)
{
  int pinStatus = 0 ;
  if( (rowPin > -1) && (columnPin > 0) && ( (rowPin + 1) < (rowNo + 1)) && ( columnPin  < columnNo ) )
  {
    digitalWrite(row[0], LOW);
    digitalWrite(row[1], LOW);
    digitalWrite(row[2], LOW);
    digitalWrite(row[3], LOW);
    digitalWrite(row[4], LOW);
    digitalWrite(row[5], LOW);
    digitalWrite(row[6], LOW);
    
    delay(100);
    digitalWrite(row[rowPin], HIGH);
    pinStatus = ( analogRead(column[columnPin]) > Threshold ) ;
    delay(100);
    
    digitalWrite(row[0], LOW);
    digitalWrite(row[1], LOW);
    digitalWrite(row[2], LOW);
    digitalWrite(row[3], LOW);
    digitalWrite(row[4], LOW);
    digitalWrite(row[5], LOW);
    digitalWrite(row[6], LOW);

    
    /*
    Serial.print ("Pin ");
    Serial.print (rowPin);
    Serial.print (",");
    Serial.print (columnPin);
    Serial.print (" Status : ");
    Serial.println (pinStatus);
    */
  }
  else  
    pinStatus = 0 ;
  delay(20);
  return (pinStatus) ;
}


int compareArray(int a[rownum][columnnum],int b[rownum][columnnum])  {
  int i,j;
  for(i=0;i<rownum;i++){
    for(j=0; j<columnnum;j++){
    if(a[i][j]!=b[i][j])
      return 1;
    }
  }
  return 0;
}

void read_mat()
{
    for( int rowPin = 0; rowPin < rownum; rowPin++ )
    {
       digitalWrite(row[rowPin], HIGH);
       
       for (int columnPin = 0; columnPin < columnnum; columnPin++) {
        /* 
         Serial.print(rowPin) ;
         Serial.print(",") ;
         Serial.print(columnPin) ;
         Serial.print(":\t") ;
         Serial.print( analogRead(column[columnPin]) > Threshold ) ;
         Serial.print("\t") ;
        */ 
         matrix [rowPin] [columnPin] = analogRead(column[columnPin]) > Threshold ;
         delay(10) ;
  
         
         //Serial.print("\t") ;
         
       /*
       if ( digitalRead (column[columnPin]) )
         {
            Serial.print("Current HIGH Pin : ");
            Serial.print(rowPin);
            Serial.print(",");
            Serial.println(columnPin);
            
            //Serial.print ("Pin ");
            //Serial.print (rowPin);
            //Serial.print (",");
            //Serial.print (columnPin - 1);
            //Serial.print (" Status : ");
            //Serial.println("Checking Around. ");
            //Serial.println (check_nearby(rowPin, columnPin));
         }
         */
       }
       digitalWrite(row[0], LOW);
       digitalWrite(row[1], LOW);
       digitalWrite(row[2], LOW);
       digitalWrite(row[3], LOW);
       digitalWrite(row[4], LOW);
       digitalWrite(row[5], LOW);
       digitalWrite(row[6], LOW);

       
       //Serial.println();
    }

       for( int rowPin = 0; rowPin < rownum; rowPin++ )
       {         
          matrix [rowPin] [0] = 0 ;
         delay(10) ;
       }
       
       for( int rowPin = 0; rowPin < rownum; rowPin++ )
       {
         matrix [rowPin] [5] = 0 ;
         delay(10) ;
       }
}

void print_mat()
{
  for( int rowPin = 0; rowPin < rownum; rowPin++ )
  {
     for (int columnPin = 0; columnPin < columnnum; columnPin++)
     {
        Serial.print( matrix [rowPin] [columnPin] ) ;
        Serial.print("  ");
     }
    
     Serial.println();
     //Serial.println("----------------------------------------------------------");
  }
}

/*
int auth()
{
  read_mat();
  print_mat();
  delay(500);
  Serial.print( "With Key 1: ");
  Serial.println( compareArray(matrix,key_1));
  if(! compareArray(matrix,key_1) )
  {
    match_1 = 1;
    delay(5000);
    read_mat();
    delay(100);
    //print_mat();
    Serial.print( "With Key 2: ");
    Serial.println( compareArray(matrix,key_2));
    if(! compareArray(matrix,key_2) )
    {
      match_2 = 1;
      Serial.println("************************************************************************************");
      Serial.println("Match Found");
      Serial.println("************************************************************************************");
      return 1 ;
    }
    else return 0;
  }
  else
  {
    Serial.println("Match Not Found");
    return 0;
  }
  return 0;
}
*/
