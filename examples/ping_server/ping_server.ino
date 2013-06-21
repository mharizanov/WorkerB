/**
 * An Mirf example which copies back the data it recives.
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
 */

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

void setup(){
  Serial.begin(9600);
  
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW); //Turn on the nRF24L01
  delay(6000);
  
  Mirf.cePin = 9;
  Mirf.csnPin = 10;
  
  /*
   * Set the SPI Driver.
   */

  Mirf.spi = &MirfHardwareSpi;
  
  /*
   * Setup pins / SPI.
   */
   
  Mirf.init();
  
  /*
   * Configure reciving address.
   */
   
  Mirf.setRADDR((byte *)"serv1");
  
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
   
   
  Mirf.config();
  
     // Set 1Mbps data rate
 //  Mirf.configRegister(RF_SETUP,0x06);
   
    //Mirf.configRegister(RF_SETUP, 0b00100110);                                
    //Mirf.configRegister(SETUP_RETR, 0b01011111);


  Serial.println("Listening..."); 
}

void loop(){
  /*
   * A buffer to store the data.
   */
   
  byte data[Mirf.payload];
  
  /*
   * If a packet has been recived.
   *
   * isSending also restores listening mode when it 
   * transitions from true to false.
   */
   
  if(!Mirf.isSending() && Mirf.dataReady()){
    Serial.println("Got packet");
  
    
    /*
     * Get load the packet into the buffer.
     */
     
    Mirf.getData(data);
    
    /*
     * Set the send address.
     */
     
     
    Mirf.setTADDR((byte *)"clie1");
    
    /*
     * Send the data back to the client.
     */
    
    unsigned long time=*(unsigned long*) data;
    
    Serial.println(time);
    
    Mirf.send(data);
    
    /*
     * Wait untill sending has finished
     *
     * NB: isSending returns the chip to receving after returning true.
     */
      
   pinMode(13,OUTPUT);
   digitalWrite(13,HIGH);
   delay(50);
   digitalWrite(13,LOW);
 
    Serial.println("Reply sent.");
  }
}
