/**
 * A Mirf example to test the latency between two Ardunio.
 *
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 *
 * Note: To see best case latency comment out all Serial.println
 * statements not displaying the result and load 
 * 'ping_server_interupt' on the server.
 */

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#define LEDPin 13

void setup(){
  Serial.begin(9600);
  
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);  //Turn on the nRF24L01
  delay(6000);


  /*
   * Setup pins / SPI.
   */
   
  /* To change CE / CSN Pins:
   * 
   * Mirf.csnPin = 9;
   * Mirf.cePin = 7;
   */
  
  Mirf.cePin = 9;
  Mirf.csnPin = 10;
  
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  /*
   * Configure reciving address.
   */
   
  Mirf.setRADDR((byte *)"clie1");
  
  /*
   * Set the payload length to sizeof(unsigned long) the
   * return type of millis().
   *
   * NB: payload on client and server must be the same.
   */
   
  Mirf.payload = sizeof(unsigned long);
  Mirf.channel = 8;
  
  /*
   * Write channel and payload config then power up reciver.
   */
   
  /*
   * To change channel:
   * 
   * Mirf.channel = 10;
   *
   * NB: Make sure channel is legal in your area.
   */
   
  Mirf.config();
     // Set 1Mbps data rate
//   Mirf.configRegister(RF_SETUP,0x06);

    //Mirf.configRegister(RF_SETUP, 0b00100110);
    //Mirf.configRegister(SETUP_RETR, 0b00011111);


   
  Serial.println("Beginning ... "); 
}

void loop(){
  unsigned long time = millis();
  
  Mirf.setTADDR((byte *)"serv1");

  pinMode(LEDPin,OUTPUT);
  digitalWrite(LEDPin,HIGH);
 
  Mirf.send((byte *)&time);
  
  while(Mirf.isSending()){
  }
 
 digitalWrite(LEDPin,LOW);
 
  Serial.println("Finished sending");
  delay(10);

  while(!Mirf.dataReady()){
    //Serial.println("Waiting");
    if ( ( millis() - time ) > 1000 ) {
      Serial.println("Timeout on response from server!");
      return;
    }
  }
  
  Mirf.getData((byte *) &time);


  
  Serial.print("Ping: ");
  Serial.println((millis() - time));

  
  delay(1000);
} 
  
  
  
