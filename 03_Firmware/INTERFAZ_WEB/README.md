# ☕ Teleférico del Café — Guía de Instalación y Uso
## Sistema Embebido de Pesaje Agroindustrial con LoRa 915 MHz

El Teleférico del Café es un sistema diseñado para pesar automáticamente el café recolectado por cada trabajador en campo, calcular su pago en COP y transmitir los datos de forma inalámbrica a una base receptora. En esta guía aprenderás paso a paso cómo preparar los dos nodos del sistema (transmisor de campo y receptor base), cómo instalar el firmware y cómo usar la interfaz web para gestionar trabajadores y descargar reportes de pagos.

---

## ¿Qué necesitas?

### Hardware — Nodo A (Transmisor de Campo)

| Componente | Descripción |
|---|---|
| LilyGo TTGO LoRa32 V2.1 | Microcontrolador ESP32 + LoRa SX1276 integrado |
| HX711 24 bits | Módulo ADC para celda de carga |
| Celda de carga 5 kg | Strain gauge barra (E+/E-/A+/A-) |
| LCD 16×2 I²C | Pantalla con PCF8574 (dirección 0x27) |
| L298N | Driver motor DC |
| Motor DC 5V | Transporte de canastilla (simula teleférico) |
| 3 pulsadores 6×6 mm | BTN_NOMBRE, BTN_OK, BTN_STOP |
| Resistencia 10 kΩ | Pull-down externo para BTN_STOP |
| Cables y protoboard | Conexiones |
| Carcasa 3D PLA+ | Protección mecánica |

### Hardware — Nodo B (Receptor Base)

| Componente | Descripción |
|---|---|
| LilyGo TTGO LoRa32 V2.1 | Microcontrolador ESP32 + LoRa SX1276 integrado |
| Antena SMA 915 MHz | Para recepción LoRa |
| Fuente USB-C | Alimentación y programación |

### Conexiones del hardware — Nodo A
