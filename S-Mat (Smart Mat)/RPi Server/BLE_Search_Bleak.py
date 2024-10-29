import asyncio
from bleak import BleakScanner, BleakClient
import sys
import time
import random
import datetime
import telepot


chat_id_list = [ 603890797, 882242057 ]
#chat_id_list = []

#from PyObjC import KeyValueCoding
BLE_MAC = "CC:EF:33:C5:5C:BB"
SERVICE_UUID = "19b10000-e8f2-537e-4f6c-d104768a1214"
CHARACTERISTIC_UUID = "19b10001-e8f2-537e-4f6c-d104768a1214"

def handle(msg):
    global chat_id
    new_chat_id = msg['chat']['id']
    command = msg['text']

    print ("Got Chat ID: %s" % new_chat_id)
    print ("Got command: %s" % command)
    
    if ( command == "/start" ) and ( new_chat_id not in chat_id_list ) :
      chat_id_list.append(new_chat_id)
      bot.sendMessage(new_chat_id, "Welcome to Design for IoT Project.\n You are now added to the group.")
      print(chat_id_list)
      
bot = telepot.Bot('5567383577:AAGo8PNoJWE2s3N4Xts8iFyjd0m83GTFC9g')
bot.message_loop(handle)
#bot.sendMessage(603890797, "IoT Project")
print ("I am listening...")

#for chat_id in chat_id_list :
#  bot.sendMessage(chat_id, "IoT Project")
  
  
async def main():
    devices = await BleakScanner.discover()
    for d in devices:
        print(d)
        d = str(d)
        d = d.split()
        MAC = d[0]
        #print(MAC)
        if MAC == "CC:EF:33:C5:5C:BB:" :
          print("Device Found")
    
    async with BleakClient(BLE_MAC) as BLE_client:
    
        svcs = await BLE_client.get_services()
        print("Services:")
        for service in svcs:
            print(service)
        for chat_id in chat_id_list :
          bot.sendMessage(chat_id, "Welcome to Design for IoT Project")
  
        while ( True ) :
          
         # try :
          
            RX_DATA = await BLE_client.read_gatt_char("19B10011-E8F2-537E-4F6C-D104768A1214")
            RX_DATA = RX_DATA.decode()
            print(RX_DATA)
            
            if RX_DATA == "1" :
              
              for chat_id in chat_id_list :
                bot.sendMessage(chat_id, "Intruder Detected at Door Step")
              
              print("Intruder Detected at door step")
            
            elif RX_DATA == "2" :
              
              for chat_id in chat_id_list :
                bot.sendMessage(chat_id, "Authentication Successful")
              
              print("Authentication Successful")
          
          #except KeyboardInterrupt :
          #  BLE_client.disconnect()
          #  print("Keyboard Interrrupt. BLE Disconnected")
          #  break
 #       if KeyValueCoding.getKey(d.details,'name') == 'SARVJIT':
 #           myDevice = d
 #           print('Found it')

asyncio.run(main())