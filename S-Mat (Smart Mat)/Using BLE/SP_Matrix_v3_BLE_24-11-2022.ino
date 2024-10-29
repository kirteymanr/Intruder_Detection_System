#include <ArduinoBLE.h>

BLEService step_detect ("19B10010-E8F2-537E-4F6C-D104768A1214");

BLEStringCharacteristic is_step("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify, 24);

bool is_con = 0 ;
//int row[] = {A0, A1, A2, A3, A4, A5, A6}
int Threshold = 450;
int rowNo = 7;
int columnNo = 6;
int row[] = {8, 7, 6, 5, 4, 3, 2} ;//{A0, A1, A2, A3, A4, A5, A6} ; // {5, 4, 3, 2} ;
int column[] = {0, A0, A1, A2, A3, 0 } ; //{A0, A1, A2, A3, A4, A5, A6} ;
//int pinCount = 4 ;
int step_cnt = 0 ;

bool match_1 = 0 ;
bool match_2 = 0 ;

const byte rownum = 7;
const byte columnnum = 6;

int matrix [rownum] [columnnum] = {0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,};

int key_1 [rownum] [columnnum] =  {0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 1, 1, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,};

int key_2 [rownum] [columnnum] =  {0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 1, 1, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,};
                                    
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  for (int rowPin = 0; rowPin < rowNo; rowPin++) {
    pinMode(row[rowPin], OUTPUT);
    //pinMode(column[thisPin], INPUT);
  }

  if (!BLE.begin()) 
  {
      Serial.println("starting Bluetooth® Low Energy module failed!");
      while (1);
  }

  // set the local name peripheral advertises
  BLE.setLocalName("SARVJIT");
  // set the UUID for the service this peripheral advertises:
  BLE.setAdvertisedService(step_detect);

  // add the characteristics to the service
  step_detect.addCharacteristic(is_step);
  //step_detect.addCharacteristic(pressure);

  // add the service
  BLE.addService(step_detect);

//  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
//  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  
  is_step.writeValue(String(0));
  //pressure.writeValue(String(0));

  // start advertising
  BLE.advertise();

  Serial.println("Bluetooth® device active, waiting for connections...");  
  delay(2000);
  Serial.println("Welcome");
/*
  for (int rowPin = 0; rowPin < rowNo; rowPin++)
  {
    digitalWrite( row[rowPin], HIGH ) ;
  }
*/  
}

void loop() {
  // put your main code here, to run repeatedly:

  //BLE.poll();
  //BLE.addService(step_detect);
  BLEDevice central = BLE.central();
  if( ! is_con )
  {
    //Serial.println("- Discovering central device...");
  }
  
  delay(500);

  if (central and ! is_con) {
    //Serial.println("* Connected to central device!");
    //Serial.print("* Device MAC address: ");
    //Serial.println(central.address());
    //Serial.println(" ");
    is_con = 1 ;
  }
  
  is_step.writeValue("0");

  read_mat();
  //print_mat();

  //Serial.print( "With Key 1: ");
  //Serial.println( compareArray(matrix,key_1));
  if(! compareArray(matrix,key_1) )
  {
    match_1 = 1;
    delay(5000);
    read_mat();
    delay(100);
    //print_mat();
    //Serial.print( "With Key 2: ");
    //Serial.println( compareArray(matrix,key_2));
    if(! compareArray(matrix,key_2) )
    {
      match_2 = 1;
      Serial.println("Match Found");
      //Serial.println("************************************************************************************");
      //Serial.println("Match Found");
      //Serial.println("************************************************************************************");
    }
    else;
  }
  else
  {
    //Serial.println("Match Not Found");
  }



  if (match_1 && ! match_2)
  {
    is_step.writeValue("1");
    //BLEDevice central = BLE.central();
    step_cnt ++ ;
    //Serial.println("************************************************************************************");
    Serial.println("Foot Step Detected") ;
    //Serial.println(step_cnt) ;
    //Serial.println("************************************************************************************");
    delay(200);
    //while ( check_nearby(rowPin, columnPin) ) ;
    is_step.writeValue("0");
    match_1 = 0;
  }
  
  if ( match_2 )
  {
    Serial.println("Authentication Successfull");
    is_step.writeValue("2");
    //BLEDevice central = BLE.central();
    delay(10000);
    match_1 = 0;
    match_2 = 0;
  }
  else ;
  
  for( int rowPin = 0; rowPin < rowNo; rowPin++ )
  {
     digitalWrite(row[rowPin], HIGH);
     for (int columnPin = 0; columnPin < columnNo; columnPin++) {
     /*  
       Serial.print(rowPin) ;
       Serial.print(",") ;
       Serial.print(columnPin) ;
       Serial.print(":\t") ;
       Serial.print( digitalRead(column[columnPin]) ) ;
       delay(10) ;
       Serial.print("\t") ;
     */  
     while ( analogRead (column[columnPin]) > Threshold )
       {
          /*
          Serial.print("Current HIGH Pin : ");
          Serial.print(rowPin);
          Serial.print(",");
          Serial.println(columnPin);
          */
          /*
           
          Serial.print ("Pin ");
          Serial.print (rowPin);
          Serial.print (",");
          Serial.print (columnPin - 1);
          Serial.print (" Status : ");
          */
          
          //Serial.print("Checking Around. ");
          //Serial.println (check_nearby(rowPin, columnPin));

          if ( check_nearby(rowPin, columnPin) )
          {
            is_step.writeValue("1");
            BLEDevice central = BLE.central();
            step_cnt ++ ;
            //BLE.poll();
            //temperature.writeValue(String(step_cnt));
            //temperature.writeValue("1");
            //Serial.println("************************************************************************************");
            Serial.println("Foot Step Detected") ;
            //Serial.println(step_cnt) ;
            //Serial.println("************************************************************************************");
            delay(200);
            while ( check_nearby(rowPin, columnPin) ) ;
            is_step.writeValue("0");
          }
          else
          {
            is_step.writeValue("0");
          }
          //temperature.writeValue("0");
       }
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
  //Serial.println("----------------------------------------------------------");
}

int check_nearby(int rowPin, int columnPin)
{
  int status1 = 0, status2 = 0, status3 = 0, status4 = 0 ;

  if( rowPin - 1 > -1 )
  {
    status1 = check_status(rowPin - 1, columnPin);
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

  //else ;

  if ( rowPin + 1 < rowNo )
  {
    status2 = check_status(rowPin + 1, columnPin);
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

  //else ;
  
  if( columnPin - 1 > -1 )
  {
    status3 = check_status(rowPin, columnPin - 1);
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
  
  //else ;
  
  if ( columnPin + 1 < columnNo )
  {
    status4 = check_status(rowPin, columnPin + 1);
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

  //else ;

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
  if( (rowPin > -1) && (columnPin > -1) && (rowPin + 1 < rowNo) && (columnPin + 1 < columnNo) )
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
void blePeripheralConnectHandler(BLEDevice central) {
  // central connected event handler
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
}
*/
