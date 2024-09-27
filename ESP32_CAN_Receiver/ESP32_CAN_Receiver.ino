#include <CAN.h>

#define TX_GPIO_NUM 21
#define RX_GPIO_NUM 22

int printmode = 0;
int ledwrite[3] = {0};

void setup() 
{
  Serial.begin(115200);
  CANinit();
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(32, OUTPUT);
}

void loop() 
{
  if (printmode == 1)
  {
    for (int i = 0; i < 3; i++)
    {
      Serial.print(ledwrite[i]);
      Serial.print("  ");
    }
    Serial.println();
    printmode = 0;
  }

  digitalWrite(14, ledwrite[0]);
  digitalWrite(27, ledwrite[1]);
  digitalWrite(32, ledwrite[2]);
}

void onReceive(int packetSize)
{
  int packetId = CAN.packetId();
  
  if (1)
  {
    int p = 0;
    if (CAN.available()) 
    {
      p = CAN.read();  // Read a single byte from CAN bus
    }

    printmode = 1;
    int index = packetId - 0x14;  // Calculate index for ledwrite array
    ledwrite[index] = p;
  }
}

void CANinit()
{
  Serial.println("CAN Receiver");

  CAN.setPins(RX_GPIO_NUM, TX_GPIO_NUM);

  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  CAN.onReceive(onReceive);
}
