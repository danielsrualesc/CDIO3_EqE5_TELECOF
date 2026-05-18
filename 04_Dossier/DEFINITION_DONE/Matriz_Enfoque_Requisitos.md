# 📊 Matriz de Enfoque y Requisitos — Proyecto Teleférico de Café  
**Universidad del Quindío | Ingeniería Electrónica | 2025–2026**  
**Equipo:** [Nombre de Integrantes]

---

## 1. Historia de Usuario y Valor del Proyecto

| ID | Historia de Usuario | Valor (1–5) | Riesgo Técnico (1–5) | Prioridad |
|----|---|:---:|:---:|:---:|
| HU-01 | Como operador, quiero monitorear el estado del teleférico en tiempo real para garantizar un funcionamiento seguro. | 5 | 4 | **P0** |
| HU-02 | Como usuario del sistema, quiero que el transporte de café sea automatizado para reducir el esfuerzo manual. | 5 | 3 | **P0** |
| HU-03 | Como técnico, quiero visualizar datos de sensores para detectar fallas rápidamente. | 4 | 4 | **P1** |
| HU-04 | Como administrador, quiero registrar el comportamiento del sistema para evaluar rendimiento y mantenimiento. | 4 | 3 | **P1** |
| HU-05 | Como usuario final, quiero un sistema estable y seguro para evitar pérdidas del producto transportado. | 5 | 5 | **P0** |

---

## 2. Matriz de Requisitos Técnicos

| ID Req. | Requisito | Especificación Medible | Validado por |
|---------|---|---|---|
| REQ-HW-01 | Alimentación estable | Sistema operando a 5V/12V sin interrupciones | TEST-HW-01 ✅ |
| REQ-HW-02 | Sensado de posición | Lectura correcta de sensores en tiempo real | TEST-HW-02 ✅ |
| REQ-FW-01 | Tiempo de respuesta | Actualización de datos ≤ 1 segundo | TEST-SW-01 ✅ |
| REQ-FW-02 | Comunicación | Conectividad estable entre sensores y controlador | TEST-COM-01 ✅ |
| REQ-SW-01 | Interfaz de monitoreo | Visualización clara del estado del teleférico | Validado v1.0 |
| REQ-MC-01 | Integridad mecánica | Funcionamiento continuo sin fallos estructurales | TEST-MEC-01 ✅ |

---

## 3. Hardware Backlog y Presupuesto (BOM)

### Electrónica Principal

| Ítem | Componente | Cant. | Especificación | Est. Costo (COP) |
|------|---|:---:|---|:---:|
| 1 | Microcontrolador | 1 | ESP32 / Arduino (según implementación) | $35.000 |
| 2 | Sensor principal | 1 | MPU6050 / Sensor de inclinación | $15.000 |
| 3 | Pantalla | 1 | OLED I2C 0.96" | $20.000 |
| 4 | Buzzer | 1 | Indicador sonoro | $3.000 |
| 5 | Fuente/Batería | 1 | Alimentación del sistema | $25.000 |

### Sistema Mecánico

| Ítem | Componente | Cant. | Especificación | Est. Costo (COP) |
|------|---|:---:|---|:---:|
| 6 | Poleas | 2 | Movimiento del cable | $20.000 |
| 7 | Motor DC | 1 | Accionamiento del teleférico | $45.000 |
| 8 | Estructura | 1 | Soporte de maqueta | $40.000 |
| 9 | Cable guía | 1 | Transporte del vagón | $10.000 |

### Mecánica e Insumos

| Ítem | Componente | Cant. | Especificación | Est. Costo (COP) |
|------|---|:---:|---|:---:|
| 10 | Protoboard/Cables | 1 | Conexión de componentes | $15.000 |
| 11 | Resistencias y LEDs | Varias | Señalización visual | $5.000 |
| 12 | Tornillería | Varias | Ensamble mecánico | $8.000 |

### 💰 Resumen Presupuesto

| Categoría | Subtotal |
|---|:---:|
| Electrónica | $98.000 |
| Sistema Mecánico | $115.000 |
| Insumos y Materiales | $28.000 |
| **TOTAL APROXIMADO** | **$241.000 COP** |

---

## 4. Planificación MAHD — Ciclos IPAC

| IPAC | Objetivo | Fecha Inicio | Fecha Fin | Estado |
|------|---|---|---|---|
| IPAC-01 | Diseño conceptual del sistema teleférico | Sem. 1 | Sem. 2 | ✅ Done |
| IPAC-02 | Integración electrónica (sensores + ESP32) | Sem. 3 | Sem. 5 | ✅ Done |
| IPAC-03 | Desarrollo de maqueta mecánica y pruebas | Sem. 6 | Sem. 8 | ✅ Done |
| IPAC-04 | Integración total y validación del sistema | Sem. 9 | Sem. 12 | ✅ Validado |

---

**Proyecto Teleférico de Café © 2025 — Sistema Inteligente de Transporte Automatizado de Café**
