# 🚡 Teleférico del Café

![Estado: Completado](https://img.shields.io/badge/Estado-Completado-brightgreen)
![Hardware: ESP32](https://img.shields.io/badge/Hardware-ESP32_LilyGo_LoRa32-blue)
![Fase: Semana_15](https://img.shields.io/badge/Fase-Semana_15-orange)

**Autores:** Erick Santiago Cruz Silva · Rohin Heliab Suarez Gallego · Daniel Steven Ruales Cuaran · Kevin Esteban Aragon Camacho  
**Programa:** Ingeniería Electrónica — Proyecto CDIO III

El **Teleférico del Café** es un sistema embebido de pesaje agroindustrial diseñado para la medición y registro automatizado del café recolectado por trabajadores en campo. El sistema integra dos nodos LilyGo TTGO LoRa32: el **Nodo A (Transmisor)** que gestiona el pesaje, el control del motor DC y la interfaz del operario, y el **Nodo B (Receptor)** que almacena los registros y sirve la lista de trabajadores por WiFi.

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

El siguiente diagrama detalla el plan de trabajo semestral desde el inicio de clases hasta el cierre definitivo en la **Semana 16**.

> **Nota:** La línea vertical indica la fecha actual.

```mermaid
gantt
    title Teleferico del Cafe - Semestre 2026-I
    dateFormat  YYYY-MM-DD
    axisFormat  %d/%m
    todayMarker on

    section Fase 1 Analisis y Diseno
    Levantamiento Requisitos   :done, des1, 2026-02-09, 7d
    Seleccion Componentes      :done, des2, 2026-02-16, 7d
    Diseno Pinout              :done, des3, 2026-02-23, 7d
    Portafolio 1 Sem5          :milestone, done, m1, 2026-03-09, 1d

    section Fase 2 Firmware
    WiFi y HTTP                :done, dev1, 2026-03-13, 7d
    Pesaje ADC                 :done, dev2, 2026-03-20, 7d
    Motor DC L298N             :done, dev3, 2026-03-27, 7d
    Boton Emergencia GPIO13    :done, dev4, 2026-04-03, 7d
    Evaluacion Sem9            :milestone, done, m2, 2026-04-07, 1d

    section Fase 3 Integracion
    Flujo Emergencia           :done, int1, 2026-04-10, 7d
    Transmision LoRa 915MHz    :done, int2, 2026-04-17, 7d
    Ciclo Completo             :done, int3, 2026-04-24, 7d
    LilyGo B Receptor          :done, int4, 2026-05-01, 7d
    Cierre Desarrollo Sem13    :milestone, done, m3, 2026-04-27, 1d

    section Fase 4 Validacion y Cierre
    Pruebas de Campo           :done, val1, 2026-05-08, 7d
    Codigo v23                 :done, val2, 2026-05-11, 4d
    Presentacion Cliente       :crit, milestone, m4, 2026-05-11, 1d
    Documentacion Final        :active, doc1, 2026-05-11, 7d
    Sustentacion Final Sem16   :crit, milestone, m5, 2026-05-25, 1d
```

---

## 📁 Estructura del Repositorio
