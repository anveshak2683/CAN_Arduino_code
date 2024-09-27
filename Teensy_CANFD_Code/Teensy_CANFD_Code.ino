#include <FlexCAN_T4.h>
#include <TeensyThreads.h>

FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_16> FD;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

IntervalTimer timer, timer2;
int SILENT = 9;
bool msgid_ctr = true;
uint8_t buffer_mem[100];
Threads::Mutex mylock;
volatile uint8_t count;

uint8_t a=0;
void setup(void) {

  
  can2.begin();
  can2.setBaudRate(500000);
  pinMode(SILENT,OUTPUT); 

  digitalWrite(SILENT,LOW);
  
  FD.begin();
  CANFD_timings_t config;
  config.clock = CLK_24MHz;
  config.baudrate =   500000;     // 500kbps Nominal data rate
  config.baudrateFD = 1000000;    // 2000kpbs Data rate
  config.propdelay = 190;
  config.bus_length = 1;
  config.sample = 75;
  FD.setRegions(64);
  FD.setBaudRate(config);


  FD.setMBFilter(ACCEPT_ALL);
  FD.setMBFilter(MB13, 0x1);
  FD.setMBFilter(MB12, 0x1, 0x3);
  FD.setMBFilterRange(MB8, 0x1, 0x04);
  FD.enableMBInterrupt(MB8);
  FD.enableMBInterrupt(MB12);
  FD.enableMBInterrupt(MB13);
  FD.enhanceFilter(MB8);
  FD.enhanceFilter(MB10);
  FD.distribute();
  FD.mailboxStatus();
  //timer2.begin(read_msg ,50000);
  timer.begin(sendframe, 1000000); // Send frame every 100ms
  //timer2.begin(sendframecan1,1000000);
  threads.addThread(recvframecan2);
}
void recvframecan2()
{
   CAN_message_t msg1;
   while(1)
   {
      if ( can2.read(msg1) ) {
        canSniff(msg1);
      }
   }
}

void canSniff(const CAN_message_t &msg) {
  Serial.print("MB "); Serial.print(msg.mb);
  Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
  Serial.print("  LEN: "); Serial.print(msg.len);
  Serial.print(" EXT: "); Serial.print(msg.flags.extended);
  Serial.print(" TS: "); Serial.print(msg.timestamp);
  Serial.print(" ID: "); Serial.print(msg.id, HEX);
  Serial.print(" Buffer: ");
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.print(msg.buf[i], HEX); Serial.print(" ");
  } Serial.println();
}

void sendframe()
{

  CANFD_message_t msg;
  msg.len = 8;           // Set frame length to 64 bytes
  if(msgid_ctr == true)
  {
    msg.id = 0x321;
    msg.flags.extended = 0;
  }
  else
  {
    msg.id = 0x12345678;
    msg.flags.extended = 1;
  }
  msg.seq = 1;
  msg.buf[0] = a++;       // Pot 1 value
  msg.buf[1] = 0;
  msg.buf[2] = 0;
  msg.buf[3] = 04;
  msg.buf[4] = 0;  // SW1 value
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;
  FD.write( msg);
  msgid_ctr = !msgid_ctr;
 
}
void loop() {
  CANFD_message_t msg;
  FD.events();
  if (FD.readMB(msg))
  {
    
      Serial.print("MB: "); Serial.print(msg.mb);
      Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
      Serial.print("  ID: 0x"); Serial.print(msg.id, HEX );
      Serial.print("  EXT: "); Serial.print(msg.flags.extended );
      Serial.print("  LEN: "); Serial.print(msg.len);
      Serial.print("  BRS: "); Serial.print(msg.brs);
      Serial.print(" DATA: ");
      
      mylock.lock();
      for ( uint8_t i = 0; i <msg.len ; i++ ) {
          Serial.print(msg.buf[i]); Serial.print(" ");
          buffer_mem[i] = msg.buf[i];     
      }
      mylock.unlock();

      if(msg.id == 0x123)
      {
        Serial.print("From Joystick");
      }
      else
      {
        Serial.print("From Int8 Topic");
      }
      count = (count+1) % msg.len;
      Serial.print("  TS: "); Serial.println(msg.timestamp);
    
  }
 

}
