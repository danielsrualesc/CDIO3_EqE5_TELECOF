# Gestion del Proyecto Teleferico del Cafe:

Este directorio centraliza la documentacion administrativa, planificacion y analisis de requisitos del sistema **Teleferico del Cafe** (Sistema Embebido de Pesaje Agroindustrial para Recoleccion de Cafe).

**Institucion:** Universidad del Quindio.
**Programa:** Ingenieria Electronica (Sexto Semestre)
**Ubicacion:** Armenia, Quindio, Colombia.
**Duracion:** 1 Semestre (CDIO III).
---

## Alcance del Proyecto:

El objetivo es desarrollar un sistema embebido de dos nodos capaz de automatizar el registro de pesaje de cafe recolectado, calcular el pago al trabajador y transmitir los datos via LoRa desde el campo hasta la oficina de administracion.

### Objetivos Especificos (KPIs)
1.  **Captura de Peso:** Medicion con resolucion de 0.1 g en rango 0 -- 5.000 g.
2.  **Calculo de Pago:** Conversion automatica a COP con tarifa 1.200 COP/kg.
3.  **Transmision Inalambrica:** Envio de datos via LoRa 915 MHz a 50 m campo abierto.
4.  **Autonomia:** Operacion continua &gt;= 4 horas sin recarga.
5.  **Costo:** Presupuesto total entre $250.000 y $300.000 COP.

---

## Roadmap de Implementacion:

El proyecto se ejecuta en un semestre segun los lineamientos academicos del curso CDIO III:

### Fase Unica: Hardware, Firmware y Conectividad (Semestre Actual)
| Semanas | Hito / Entregable | Estado |
| :--- | :--- | :--- |
| **1-4** | Adquisicion de componentes (LilyGo TTGO x2, HX711, celda 5kg, L298N, LCD 16x2, motor DC). | Hecho |
| **5-8** | Integracion de modulo de pesaje (HX711 + celda), pantalla LCD 16x2 I2C y botones (NOMBRE, OK, STOP). | Hecho |
| **9-12** | Implementacion de motor DC con L298N (teleferico simulado), FSM de 9 estados y comunicacion LoRa 915 MHz. | Hecho |
| **13-16** | Pruebas de campo, calibracion de pesaje, validacion de alcance LoRa y documentacion final. | Hecho |

---
## Matriz de Requisitos

### Requisitos Funcionales (RF)
* **RF-001:** Captura de peso con resolucion 0.1 g (HX711 24 bits, ganancia 128).
* **RF-002:** Calculo automatico de pago en COP (tarifa 1.200 COP/kg).
* **RF-003:** Seleccion de trabajador via boton NOMBRE (GPIO32).
* **RF-004:** Ciclo de pesaje de 10 s con promedio de 10 muestras.
* **RF-005:** Control de motor DC (adelante 1.350 ms, pausa 10 s, atras 1.350 ms).
* **RF-006:** Transmision LoRa de paquete PESAJE,nombre,peso,pago al Nodo B.
* **RF-007:** Visualizacion de peso y pago en LCD 16x2 I2C (direccion 0x27).
* **RF-008:** Descarga de registros via HTTP GET /lista desde Nodo B.
* **RF-009:** Modo autonomo con lista de respaldo hardcodeada (sin WiFi).
* **RF-010:** Detencion de emergencia con BTN_STOP (GPIO4, hold 400 ms).

### Requisitos No Funcionales (RNF)
* **RNF-001 Precision:** Error maximo de pesaje +/- 0.2 g en carga maxima (5 kg).
* **RNF-002 Portabilidad:** Peso total Nodo A &lt;= 300 g, Nodo B &lt;= 100 g.
* **RNF-003 Resistencia Ambiental:** Operacion en clima de Quindio (0 C - 50 C, humedad 10-90% RH).
* **RNF-004 Recuperabilidad:** Sistema autonomo ante falla de WiFi (lista respaldo en 20 s).
* **RNF-005 Seguridad:** Detencion de emergencia desde cualquier estado motor activo.
* **RNF-006 Usabilidad:** Interfaz LCD con mensajes en espanol, formato 1 decimal unificado.

---

## Presupuesto y Recursos

**Presupuesto Estimado:** $250.000 - $300.000 COP.

### Componentes Principales (BOM)
* **Microcontrolador:** LilyGo TTGO LoRa32 V2.1 (ESP32 dual-core + SX1276) x2 unidades.
* **Modulo de Pesaje:** HX711 24 bits + Celda de carga 5 kg (strain gauge).
* **Interfaz:** LCD 16x2 I2C (PCF8574) + 3 botones pulsadores 6x6 mm.
* **Actuador:** Motor DC 5V + Driver L298N (control PWM 1 kHz).
* **Energia:** Fuente 5V via USB-C (regulador interno 3.3V ESP32).
* **Comunicacion:** LoRa 915 MHz (antenas SMA integradas en LilyGo).
* **Carcasa:** Impresion 3D PLA+ (120 mm x 80 mm x 45 mm).

---

## Gestion de Riesgos y Restricciones
1.  **Conectividad:** La red WiFi en campo no es garantizada. Se mitiga con operacion autonoma (lista respaldo) y transmision LoRa independiente de internet.
2.  **Clima:** La alta humedad del Quindio requiere proteccion de la PCB y celda de carga contra condensacion (carcasa PLA+ cerrada).
3.  **Vibracion:** El motor DC genera vibraciones que pueden afectar la lectura del HX711. Se mitiga con promedio de 10 muestras y estabilizacion mecanica.
4.  **Peso maximo:** La celda de carga soporta maximo 5 kg. Se debe educar al operario para no exceder este limite.
5.  **GPIO boot:** GPIO13 y GPIO2 tienen comportamiento especial en boot del ESP32. Se mitiga con reasignacion de pines (BTN_STOP a GPIO4) y verificacion de inicializacion.

---

*Documento basado en la especificacion de requisitos v1.0 (Febrero 2026).*
