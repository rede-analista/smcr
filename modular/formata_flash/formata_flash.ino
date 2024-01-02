#include <Preferences.h>
#include <nvs_flash.h>

/*---- Inicia objetos ----*/
Preferences CONFIG_FLASH;

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("");

  Serial.print("As preferencias estao sendo limpas, todas as configuracoes serão perdidas... ");
  CONFIG_FLASH.begin("confiGeral", false);
  CONFIG_FLASH.clear();
  CONFIG_FLASH.end();
  delay(100);
  Serial.println(" OK");

  Serial.print("Particao NVS sendo formatada, todas as informacoes serão perdidas... ");
  nvs_flash_erase(); //apague a partição NVS
  nvs_flash_init(); //inicializa a partição NVS
  delay(100);
  Serial.println("OK");

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(100);
  digitalWrite(2, LOW);
  delay(1000);
}
