#define BLYNK_TEMPLATE_ID "TMPLE2olxXrP"
#define BLYNK_DEVICE_NAME "Horta"

#define BLYNK_AUTH_TOKEN "olhe o arquivo original"//???
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


#define LIGADA 1
#define DESLIGADA 0
#define PIN_BOMBA 22
#define V_PIN V1
#define LIM_BOMBA 60000

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ESP32-projeto01";
char pass[] = "da2s383jqo7grolJ";

bool bomba_bt;
int  bomba_tempo; 

unsigned long tempo_exec;

BLYNK_WRITE(V_PIN) {
  bomba_bt = param.asInt();
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  pinMode(PIN_BOMBA, OUTPUT);

  Serial.println(bomba_bt);
  tempo_exec = 0;
}

void loop()
{
  Blynk.run();

  if (bomba_bt == LIGADA) {
    LigarBomba();
  }else if(bomba_bt == DESLIGADA) {
    DesligarBomba();
  }
  Serial.println(bomba_bt);
}



void LigarBomba(void){
  digitalWrite(PIN_BOMBA, HIGH);
  Blynk.virtualWrite(V_PIN, 1);
  if(tempo_exec == 0){
    tempo_exec = millis();
  }else if((tempo_exec + LIM_BOMBA) <= millis()){
    DesligarBomba();
    Blynk.syncVirtual(V_PIN);
    tempo_exec = 0;
  }
}

void DesligarBomba(void){
  Blynk.virtualWrite(V_PIN, 0);
  digitalWrite(PIN_BOMBA, LOW);
  
}
