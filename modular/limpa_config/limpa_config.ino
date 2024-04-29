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
      CONFIG_FLASH.remove("paS_InterMod");
      CONFIG_FLASH.remove("paU16_InterMod");
      CONFIG_FLASH.remove("paB_InterMod");
      CONFIG_FLASH.remove("bits_proc");
      CONFIG_FLASH.remove("cicl_samp");

      CONFIG_FLASH.remove("paS8_Pinos");
      CONFIG_FLASH.remove("paU16_Pinos");

      CONFIG_FLASH.remove("paU16_Acao1");
      CONFIG_FLASH.remove("paU16_AcaoRede1");
      CONFIG_FLASH.remove("paS8_Acao1");
      CONFIG_FLASH.remove("paU16_Acao2");
      CONFIG_FLASH.remove("paU16_AcaoRede2");
      CONFIG_FLASH.remove("paS8_Acao2");
      CONFIG_FLASH.remove("paU16_Acao3");
      CONFIG_FLASH.remove("paU16_AcaoRede3");
      CONFIG_FLASH.remove("paS8_Acao3");
  CONFIG_FLASH.end();
  delay(100);
  Serial.println(" OK");


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
