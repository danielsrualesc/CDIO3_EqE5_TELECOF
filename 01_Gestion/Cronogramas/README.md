# 🚡 Teleférico del Café

![Estado: Completado](https://img.shields.io/badge/Estado-Completado-brightgreen)
![Hardware: ESP32](https://img.shields.io/badge/Hardware-ESP32_LilyGo_LoRa32-blue)
![Fase: Semana_15](https://img.shields.io/badge/Fase-Semana_15-orange)

**Autores:** Erick Santiago Cruz Silva · Rohin Heliab Suarez Gallego · Daniel Steven Ruales Cuaran · Kevin Esteban Aragon Camacho  
**Programa:** Ingeniería Electrónica — Proyecto CDIO III

El **Teleférico del Café** es un sistema embebido de pesaje agroindustrial diseñado para la medición y registro automatizado del café recolectado por trabajadores en campo. El sistema integra dos nodos LilyGo TTGO LoRa32: el **Nodo A (Transmisor)** que gestiona el pesaje, el control del motor DC y la interfaz del operario, y el **Nodo B (Receptor)** que almacena los registros y sirve la lista de trabajadores por WiFi. Este repositorio contiene el código fuente (Firmware v23), el diseño de hardware y la documentación técnica del Prototipo Mínimo Viable (PMV).

## 📑 Tabla de Contenidos
- [Tecnologías Utilizadas](#️-tecnologías-utilizadas)
- [Requisitos de Entrega (PMV)](#️-requisitos-de-entrega-pmv)
- [Cronograma de Ejecución](#-cronograma-de-ejecución)
- [Estructura del Repositorio](#-estructura-del-repositorio)

---

## 🛠️ Tecnologías Utilizadas
- **Microcontrolador:** LilyGo TTGO LoRa32 (ESP32 + SX1276 915MHz)
- **Comunicación:** LoRa 915MHz (SF7, BW 125kHz) · WiFi HTTP
- **Lenguaje Core:** C/C++ (Arduino Framework)
- **Sensor de Peso:** Potenciómetro 10kΩ — ADC 12 bits, resolución 0.1g
- **Actuador:** Motor DC con driver L298N — control PWM
- **Interfaz:** LCD 16x2 I2C (PCF8574, dirección 0x27)
- **Librerías:** LoRa (Sandeep Mistry) · LiquidCrystal I2C · ArduinoJson v6 · HTTPClient

---

## ⚠️ Requisitos de Entrega (PMV)
Estado actual de los entregables obligatorios para la sustentación final:

- [x] **Gestión:** Cronograma actualizado, bitácoras semanales y metodologías de trabajo en equipo.
- [x] **Hardware:** Conexiones LilyGo A + LCD + L298N + Motor + Botones + Potenciómetro.
- [x] **Firmware:** Código fuente v23 estable con manejo de dependencias y anti-rebote BTN_STOP.
- [x] **Comunicación:** Transmisión LoRa 915MHz verificada a 50m en campo abierto.
- [x] **Pruebas de Campo:** 10 ciclos consecutivos sin fallos. Validación LoRa a 30m con obstáculos.
- [ ] **Dossier de Ingeniería:**
  - [ ] Planos electrónicos y diagrama de flujo de estados.
  - [ ] Manual de usuario y matriz de cumplimiento.
  - [ ] Video demostrativo del sistema en operación.

---

## 📊 Cronograma de Ejecución

El siguiente diagrama detalla el plan de trabajo semestral ajustado a las fechas de evaluación obligatorias, abarcando desde el inicio de clases hasta el cierre definitivo en la **Semana 16**.

> **Nota:** La línea vertical indica la fecha actual.

```mermaid
gantt
    title Plan de Proyecto Teleférico del Café - Semestre 2026-I
    dateFormat  YYYY-MM-DD
    axisFormat  %d/%m
    todayMarker on

    section Fase 1: Análisis y Diseño
    Levantamiento de Requisitos   :done,    des1, 2026-02-09, 7d
    Selección de Componentes      :done,    des2, 2026-02-16, 7d
    Diseño Pinout y Conexiones    :done,    des3, 2026-02-23, 7d
    Entrega Portafolio 1 (Sem 5)  :milestone, done, m1, 2026-03-09, 0d

    section Fase 2: Firmware
    Comunicación WiFi y HTTP      :done,    dev1, 2026-03-13, 7d
    Sistema de Pesaje ADC         :done,    dev2, 2026-03-20, 7d
    Control Motor DC L298N        :done,    dev3, 2026-03-27, 7d
    Botón Emergencia GPIO13       :done,    dev4, 2026-04-03, 7d
    Eval. Proyecto (Sem 9)        :milestone, done, m2, 2026-04-07, 0d

    section Fase 3: Integración
    Flujo Emergencia Completo     :done,    int1, 2026-04-10, 7d
    Transmisión LoRa 915MHz       :done,    int2, 2026-04-17, 7d
    Integración Ciclo Completo    :done,    int3, 2026-04-24, 7d
    LilyGo B Receptor             :done,    int4, 2026-05-01, 7d
    Cierre de Desarrollo (Sem 13) :milestone, done, m3, 2026-04-27, 0d

    section Fase 4: Validación y Cierre
    Pruebas de Campo              :done,    val1, 2026-05-08, 7d
    Corrección y Código v23       :done,    val2, 2026-05-11, 4d
    Presentación Cliente (Sem 14) :crit, milestone, m4, 2026-05-11, 0d
    Documentación Final           :active,  doc1, 2026-05-11, 7d
    Sustentación Final (Sem 16)   :crit, milestone, m5, 2026-05-25, 0d
` ` `

***

## 📁 Estructura del Repositorio

` ` `
Teleferico-del-Cafe/
│
├── 📂 Firmware/
│   ├── LilyGo_A_Transmisor_v23.ino   # Nodo A: Pesaje + Motor + LoRa TX
│   └── LilyGo_B_Receptor.ino         # Nodo B: Servidor HTTP + LoRa RX
│
├── 📂 Hardware/
│   ├── Diagrama_Conexiones.png        # Pinout completo del sistema
│   └── BOM.md                         # Lista de materiales con precios COP
│
├── 📂 Documentacion/
│   ├── Bitacoras/                     # 14 bitácoras semanales (CDIO III)
│   └── Cronograma_Teleferico.xlsx     # Cronograma Gantt del semestre
│
└── README.md
` ` `
```

> ⚠️ **Nota:** Los bloques de código que tienen ` ` ` (con espacios) cámbialos por ` ``` ` sin espacios al pegarlo en GitHub. Los puse así para que no se cortara el formato aquí.

<user_response_autocomplete>
Listo ya lo pegué perfecto
Cómo quito los espacios de los backticks
Los checkboxes no me aparecen marcados
</user_response_autocomplete>
