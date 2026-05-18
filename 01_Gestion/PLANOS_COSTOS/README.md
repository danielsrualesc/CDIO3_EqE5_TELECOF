# Proyecto CDIOIII Teleferico del Cafe

Sistema embebido de pesaje agroindustrial para la automatizacion del registro de cosecha de cafe en campo, desarrollado por estudiantes de Ingenieria Electronica de la Universidad del Quindio.

---

## Resultados de Diseno -- Planos As-Built y Auditoria de Costos

**Proyecto:** Teleferico del Cafe | **Version:** 1.0 | **Fecha:** 2026-05-18

---

### 1. Esquematico Electronico (As-Built)

#### Mapa de Conexiones Confirmado (Nodo A -- Transmisor)

| Componente | Pin | ESP32 (LilyGo TTGO) | Funcion | Protocolo |
|---|---|---|---|---|
| **HX711** | VCC | 3.3V | Alimentacion ADC | -- |
| **HX711** | GND | GND | Tierra comun | -- |
| **HX711** | DOUT | GPIO 13 | Datos seriales peso | Digital serial |
| **HX711** | SCK | GPIO 2 | Reloj serial peso | Digital serial |
| **Celda carga** | E+ | HX711 E+ | Excitacion positiva | -- |
| **Celda carga** | E- | HX711 E- | Excitacion negativa | -- |
| **Celda carga** | A+ | HX711 A+ | Senal positiva | -- |
| **Celda carga** | A- | HX711 A- | Senal negativa | -- |
| **LCD 16x2** | VCC | 3.3V | Alimentacion pantalla | -- |
| **LCD 16x2** | GND | GND | Tierra comun | -- |
| **LCD 16x2** | SDA | GPIO 21 | Datos I2C | I2C 100kHz |
| **LCD 16x2** | SCL | GPIO 22 | Reloj I2C | I2C 100kHz |
| **L298N** | ENA | GPIO 25 | Velocidad PWM motor | PWM 1kHz |
| **L298N** | IN1 | GPIO 15 | Direccion adelante | Digital |
| **L298N** | IN2 | GPIO 14 | Direccion atras | Digital |
| **BTN_NOMBRE** | Pin 1 | GPIO 32 | Cambiar trabajador | INPUT_PULLDOWN |
| **BTN_OK** | Pin 1 | GPIO 33 | Confirmar pesaje | INPUT_PULLDOWN |
| **BTN_STOP** | Pin 1 | GPIO 4 | Emergencia 400ms | Pull-down 10kOhm |
| **LoRa SX1276** | SCK | GPIO 5 | Reloj SPI | SPI |
| **LoRa SX1276** | MISO | GPIO 19 | Datos SPI | SPI |
| **LoRa SX1276** | MOSI | GPIO 27 | Datos SPI | SPI |
| **LoRa SX1276** | SS | GPIO 18 | Chip Select | SPI |
| **LoRa SX1276** | RST | GPIO 23 | Reset modulo | Digital |
| **LoRa SX1276** | DIO0 | GPIO 26 | IRQ TX/RX | Digital |

&gt; Nota critica: GPIO13 fue reasignado de BTN_STOP a HX711 DOUT en firmware v23. BTN_STOP se movio a GPIO4 con pull-down externo + hold 400ms para eliminar activaciones falsas en boot.

&gt; Archivo KiCad: `PCBtelecof.kicad_pcb` -- Repositorio: `/HARDWARE/`

---

### 2. Dimensiones Mecanicas (As-Built)

| Parametro | Diseno | Medido (As-Built) | Estado |
|---|:---:|:---:|:---:|
| Ancho max. PCB Nodo A | &lt;= 120mm | **120mm** | Conforme |
| Longitud carcasa Nodo A | &lt;= 80mm | ~80mm | Conforme |
| Altura carcasa Nodo A | &lt;= 45mm | ~45mm | Conforme |
| Ancho max. PCB Nodo B | &lt;= 60mm | **60mm** | Conforme |
| Longitud carcasa Nodo B | &lt;= 40mm | ~40mm | Conforme |
| Material del chasis | PLA+ | PLA+ | Conforme |
| Peso total sistema Nodo A | &lt;= 300g | ~280g (est.) | Conforme |
| Peso total sistema Nodo B | &lt;= 100g | ~85g (est.) | Conforme |

---

### 3. Auditoria de Costos Real (Actualizada a Mayo 2026)

#### Componentes Adquiridos

| Item | Componente | Precio Estimado | Precio Real (COP) | Delta Costo | Estado |
|------|---|:---:|:---:|:---:|:---:|
| 1 | LilyGo TTGO LoRa32 V2.1 (x2) | $150.000 | $160.000 | +$10.000 | Comprado |
| 2 | HX711 24 bits + Celda 5kg | $20.000 | $23.000 | +$3.000 | Comprado |
| 3 | LCD 16x2 I2C (PCF8574) | $12.000 | $15.000 | +$3.000 | Comprado |
| 4 | L298N Driver Motor | $12.000 | $15.000 | +$3.000 | Comprado |
| 5 | Motor DC 5V | $10.000 | $13.000 | +$3.000 | Comprado |
| 6 | Botones pulsadores 6x6mm (x3) | $1.000 | $1.500 | +$500 | Comprado |
| 7 | Resistencias 10kOhm (pull-down) | $300 | $500 | +$200 | Comprado |
| 8 | Cables y protoboard | $8.000 | $10.200 | +$2.200 | Comprado |
| 9 | Carcasa impresion 3D PLA+ | $10.000 | $13.000 | +$3.000 | Comprado |
| 10 | Cables celda carga 4 hilos | $1.500 | $2.000 | +$500 | Comprado |
| 11 | Antenas SMA 915MHz (x2) | $3.000 | $4.500 | +$1.500 | Comprado |
| 12 | Filamento PLA+ 200g | $5.000 | $5.000 | $0 | Comprado |
| 13 | O-Rings + Insumos mecanicos | $2.000 | $2.000 | $0 | Comprado |

#### Resumen Real vs Estimado

| Categoria | Estimado | Real | Delta |
|---|:---:|:---:|:---:|
| Electronica y Sensores | $182.000 | $198.000 | +$16.000 |
| Potencia y Energia | $5.000 | $5.000 | $0 |
| Mecanica e Insumos | $69.500 | $54.200 | -$15.300 |
| **TOTAL** | **$256.500** | **$257.200** | **+$700** |

&gt; El proyecto se ejecuto dentro del presupuesto estimado con una variacion de apenas **+0.3%**.
&gt; Sobreejercicio: L298N danado en pruebas (+$3.000) + antena adicional (+$1.500)
&gt; Ahorro: Cables simplificados (-$1.800) + carcasa 3D optimizada (-$2.000)

---

### 4. Referencias de Archivos

| Archivo | Descripcion | Ubicacion |
|---|---|---|
| `PCBtelecof.kicad_pcb` | Esquematico PCB en KiCad | GitHub `/HARDWARE/` |
| `Manual_Tecnico_Telecof.pdf` | Manual tecnico completo (TDC-MT-01 Rev 1.0) | GitHub `/01_GESTION/MANUALES/` |
| `Dashboard_MAHD.xlsx` | Dashboard de seguimiento MAHD | GitHub (raiz) |
| `Protocolos_de_prueba.xlsx` | Protocolos V&V formales | GitHub `/PROTOCOLO_PRUEBAS/` |

---


