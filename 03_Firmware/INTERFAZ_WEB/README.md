# ☕ Teleférico del Café — Sistema de Pesaje Agroindustrial

&gt; Sistema embebido de pesaje agroindustrial con transmisión inalámbrica LoRa 915 MHz  
&gt; **Universidad del Quindío** · Ingeniería Electrónica · Semestre 2026-I · Curso CDIO III

---

## 📋 Tabla de Contenidos
- [Descripción](#-descripción)
- [Integrantes](#-integrantes)
- [Arquitectura del Sistema](#-arquitectura-del-sistema)
- [Hardware](#-hardware)
- [Firmware](#-firmware)
- [Interfaz Web (Nodo B)](#-interfaz-web-nodo-b)
- [Documentos del Proyecto](#-documentos-del-proyecto)
- [Bitácoras de Reunión](#-bitácoras-de-reunión)
- [Estado Actual](#-estado-actual)
- [Presupuesto](#-presupuesto)
- [Instalación y Uso](#-instalación-y-uso)

---

## 📝 Descripción

El **Teleférico del Café** es un sistema embebido que automatiza el pesaje del café recolectado por trabajadores en campo. Cada trabajador se identifica en una pantalla LCD, coloca su cosecha en una canastilla, el sistema pesa con resolución de **0.1 g** usando un módulo HX711 + celda de carga de 5 kg, calcula el pago en COP a tarifa de **$1,200 COP/kg**, activa un motor DC que simula el teleférico transportando la canastilla, y transmite el registro completo por radio **LoRa 915 MHz** a un nodo receptor base con interfaz web.

### Flujo de un Ciclo Completo
1. **Selección** — Operario elige su nombre con BTN_NOMBRE (cicla lista descargada vía WiFi)
2. **Pesaje** — Lectura HX711 durante 10 segundos con cuenta regresiva en LCD
3. **Resultado** — Muestra peso (0.1 g) y pago ($COP)
4. **Confirmación** — BTN_OK confirma y activa el motor
5. **Transporte** — Motor gira adelante 1350 ms (duty cycle 130/255)
6. **Depósito** — Pausa 10 s para que el operario deposite el café
7. **Retorno** — Motor retorna atrás 1350 ms
8. **Transmisión** — Envía paquete LoRa: `PESAJE,nombre,peso,pago`

&gt; ⚠️ **Emergencia:** BTN_STOP (GPIO 4, hold 400 ms) detiene el motor inmediatamente desde cualquier estado activo y activa retorno proporcional al tiempo girado.

---

## 👥 Integrantes

| Nombre | Rol | Responsabilidad |
|---|---|---|
| **Erick S. Cruz Silva** | Líder de Proyecto | Firmware v23, arquitectura del sistema |
| **Rohin H. Suarez Gallego** | Hardware | Motor DC, driver L298N, comunicación LoRa |
| **Daniel S. Ruales Cuaran** | Software | Máquina de estados (FSM), integración lógica |
| **Kevin E. Aragon Camacho** | Integración | Pruebas V&V, validación de campo |

**Asesor:** Prof. Jorge Luis Chávez  
**Sustentación final:** 25 de mayo de 2026

---

## 🏗️ Arquitectura del Sistema

### Nodo A — Transmisor (Campo)
- **Microcontrolador:** LilyGo TTGO LoRa32 V2.1 (ESP32 + SX1276)
- **Sensor de peso:** HX711 24 bits + Celda de carga 5 kg
- **Interfaz:** LCD 16×2 I²C (PCF8574, dirección 0x27)
- **Actuador:** Motor DC 5V + Driver L298N (PWM 1 kHz)
- **Controles:** 3 pulsadores (NOMBRE, OK, STOP)
- **Comunicación:** LoRa 915 MHz (SF7, BW 125 kHz, CR 4/5)

### Nodo B — Receptor (Base)
- **Microcontrolador:** LilyGo TTGO LoRa32 V2.1
- **Servidor:** AsyncWebServer (ESPAsyncWebServer) vía WiFi
- **Almacenamiento:** RAM (persistencia en flash pendiente)
- **Endpoints:**
  - `GET /` → Login
  - `GET /panel` → Gestión de trabajadores
  - `GET /sistema` → Dashboard de pesajes en vivo
  - `GET /lista` → JSON lista de nombres (consumido por Nodo A)
  - `GET /datos` → JSON registros de pesajes
  - `GET /reporte` → Descarga TXT con reporte formateado
  - `GET /login?user=&pass=` → Autenticación
  - `GET /agregarTrab?nombre=` → Agregar trabajador
  - `GET /eliminarTrab?id=` → Eliminar trabajador
  - `GET /reiniciar` → Resetear contadores
  - `GET /logout` → Cerrar sesión

---

## 🔧 Hardware

### BOM v23 As-Built

| Componente | Referencia | Cantidad | Costo (COP) |
|---|---|---|---|
| Microcontrolador | LilyGo TTGO LoRa32 V2.1 | 2 | $160,000 |
| Módulo ADC peso | HX711 24 bits | 1 | $8,000 |
| Celda de carga | Strain Gauge 5 kg | 1 | $15,000 |
| Pantalla | LCD 16×2 I²C (PCF8574) | 1 | $15,000 |
| Driver motor | L298N | 1 | $15,000 |
| Motor DC | Motor DC 5V | 1 | $13,000 |
| Botones | Pulsadores 6×6 mm | 3 | $1,500 |
| Resistencias | 10 kΩ (pull-down BTN_STOP) | Varias | $500 |
| Cables y protoboard | — | — | $10,200 |
| Carcasa | Impresión 3D PLA+ | 1 | $13,000 |
| Cables celda | 4 hilos (E+/E-/A+/A-) | 1 | $2,000 |
| Antenas SMA | 915 MHz | 2 | $4,500 |
| **TOTAL** | | | **$257,200** |

&gt; ⚠️ **Nota crítica:** En versiones anteriores se usó un potenciómetro de 10 kΩ como sensor de peso simulado. Esto fue **completamente eliminado y reemplazado** por el módulo HX711 + celda de carga de 5 kg. Cualquier referencia al potenciómetro en documentos antiguos es un error que debe corregirse.

### Mapa de Pines Nodo A (As-Built)

| Componente | Pin Componente | GPIO ESP32 | Función | Protocolo |
|---|---|---|---|---|
| LCD 16×2 | VCC | 3.3V | Alimentación | — |
| LCD 16×2 | GND | GND | Tierra común | — |
| LCD 16×2 | SDA | GPIO 21 | Datos I²C | I²C 100 kHz |
| LCD 16×2 | SCL | GPIO 22 | Reloj I²C | I²C 100 kHz |
| HX711 | DOUT | GPIO 13 | Datos seriales peso | Digital serial |
| HX711 | SCK | GPIO 2 | Reloj serial peso | Digital serial |
| Celda carga | E+ | HX711 E+ | Excitación positiva | — |
| Celda carga | E- | HX711 E- | Excitación negativa | — |
| Celda carga | A+ | HX711 A+ | Señal positiva | — |
| Celda carga | A- | HX711 A- | Señal negativa | — |
| L298N | ENA | GPIO 25 | Velocidad PWM motor | PWM 1 kHz |
| L298N | IN1 | GPIO 15 | Dirección adelante | Digital |
| L298N | IN2 | GPIO 14 | Dirección atrás | Digital |
| BTN_NOMBRE | Pin 1 | GPIO 32 | Cambiar trabajador | INPUT_PULLDOWN |
| BTN_OK | Pin 1 | GPIO 33 | Confirmar pesaje | INPUT_PULLDOWN |
| BTN_STOP | Pin 1 | GPIO 4 | Emergencia (400 ms hold) | Pull-down 10 kΩ externo |
| LoRa SX1276 | SCK | GPIO 5 | Reloj SPI | SPI |
| LoRa SX1276 | MISO | GPIO 19 | Datos SPI | SPI |
| LoRa SX1276 | MOSI | GPIO 27 | Datos SPI | SPI |
| LoRa SX1276 | SS | GPIO 18 | Chip Select | SPI |
| LoRa SX1276 | RST | GPIO 23 | Reset módulo | Digital |
| LoRa SX1276 | DIO0 | GPIO 26 | Interrupción TX/RX | Digital |

&gt; **Nota crítica GPIO13:** Este pin fue originalmente asignado a BTN_STOP, pero como GPIO13 tiene nivel HIGH en el boot del ESP32, causaba activaciones falsas. Fue reasignado al HX711 DOUT (corrección AC-01). BTN_STOP se movió a GPIO4 con `gpio_pulldown_en` + hold 400 ms.

&gt; **Nota GPIO2:** GPIO2 también tiene comportamiento especial en boot (debe estar LOW). El HX711 SCK en GPIO2 funciona correctamente porque el HX711 no envía señal hasta que el firmware lo inicializa.

---

## 💻 Firmware

**Versión actual:** v23 (`LilyGo_A_Transmisor_v23.ino`)  
**Máquina de estados:** 9 estados  
**IDE:** Arduino IDE 2.x + ESP32 Espressif v2.x  
**Serial:** 115,200 baud

### Estados FSM

| Estado | Descripción | Transición |
|---|---|---|
| **ST_ESPERA** | LCD muestra nombre del trabajador activo | BTN_NOMBRE cicla lista; BTN_OK → ST_PESANDO |
| **ST_PESANDO** | Lectura HX711 durante 10 s, LCD muestra peso + cuenta regresiva | Al terminar → ST_RESULTADO |
| **ST_RESULTADO** | Muestra peso (0.1 g) y pago ($COP) | BTN_OK → ST_CONFIRMAR |
| **ST_CONFIRMAR** | Pide confirmación al operario | BTN_OK → ST_MOTOR_A |
| **ST_MOTOR_A** | Motor adelante 1350 ms, registra `tiempoGirado` | Al terminar → ST_MOTOR_PAUSA |
| **ST_MOTOR_PAUSA** | Motor detenido 10 s, operario deposita café | Al terminar → ST_MOTOR_B |
| **ST_MOTOR_B** | Motor atrás 1350 ms, envía paquete LoRa | Al terminar → ST_ESPERA |
| **ST_EMERGENCIA_ESPERA** | Motor detenido, cuenta regresiva 3 s | BTN_STOP liberado → ST_EMERGENCIA_RETORNO |
| **ST_EMERGENCIA_RETORNO** | Motor retorna proporcional a `tiempoGirado` | Al terminar → ST_ESPERA |

&gt; BTN_STOP puede activarse desde **cualquier estado** que tenga el motor activo (ST_MOTOR_A, ST_MOTOR_PAUSA, ST_MOTOR_B) con hold mínimo de 400 ms.

### Ecuaciones de Pesaje
```cpp
raw        = scale.get_units(10);           // promedio 10 muestras, ganancia 128
peso [g]   = roundf(raw * 10.0) / 10.0;   // resolución 0.1 g
pago [COP] = (peso / 1000.0) * 1200.0;    // tarifa $1,200 COP/kg
paquete    = "PESAJE," + nombre + "," + String(peso, 1) + "," + String(pago, 1);
