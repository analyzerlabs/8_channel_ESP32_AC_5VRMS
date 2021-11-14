#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "asd.h"
#include "variables.h"
#include <SPI.h>
BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;
char *dataDecoded;
char *dataRecieved;


#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setPot(){ 
  for(int i =0; i<4;i++){
    digitalWrite(15, LOW);
    SPI.transfer(i);
    SPI.transfer(voltage[i]*32);
    digitalWrite(15, HIGH);
    Serial.println(voltage[i]*32);
  }
  for(int i =4; i<8;i++){
  digitalWrite(16, LOW);
  SPI.transfer(i-4);
  SPI.transfer(voltage[i]*32);
  digitalWrite(16, HIGH);
  }
}

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      char aux[30];
      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++){
          Serial.print(rxValue[i]);
          aux[i]= rxValue[i];
        
        }
        dataRecieved = &aux[0];
       dataDecoded = changeValues(dataRecieved);
        Serial.print("\tData Decoded: ");
        Serial.println(dataDecoded);
        Serial.println("*********"); 
        setPot();
      }
    }
};

int timing = 0;

void setup() {
  Serial.begin(115200);
  SPI.setFrequency(4000000);
  SPI.begin(18,19,23,5);
  pinMode(15,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(2,OUTPUT);
 
  // Create the BLE Device
  BLEDevice::init("8 CANALES");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY
                  );
                      
  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
                       CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
  timing = millis();
}

void loop() {
  
  if( sineWave_step> 360 ){
      sineWave_step=0;
      }
    sineWave_step ++;
    //dacWrite(25,100);
    //dacWrite(25,SineValues[sineWave_step]);
    dacWrite(25, 128 + int(128*sin(sineWave_step*PI/180)) );
    
    
    if (deviceConnected) {
        pTxCharacteristic->setValue(&txValue, 1);
        pTxCharacteristic->notify();
        txValue++;
    delay(10); // bluetooth stack will go into congestion, if too many packets are sent
  }

    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
    // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}



