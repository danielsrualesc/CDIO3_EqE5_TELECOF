# Retrospectiva IPAC — Lecciones Aprendidas
**Proyecto:** Teleférico del Café | **Ciclo:** IPAC-03 → IPAC-04
**Fecha:** 2026-05-11 | **Facilitador:** Equipo Teleférico del Café

---

## 🔴 ¿Qué falló?

### Fallo 1 — Activaciones falsas del BTN_STOP GPIO13 (TEST-FW-01 ❌)
**Síntoma:** El botón de emergencia se activaba solo al arrancar el sistema, sin ser presionado físicamente.
**Causa raíz:** El GPIO13 del ESP32 tiene pull-up interno activo en ciertos modos de boot, dejando el pin flotante y generando lecturas HIGH espurias antes de que el firmware lo inicializara correctamente.
**Impacto:** El sistema entraba en modo emergencia al encender, bloqueando el ciclo de pesaje desde el inicio.

### Fallo 2 — Peso con múltiples decimales en ADC (TEST-FW-02 ❌)
**Síntoma:** El potenciómetro generaba valores como `45.238491g` en lugar de avanzar de décima en décima.
**Causa raíz:** La función `leerPeso()` devolvía el valor flotante crudo del mapeo ADC sin ningún redondeo, produciendo ruido en los últimos decimales.
**Impacto:** Los valores mostrados en el LCD y transmitidos por LoRa eran inconsistentes e imposibles de leer correctamente en campo.

### Fallo 3 — Motor no retornaba al origen tras emergencia (TEST-HW-01 ❌)
**Síntoma:** Al activar la emergencia durante el ciclo `ST_MOTOR_A`, el motor se detenía pero no volvía al punto de partida.
**Causa raíz:** La variable `tiempoGirado` no se calculaba correctamente al activar la emergencia desde estados distintos a `ST_MOTOR_A`, resultando en `tiempoGirado = 0` y saltando el retorno.
**Impacto:** El mecanismo quedaba en posición intermedia, requiriendo reset manual del sistema.

### Fallo 4 — Desconexión WiFi bloqueaba el arranque (TEST-FW-03 ❌)
**Síntoma:** Si el hotspot no estaba disponible al encender, el sistema quedaba colgado esperando conexión indefinidamente.
**Causa raíz:** El loop de conexión WiFi no tenía límite de intentos, bloqueando el `setup()` sin pasar al modo de operación con respaldo.
**Impacto:** El sistema era inutilizable en campo sin cobertura WiFi, perdiendo el propósito de operación autónoma.

---

## ✅ Acciones Correctivas Implementadas / Planificadas

| # | Acción | Tipo | Estado | Responsable |
|---|---|---|---|---|
| AC-01 | Agregar `gpio_pulldown_en(GPIO_NUM_13)` y `gpio_pullup_dis(GPIO_NUM_13)` en `setup()` con delay de 500ms | Firmware | ✅ Implementado | Erick Santiago Cruz Silva |
| AC-02 | Implementar hold time de 400ms en `leerBtnStop()` para ignorar pulsaciones cortas (ruido/boot) | Firmware | ✅ Implementado | Daniel Steven Ruales Cuaran |
| AC-03 | Aplicar `roundf(pesoRaw * 10.0) / 10.0` en `leerPeso()` para resolución de 0.1g | Firmware | ✅ Implementado | Erick Santiago Cruz Silva |
| AC-04 | Unificar formato de peso a 1 decimal en LCD, Serial y paquete LoRa (`String(peso, 1)`) | Firmware | ✅ Implementado | Kevin Esteban Aragon Camacho |
| AC-05 | Calcular `tiempoGirado = millis() - timerMotor` solo cuando `estadoActual == ST_MOTOR_A` en `activarEmergencia()` | Firmware | ✅ Implementado | Daniel Steven Ruales Cuaran |
| AC-06 | Limitar intentos WiFi a 40 ciclos (20s) y llamar `usarRespaldo()` si no conecta | Firmware | ✅ Implementado | Rohin Heliab Suarez Gallego |

---

## 💡 Lo que funcionó bien (Mantener)

1. **Arquitectura por máquina de estados (FSM):** Los 9 estados del sistema (`ST_ESPERA`, `ST_PESANDO`, `ST_MOTOR_A`, etc.) permitieron agregar y corregir comportamientos sin romper el resto del flujo.
2. **Sistema de respaldo de trabajadores:** La lista local `{"Erick", "Oscar", "Yunicua"}` garantizó operación continua sin WiFi, clave para uso en campo sin conectividad.
3. **Transmisión LoRa 915MHz:** El módulo SX1276 integrado en el LilyGo transmitió correctamente a 50m en campo abierto con SF7, BW 125kHz sin pérdidas detectadas.
4. **Debounce por tiempo en botones:** El uso de `millis() - dbX > DEBOUNCE_MS` en lugar de `delay()` evitó bloqueos en el loop principal durante el ciclo de pesaje.

---

## 📌 Compromisos para IPAC-04

- [x] BTN_STOP con pull-down fuerte y hold time 400ms validado antes del **2026-04-10**
- [x] Redondeo a 0.1g implementado y verificado en LCD y LoRa antes del **2026-04-17**
- [x] Retorno de emergencia proporcional a `tiempoGirado` validado en ciclo completo antes del **2026-04-24**
- [x] Sistema operativo sin WiFi con lista de respaldo validado en campo antes del **2026-05-08**
- [ ] Diagrama de flujo de estados del firmware documentado antes del **2026-05-18**
- [ ] Video demostrativo del ciclo completo grabado antes del **2026-05-22**
