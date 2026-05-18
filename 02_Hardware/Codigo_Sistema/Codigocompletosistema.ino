// ============================================================
// LILYGO A — TRANSMISOR LoRa v23
// BTN_STOP GPIO13 · Anti-ruido por hold time obligatorio
// ============================================================

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "driver/gpio.h"

const char* WIFI_SSID    = "iPhone de Erick Santiago";
const char* WIFI_PASS    = "1007163935";
const char* LILYGO_B_URL = "http://172.20.10.5";

#define PIN_POT      35
#define MOTOR_ENA    25
#define MOTOR_IN1    15
#define MOTOR_IN2    14
#define BTN_NOMBRE   32
#define BTN_OK       33
#define BTN_STOP     13

#define LORA_SCK   5
#define LORA_MISO  19
#define LORA_MOSI  27
#define LORA_SS    18
#define LORA_RST   23
#define LORA_DIO0  26
#define LORA_BAND  915E6

#define LCD_ADDR  0x27
#define LCD_COLS  16
#define LCD_ROWS  2

#define PAGO_POR_KG         1200.0
#define T_PESAJE_MS         10000UL
#define PWM_FREQ            1000
#define PWM_BITS            8
#define VELOCIDAD           140
#define T_MOTOR_MS          1500UL
#define T_PAUSA_MS          10000UL
#define T_ESPERA_EMERGENCIA 3000UL
#define DEBOUNCE_MS         250
#define MAX_TRAB            15
#define BTN_STOP_HOLD_MS    400UL

String trabajadores[MAX_TRAB];
int numTrab = 0;
int trabajadorActual = 0;
const char* respaldo[]   = { "Erick", "Oscar", "Yunicua" };
const int   NUM_RESPALDO = 3;

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

enum Estado {
  ST_ESPERA, ST_PESANDO, ST_RESULTADO, ST_CONFIRMAR,
  ST_MOTOR_A, ST_MOTOR_PAUSA, ST_MOTOR_B,
  ST_EMERGENCIA_ESPERA, ST_EMERGENCIA_RETORNO
};
Estado estadoActual = ST_ESPERA;

float pesoG=0, pagoTotal=0, pesoConfirmado=0, pagoConfirmado=0;
unsigned long timerPesaje=0, timerMotor=0, ultimoSeg=9999;
unsigned long tiempoGirado=0, timerEmergencia=0, timerRetorno=0;
unsigned long db1=0, db2=0, db3=0;

unsigned long btnStopPresionadoDesde = 0;
bool          btnStopActivo          = false;

// ★ FUNCIÓN CORREGIDA — redondeo a décimas (0.1g)
float leerPeso() {
  int adc = analogRead(PIN_POT);
  float pesoRaw = 10.0 + ((float)adc / 4095.0) * 90.0;
  return roundf(pesoRaw * 10.0) / 10.0;  // ← Redondea a 0.1g
}

void mostrarPagoCOP(float pago) {
  lcd.print("$");
  lcd.print(pago, 3);
  lcd.print(" COP");
}

void motorStop();
void mostrarInicio();
void mostrarResultado();
void iniciarMotorA();
void iniciarMotorB();
void activarEmergencia();
void iniciarRetornoEmergencia();
void enviarLoRa(const char*, float, float);
void lcdCuentaRegresiva(const char*, unsigned long);
void usarRespaldo();

bool leerBtnStop() {
  bool presionado = (digitalRead(BTN_STOP) == HIGH);
  if (presionado) {
    if (!btnStopActivo) {
      btnStopActivo          = true;
      btnStopPresionadoDesde = millis();
    } else {
      if ((millis() - btnStopPresionadoDesde) >= BTN_STOP_HOLD_MS) {
        btnStopActivo          = false;
        btnStopPresionadoDesde = 0;
        return true;
      }
    }
  } else {
    btnStopActivo          = false;
    btnStopPresionadoDesde = 0;
  }
  return false;
}

void usarRespaldo() {
  numTrab = NUM_RESPALDO;
  for (int i = 0; i < NUM_RESPALDO; i++) trabajadores[i] = respaldo[i];
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Sin WiFi B");
  lcd.setCursor(0, 1); lcd.print("Usando respaldo");
  delay(1500);
}

void descargarTrabajadores() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Descargando...");
  lcd.setCursor(0, 1); lcd.print("lista WiFi");
  HTTPClient http;
  http.begin(String(LILYGO_B_URL) + "/lista");
  int code = http.GET();
  if (code == 200) {
    String payload = http.getString();
    StaticJsonDocument<512> doc;
    if (!deserializeJson(doc, payload)) {
      numTrab = 0;
      for (JsonVariant v : doc.as<JsonArray>()) {
        if (numTrab < MAX_TRAB) trabajadores[numTrab++] = v.as<String>();
      }
      if (numTrab == 0) { usarRespaldo(); }
      else {
        lcd.clear();
        lcd.setCursor(0, 0); lcd.print("Lista OK!");
        lcd.setCursor(0, 1); lcd.print(numTrab); lcd.print(" trab");
        delay(1500);
      }
    } else { usarRespaldo(); }
  } else { usarRespaldo(); }
  http.end();
}

void setup() {
  Serial.begin(115200);
  delay(500);

  gpio_pulldown_en(GPIO_NUM_13);
  gpio_pullup_dis(GPIO_NUM_13);
  pinMode(BTN_STOP, INPUT);

  pinMode(PIN_POT,    INPUT);
  pinMode(BTN_NOMBRE, INPUT_PULLDOWN);
  pinMode(BTN_OK,     INPUT_PULLDOWN);
  pinMode(MOTOR_IN1,  OUTPUT);
  pinMode(MOTOR_IN2,  OUTPUT);
  motorStop();
  ledcAttach(MOTOR_ENA, PWM_FREQ, PWM_BITS);
  ledcWrite(MOTOR_ENA, 0);

  lcd.init(); lcd.backlight();
  lcd.clear(); lcd.setCursor(0, 0); lcd.print("Iniciando v23...");

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  pinMode(LORA_SS, OUTPUT);
  digitalWrite(LORA_SS, HIGH);
  delay(200);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  int loraIntentos = 0;
  while (!LoRa.begin(LORA_BAND) && loraIntentos < 5) {
    Serial.println("LoRa reintentando...");
    delay(500); loraIntentos++;
  }
  if (loraIntentos >= 5) {
    lcd.clear(); lcd.setCursor(0, 0); lcd.print("LoRa ERROR!");
    while (true);
  }
  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  Serial.println("LoRa OK 915MHz");

  lcd.clear(); lcd.setCursor(0, 0); lcd.print("Conectando WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  int intentos = 0;
  while (WiFi.status() != WL_CONNECTED && intentos < 40) {
    delay(500); intentos++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi OK: " + WiFi.localIP().toString());
    descargarTrabajadores();
  } else {
    Serial.println("WiFi no disponible");
    usarRespaldo();
  }

  btnStopActivo          = false;
  btnStopPresionadoDesde = 0;

  lcd.clear(); lcd.setCursor(0, 0); lcd.print("Sistema listo");
  lcd.setCursor(0, 1); lcd.print("v23 OK");
  delay(1500);
  mostrarInicio();
}

void loop() {
  if (estadoActual != ST_EMERGENCIA_ESPERA &&
      estadoActual != ST_EMERGENCIA_RETORNO) {
    if (leerBtnStop()) {
      activarEmergencia();
      return;
    }
  }

  switch (estadoActual) {

    case ST_ESPERA:
      if (digitalRead(BTN_NOMBRE) == HIGH && millis() - db1 > DEBOUNCE_MS) {
        db1 = millis();
        trabajadorActual = (trabajadorActual + 1) % numTrab;
        mostrarInicio();
      }
      if (digitalRead(BTN_OK) == HIGH && millis() - db2 > DEBOUNCE_MS) {
        db2 = millis(); pesoG = 0;
        timerPesaje = millis(); ultimoSeg = 9999;
        estadoActual = ST_PESANDO;
        lcd.clear();
        lcd.setCursor(0, 0); lcd.print(trabajadores[trabajadorActual]);
        lcd.setCursor(0, 1); lcd.print("Pesando 10s...");
      }
      break;

    case ST_PESANDO: {
      unsigned long tr = millis() - timerPesaje;
      unsigned long re = (tr < T_PESAJE_MS) ? (T_PESAJE_MS - tr) / 1000 : 0;
      pesoG = leerPeso();  // ← Ya viene redondeado a 0.1g
      if (re != ultimoSeg) {
        ultimoSeg = re;
        lcd.setCursor(0, 1); lcd.print("                "); lcd.setCursor(0, 1);
        if (re > 0) {
          lcd.print(pesoG, 1); lcd.print("g "); lcd.print(re); lcd.print("s");
        } else {
          pagoTotal = (pesoG / 1000.0) * PAGO_POR_KG;
          Serial.print("Peso: "); Serial.print(pesoG, 1);
          Serial.print("g Pago: $"); Serial.println(pagoTotal, 3);
          estadoActual = ST_RESULTADO;
          mostrarResultado();
        }
      }
      break;
    }

    case ST_RESULTADO:
      if (digitalRead(BTN_OK) == HIGH && millis() - db2 > DEBOUNCE_MS) {
        db2 = millis();
        pesoConfirmado = pesoG; pagoConfirmado = pagoTotal;
        estadoActual = ST_CONFIRMAR;
        lcd.clear();
        lcd.setCursor(0, 0); lcd.print(pesoConfirmado, 1); lcd.print("g");
        lcd.setCursor(0, 1); lcd.print("[OK] Confirmar?");
      }
      break;

    case ST_CONFIRMAR:
      if (digitalRead(BTN_OK) == HIGH && millis() - db2 > DEBOUNCE_MS) {
        db2 = millis();
        Serial.print("CONFIRMADO "); Serial.print(trabajadores[trabajadorActual]);
        Serial.print(" "); Serial.print(pesoConfirmado, 1);
        Serial.print("g $"); Serial.println(pagoConfirmado, 3);
        iniciarMotorA();
      }
      break;

    case ST_MOTOR_A:
      lcdCuentaRegresiva("Adelante", T_MOTOR_MS);
      tiempoGirado = millis() - timerMotor;
      if (millis() - timerMotor >= T_MOTOR_MS) {
        motorStop();
        estadoActual = ST_MOTOR_PAUSA;
        timerMotor = millis(); ultimoSeg = 9999;
        lcd.clear(); lcd.setCursor(0, 0); lcd.print("Motor: PAUSA");
      }
      break;

    case ST_MOTOR_PAUSA:
      lcdCuentaRegresiva("Pausa", T_PAUSA_MS);
      if (millis() - timerMotor >= T_PAUSA_MS) iniciarMotorB();
      break;

    case ST_MOTOR_B:
      lcdCuentaRegresiva("Atras", T_MOTOR_MS);
      if (millis() - timerMotor >= T_MOTOR_MS) {
        motorStop();
        enviarLoRa(trabajadores[trabajadorActual].c_str(), pesoConfirmado, pagoConfirmado);
        tiempoGirado = 0;
        estadoActual = ST_ESPERA; ultimoSeg = 9999;
        mostrarInicio();
      }
      break;

    case ST_EMERGENCIA_ESPERA: {
      unsigned long tr = millis() - timerEmergencia;
      unsigned long re = (tr < T_ESPERA_EMERGENCIA) ? (T_ESPERA_EMERGENCIA - tr) / 1000 : 0;
      if (re != ultimoSeg) {
        ultimoSeg = re;
        lcd.setCursor(0, 1); lcd.print("                ");
        lcd.setCursor(0, 1); lcd.print("Vuelve en "); lcd.print(re + 1); lcd.print("s...");
      }
      if (tr >= T_ESPERA_EMERGENCIA) {
        if (tiempoGirado > 0) iniciarRetornoEmergencia();
        else { estadoActual = ST_ESPERA; ultimoSeg = 9999; mostrarInicio(); }
      }
      break;
    }

    case ST_EMERGENCIA_RETORNO: {
      unsigned long tr = millis() - timerRetorno;
      unsigned long re = (tr < tiempoGirado) ? (tiempoGirado - tr) / 1000 : 0;
      if (re != ultimoSeg) {
        ultimoSeg = re;
        lcd.setCursor(0, 1); lcd.print("                ");
        lcd.setCursor(0, 1); lcd.print("Volviendo "); lcd.print(re); lcd.print("s...");
      }
      if (tr >= tiempoGirado) {
        motorStop();
        tiempoGirado = 0;
        estadoActual = ST_ESPERA; ultimoSeg = 9999;
        lcd.clear(); lcd.setCursor(0, 0); lcd.print("Motor en origen");
        lcd.setCursor(0, 1); lcd.print("Sistema listo");
        delay(2000); mostrarInicio();
      }
      break;
    }
  }
}

void enviarLoRa(const char* nombre, float peso, float pago) {
  String p = "PESAJE,";
  p += nombre; p += ",";
  p += String(peso, 1); p += ",";   // ← 1 decimal
  p += String(pago, 3);
  LoRa.beginPacket(); LoRa.print(p); LoRa.endPacket();
  Serial.println("LoRa TX: " + p);
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Datos enviados!");
  lcd.setCursor(0, 1); lcd.print("$"); lcd.print(pago, 3); lcd.print(" COP");
  delay(2000);
}

void iniciarMotorA() {
  tiempoGirado = 0;
  estadoActual = ST_MOTOR_A; timerMotor = millis(); ultimoSeg = 9999;
  ledcWrite(MOTOR_ENA, 0);
  digitalWrite(MOTOR_IN1, LOW); digitalWrite(MOTOR_IN2, LOW); delay(200);
  digitalWrite(MOTOR_IN1, LOW); digitalWrite(MOTOR_IN2, HIGH);
  ledcWrite(MOTOR_ENA, VELOCIDAD);
  lcd.clear(); lcd.setCursor(0, 0); lcd.print("Motor ADELANTE");
  Serial.println("Motor ADELANTE");
}

void iniciarMotorB() {
  estadoActual = ST_MOTOR_B; timerMotor = millis(); ultimoSeg = 9999;
  ledcWrite(MOTOR_ENA, 0);
  digitalWrite(MOTOR_IN1, LOW); digitalWrite(MOTOR_IN2, LOW); delay(200);
  digitalWrite(MOTOR_IN1, HIGH); digitalWrite(MOTOR_IN2, LOW);
  ledcWrite(MOTOR_ENA, VELOCIDAD);
  lcd.clear(); lcd.setCursor(0, 0); lcd.print("Motor ATRAS");
  Serial.println("Motor ATRAS");
}

void motorStop() {
  ledcWrite(MOTOR_ENA, 0);
  digitalWrite(MOTOR_IN1, LOW); digitalWrite(MOTOR_IN2, LOW);
}

void activarEmergencia() {
  if (estadoActual == ST_MOTOR_A) {
    tiempoGirado = millis() - timerMotor;
  } else {
    tiempoGirado = 0;
  }
  motorStop();
  lcd.clear(); lcd.setCursor(0, 0); lcd.print("** EMERGENCIA **");
  lcd.setCursor(0, 1); lcd.print("Frenando...");
  estadoActual = ST_EMERGENCIA_ESPERA;
  timerEmergencia = millis(); ultimoSeg = 9999;
  Serial.print("Emergencia! ms: "); Serial.println(tiempoGirado);
}

void iniciarRetornoEmergencia() {
  estadoActual = ST_EMERGENCIA_RETORNO; timerRetorno = millis(); ultimoSeg = 9999;
  ledcWrite(MOTOR_ENA, 0);
  digitalWrite(MOTOR_IN1, LOW); digitalWrite(MOTOR_IN2, LOW); delay(200);
  digitalWrite(MOTOR_IN1, HIGH); digitalWrite(MOTOR_IN2, LOW);
  ledcWrite(MOTOR_ENA, VELOCIDAD);
  lcd.clear(); lcd.setCursor(0, 0); lcd.print("Volviendo...");
  Serial.print("Retornando: "); Serial.print(tiempoGirado); Serial.println("ms");
}

void mostrarResultado() {
  lcd.clear(); lcd.setCursor(0, 0); lcd.print(trabajadores[trabajadorActual]);
  lcd.setCursor(0, 1); lcd.print(pesoG, 1); lcd.print("g");  // ← 1 decimal
  delay(2500);
  lcd.clear(); lcd.setCursor(0, 0);
  mostrarPagoCOP(pagoTotal);
  lcd.setCursor(0, 1); lcd.print("[OK] continuar");
}

void mostrarInicio() {
  lcd.clear(); lcd.setCursor(0, 0); lcd.print(trabajadores[trabajadorActual]);
  lcd.setCursor(0, 1); lcd.print("Listo  [BTN2]");
}

void lcdCuentaRegresiva(const char* label, unsigned long dur) {
  unsigned long tr = millis() - timerMotor;
  unsigned long re = (tr < dur) ? (dur - tr) / 1000 : 0;
  if (re != ultimoSeg) {
    ultimoSeg = re;
    lcd.setCursor(0, 1); lcd.print("                ");
    lcd.setCursor(0, 1); lcd.print(label); lcd.print(" "); lcd.print(re); lcd.print("s");
  }
}