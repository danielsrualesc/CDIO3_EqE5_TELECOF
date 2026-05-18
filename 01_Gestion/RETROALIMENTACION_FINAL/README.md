# Validacion Final y Entrega del Producto Teleferico del Cafe

**Proyecto:** Teleferico del Cafe - Sistema Embebido de Pesaje Agroindustrial
**Cliente / Usuario Final:** Operarios de recoleccion de cafe y administrador de finca (Universidad del Quindio - CDIO III)
**Ingenieros a Cargo:** Erick S. Cruz Silva, Rohin H. Suarez Gallego, Daniel S. Ruales Cuaran, Kevin E. Aragon Camacho
**Fecha de Entrega:** Mayo 2026

---

## 1. Resumen de Entrega
Este documento oficializa la culminacion y entrega del proyecto **Teleferico del Cafe**. Tras un ciclo de desarrollo iterativo basado en la metodologia CDIO (Concebir, Disenar, Implementar, Operar), el sistema ha pasado de ser un concepto a una herramienta tecnologica validada y funcional en un entorno real de recoleccion de cafe. Las pruebas de campo y la retroalimentacion final del cliente confirman el exito rotundo de la implementacion.

## 2. Pruebas de Campo Reales (Operacion)
Las pruebas finales se ejecutaron en la finca experimental de la Universidad del Quindio con la participacion directa de operarios de recoleccion de cafe y el administrador de finca, sometiendo el dispositivo a condiciones reales de cosecha.

### 2.1. Condiciones de Prueba
* **Entorno:** Finca experimental al aire libre, temperatura 28 C, humedad 75%.
* **Implemento:** Nodo A (Transmisor) con celda de carga 5 kg, motor DC simulando teleferico, LCD 16x2 y 3 botones. Nodo B (Receptor) en oficina de administracion.
* **Procedimiento:** El operario selecciono su nombre, coloco cafe recolectado en la canastilla sobre la celda de carga, espero 10 s de pesaje, confirmo el resultado, y el sistema activo el motor transportador. Al finalizar, el paquete LoRa se transmitio automaticamente al Nodo B.
* **Captura de Datos:** El Nodo A registro peso y pago en LCD. El Nodo B recibio paquetes LoRa y almaceno registros en RAM para descarga HTTP.

### 2.2. Resultados de la Validacion Tecnica
* **Precision de Pesaje:** El HX711 24 bits con celda de carga 5 kg registro pesos con resolucion de 0.1 g, validado con pesas patron de 100 g, 500 g, 1000 g, 2000 g y 5000 g. Desviacion maxima: +/- 0.2 g en carga maxima.
* **Integridad Fisica:** La carcasa PLA+ (120 mm x 80 mm x 45 mm) protegio el hardware durante 4 horas continuas de operacion en campo sin deterioro estructural.
* **Transmision Inalambrica:** El envio de paquetes LoRa 915 MHz desde Nodo A (campo) a Nodo B (base) funciono a 50 m campo abierto (10/10 paquetes) y 30 m con obstaculos (9/10 paquetes), validando la independencia de internet.
* **Autonomia:** El sistema opero 4 horas 30 minutos con fuente 5V externa, superando el requisito minimo de 4 horas.
* **Emergencia:** El boton BTN_STOP (GPIO4) detuvo el motor inmediatamente en 3 pruebas consecutivas desde diferentes estados, con retorno proporcional al origen verificado.

## 3. Retroalimentacion Final del Cliente (La Voz del Usuario)
La evaluacion cualitativa del usuario final es el indicador definitivo del exito del Teleferico del Cafe. Las opiniones recopiladas durante la entrega destacan el impacto del producto:

* **Operario (Erick):** *"El sistema es facil de usar. Solo presiono mi nombre, pongo el cafe, espero unos segundos y ya se cuanto me van a pagar. El motor mueve la canastilla solo y no tengo que cargar nada pesado. Antes tenia que anotar todo en papel y a veces me confundia con los kilos."*
* **Administrador:** *"Por fin tengo los datos de todos los trabajadores organizados en un CSV que abro en Excel. No necesito internet en el campo porque el sistema usa radio. Puedo ver cuanto pago a cada uno sin estar pendiente de papeles. Los numeros coinciden con la balanza de la finca."*
* **Operario (Oscar):** *"El boton rojo de emergencia me da confianza. Una vez se atoro la cuerda del teleferico y lo detuve rapido. El motor volvio solo al inicio y no perdi el cafe que ya habia pesado."*

## 4. Evidencia Multimedia
Para respaldar este hito, se adjunta el siguiente archivo en el repositorio:
* `PRUEBASISTEMACOMPLETO.MP4`: Material audiovisual con las declaraciones y opiniones de primera mano de los operarios y el administrador tras utilizar el sistema, junto con demostracion completa del ciclo de pesaje, motor teleferico y transmision LoRa en campo real.

## 5. Cierre de Proyecto
Con la validacion tecnica en campo y la aprobacion entusiasta del cliente, el equipo de ingenieria declara el proyecto **Teleferico del Cafe** como exitosamente entregado. El producto cumple a cabalidad con la Matriz de Requisitos, el Definition of Done y soluciona un problema latente en la recoleccion de cafe de forma profesional e innovadora.
