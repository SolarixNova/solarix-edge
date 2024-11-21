#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "Wokwi-GUEST";
const char *password = "";
const char *mqtt_server = "broker.hivemq.com";

WiFiClient WOKWI_Client;
PubSubClient client(WOKWI_Client);

#define DHTPIN 15       
#define DHTTYPE DHT22  
#define LDR_PIN 34      
#define IRRADIACAO_PIN 35 
#define EFICIENCIA_PIN 32 
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup_wifi() {

  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("WiFi Conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {

  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    
    if (client.connect("WOKWI_Client")) {
      Serial.println("Conectado");
    
    } else {
      Serial.print("failed, rc= ");
      Serial.print(client.state());
      Serial.println("Tentando novamente em 5 segundos");

      delay(5000);
    }  
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  dht.begin();

  
  Wire.begin(16, 17);  
  
  lcd.begin(16, 2);
  lcd.backlight();

 
  lcd.setCursor(0, 0);
  lcd.print("Sistema Solar");
  lcd.setCursor(0, 1);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
}

void loop() {
 
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

 
  int luminosidade = analogRead(LDR_PIN);
  int irradiacao = analogRead(IRRADIACAO_PIN);
  int eficiencia = analogRead(EFICIENCIA_PIN);

  
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Erro ao ler DHT22!");
    return;
  }

  
  float irradiacaoValor = map(irradiacao, 0, 4095, 0, 1000); 
  float eficienciaValor = map(eficiencia, 0, 4095, 0, 100);  

  
  float energiaSolar = (irradiacaoValor * eficienciaValor * luminosidade) / 1000.0;

  client.publish("fiap/solarix",String(energiaSolar).c_str());
  
  Serial.println("Energia: " + String(energiaSolar, 2) + "Wh");
  Serial.println("---");

 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Energia: ");
  lcd.print(energiaSolar);
  lcd.print(" Wh");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print("C");

 
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" C, Umidade: ");
  Serial.print(umidade);
  Serial.print(" %, Luminosidade: ");
  Serial.print(luminosidade);
  Serial.print(", Irradiacao: ");
  Serial.print(irradiacaoValor);
  Serial.print(" W/m², Eficiencia: ");
  Serial.print(eficienciaValor);
  Serial.print(" %, Energia: ");
  Serial.print(energiaSolar);
  Serial.println(" Wh");

  reconnect();
  
  delay(2000); 
}
