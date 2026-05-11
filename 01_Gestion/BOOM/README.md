# 🛒 Lista de Materiales (Bill of Materials - BOM)

Este documento detalla todos los componentes electrónicos, electromecánicos, precios y materiales de manufactura necesarios para ensamblar **una (1) unidad** del sistema **LilyGo A — Transmisor LoRa v23** (Sistema de Pesaje Agroindustrial con Motor DC y Comunicación LoRa 915MHz).

> 📄 **Versión Imprimible:** [Descargar BOM Completo en PDF]

***

## ⚡ Electrónica Principal

En esta sección se listan los componentes encargados del procesamiento, comunicación inalámbrica, adquisición de datos y visualización. Estos elementos constituyen el núcleo funcional del sistema, permitiendo el pesaje en décimas de gramo, el control del motor y la transmisión de registros por radio LoRa al LilyGo B.

| Ítem | Componente | Cant. | Referencia / Especificación | Función | Est. Costo (COP) |
| :--- | :--- | :---: | :--- | :--- | :---: |
| 1 | **Microcontrolador + LoRa** | 1 | **LilyGo TTGO LoRa32** ESP32 915MHz (SX1276) | Procesamiento central, WiFi nativo y transmisión LoRa | $ 134.470 |
| 2 | **Pantalla** | 1 | **LCD 16x2** con módulo I2C (PCF8574, dirección 0x27) | Interfaz visual para el operario — muestra nombre, peso y pago | $ 15.000 |
| 3 | **Sensor de Peso** | 1 | **Potenciómetro 10kΩ** lineal (conectado a GPIO35 — ADC 12 bits) | Lectura analógica de peso de 10g a 100g con resolución de 0.1g | $ 1.700 |
| 4 | **Driver Motor** | 1 | **Módulo Puente H L298N** (ENA → GPIO25, IN1 → GPIO15, IN2 → GPIO14) | Control de velocidad PWM y dirección del motor DC | $ 9.940 |
| 5 | **Motor DC** | 1 | Motor DC 5–12V con reductor (velocidad PWM = 130/255) | Mecanismo físico de descarga: gira adelante 1.35s, pausa 10s, vuelve atrás | $ 25.000 |

***

## 🔋 Sistema de Potencia

A continuación se presentan los componentes responsables del suministro y gestión de la energía del sistema. Estos elementos garantizan un funcionamiento estable tanto para la lógica ESP32 como para el motor DC durante la operación en campo.

| Ítem | Componente | Cant. | Referencia / Especificación | Función | Est. Costo (COP) |
| :--- | :--- | :---: | :--- | :--- | :---: |
| 6 | **Fuente de Alimentación** | 1 | Fuente DC regulada 5V–12V / 2A mínimo | Alimentación del sistema completo y motor DC | $ 20.000 |
| 7 | **Cable USB-C** | 1 | Cable USB-C estándar | Programación del LilyGo y carga si se usa batería | $ 5.000 |

***

## 🔘 Interfaz y Control

Esta sección agrupa los elementos de interacción con el operario: botones físicos para navegar entre trabajadores, confirmar pesajes y activar la parada de emergencia con protección anti-ruido por hold time de 400ms.

| Ítem | Componente | Cant. | Referencia / Especificación | Función | Est. Costo (COP) |
| :--- | :--- | :---: | :--- | :--- | :---: |
| 8 | **Botón NOMBRE** | 1 | Pulsador Tact Switch 6x6mm — GPIO32 (INPUT_PULLDOWN) | Cicla entre los trabajadores de la lista | $ 500 |
| 9 | **Botón OK / Confirmar** | 1 | Pulsador Tact Switch 6x6mm — GPIO33 (INPUT_PULLDOWN) | Inicia pesaje y confirma resultados en cada paso del flujo | $ 500 |
| 10 | **Botón STOP / Emergencia** | 1 | Pulsador Tact Switch 6x6mm — GPIO13 (pull-down fuerte vía driver) | Activa emergencia solo si se mantiene presionado ≥ 400ms | $ 500 |
| 11 | **Resistencia Pull-down** | 1 | Resistencia 10kΩ 1/4W (entre GPIO13 y GND) | Previene activaciones falsas por ruido o flotación del pin | $ 200 |

***

## 📡 Conectividad y Comunicación

| Ítem | Componente | Cant. | Referencia / Especificación | Función | Est. Costo (COP) |
| :--- | :--- | :---: | :--- | :--- | :---: |
| 12 | **Antena LoRa 915MHz** | 1 | Antena SMA 915MHz (incluida con LilyGo TTGO LoRa32) | Transmisión inalámbrica del registro de pesaje al LilyGo B | $ 0 (incluida) |
| 13 | **Red WiFi / Hotspot** | 1 | Hotspot móvil (SSID configurado en código) | Descarga de lista de trabajadores desde LilyGo B vía HTTP GET | $ 0 (existente) |

***

## 🛠️ Insumos de Montaje

Esta sección agrupa los materiales necesarios para el ensamblaje físico del sistema, incluyendo la base del circuito y los insumos de soldadura y conexión.

| Ítem | Componente | Cant. | Referencia / Especificación | Función | Est. Costo (COP) |
| :--- | :--- | :---: | :--- | :--- | :---: |
| 14 | **PCB / Protoboard** | 1 | Baquelita universal doble cara o Protoboard 830 puntos | Base del circuito (cortar a medida o usar directamente) | $ 8.000 |
| 15 | **Cables Dupont** | 1 set | Macho-Macho y Macho-Hembra 20cm | Conexiones entre módulos (LilyGo ↔ LCD, L298N, botones) | $ 5.000 |
| 16 | **Varios** | 1 | Estaño 60/40, cautín, cinta aislante, termoencogible | Insumos de montaje, soldadura y aislamiento | $ 8.000 |

***

## 💰 Resumen de Presupuesto

A continuación se presenta un resumen consolidado de los costos estimados por categoría, lo que permite visualizar la distribución del presupuesto total del sistema por unidad.

| Categoría | Subtotal Estimado |
| :--- | :--- |
| Electrónica Principal | $ 186.110 |
| Sistema de Potencia | $ 25.000 |
| Interfaz y Control | $ 1.700 |
| Conectividad | $ 0 |
| Insumos de Montaje | $ 21.000 |
| **TOTAL POR UNIDAD** | **$ 233.810 COP** |

*(Precios estimados en mercado local colombiano — Luloa, Sigma Electrónica, Robótica de Colombia · Mayo 2026)*

***

## 📍 Proveedores Recomendados

A continuación se sugieren proveedores confiables para la adquisición de los componentes, basados en disponibilidad, costo y experiencia previa en proyectos similares:

* **LilyGo TTGO LoRa32 + módulos:** [Luloa](https://luloa.co) (proveedor principal recomendado).
* **LCD 16x2 I2C / Potenciómetros / Resistencias:** Luloa · Sigma Electrónica.
* **Puente H L298N / Motor DC:** Luloa · Robótica de Colombia · MercadoLibre Colombia.
* **Protoboard / Cables Dupont / Insumos:** Luloa · Electrónicas locales Armenia / Pereira.

***
