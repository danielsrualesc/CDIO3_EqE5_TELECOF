// ============================================================
// LILYGO B — RECEPTOR LoRa + SERVIDOR WEB v5
// Pago con 3 decimales COP · IP fija iPhone 172.20.10.5
// ============================================================

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPI.h>
#include <LoRa.h>
#include <time.h>

const char* WIFI_SSID  = "iPhone de Erick Santiago";
const char* WIFI_PASS  = "1007163935";
const char* LOGIN_USER = "admin";
const char* LOGIN_PASS = "1234";

#define LORA_SCK   5
#define LORA_MISO  19
#define LORA_MOSI  27
#define LORA_SS    18
#define LORA_RST   23
#define LORA_DIO0  26
#define LORA_BAND  915E6
#define MAX_TRAB   15

String nombresReg[MAX_TRAB];
int numNombres = 0;

struct Trabajador {
  String nombre;
  int    cargas;
  float  pesoTotal;
  float  pagoTotal;
};
Trabajador trab[MAX_TRAB];
int   numTrab = 0;
float tarifa  = 1200.0;
bool  sesionActiva = false;

AsyncWebServer server(80);

int buscarOCrear(String nombre) {
  nombre.trim();
  for (int i = 0; i < numTrab; i++) if (trab[i].nombre == nombre) return i;
  if (numTrab < MAX_TRAB) {
    trab[numTrab].nombre    = nombre;
    trab[numTrab].cargas    = 0;
    trab[numTrab].pesoTotal = 0.0;
    trab[numTrab].pagoTotal = 0.0;
    return numTrab++;
  }
  return -1;
}

void procesarLoRa(String pkt) {
  pkt.trim();
  if (!pkt.startsWith("PESAJE,")) return;
  int c1 = pkt.indexOf(",");
  int c2 = pkt.indexOf(",", c1 + 1);
  int c3 = pkt.indexOf(",", c2 + 1);
  if (c1 < 0 || c2 < 0 || c3 < 0) return;
  String nombre = pkt.substring(c1 + 1, c2);
  float  peso   = pkt.substring(c2 + 1, c3).toFloat();
  float  pago   = pkt.substring(c3 + 1).toFloat();
  int idx = buscarOCrear(nombre);
  if (idx < 0) return;
  trab[idx].cargas++;
  trab[idx].pesoTotal += peso;
  trab[idx].pagoTotal += pago;
  Serial.print("LoRa RX: "); Serial.print(nombre);
  Serial.print(" $"); Serial.println(pago, 3);
}

String generarReporte() {
  time_t ahora = time(nullptr);
  struct tm* t = localtime(&ahora);
  char fecha[50];
  strftime(fecha, sizeof(fecha), "%d/%m/%Y %H:%M:%S", t);
  int tc = 0; float tp = 0, tpg = 0;
  for (int i = 0; i < numTrab; i++) {
    tc  += trab[i].cargas;
    tp  += trab[i].pesoTotal;
    tpg += trab[i].pagoTotal;
  }
  String s = "REPORTE DE PESAJES Y PAGOS\n";
  s += "Fecha: "; s += fecha; s += "\n";
  s += "Tarifa: $"; s += String(tarifa, 0); s += " por kg\n";
  s += "----------------------------------------\n";
  for (int i = 0; i < numTrab; i++) {
    char l[200];
    snprintf(l, sizeof(l), "%d | %-18s | %4d | %8.3f g | $%12.3f\n",
      i + 1, trab[i].nombre.c_str(), trab[i].cargas,
      trab[i].pesoTotal, trab[i].pagoTotal);
    s += l;
  }
  s += "----------------------------------------\n";
  char tot[200];
  snprintf(tot, sizeof(tot), "TOTALES | %4d | %8.3f g | $%12.3f\n", tc, tp, tpg);
  s += tot;
  return s;
}

String jsonNombres() {
  String j = "[";
  for (int i = 0; i < numNombres; i++) {
    if (i > 0) j += ",";
    j += char(34); j += nombresReg[i]; j += char(34);
  }
  j += "]";
  return j;
}

String jsonDatos() {
  String j = "[";
  for (int i = 0; i < numTrab; i++) {
    if (i > 0) j += ",";
    j += "{";
    j += char(34); j += "nombre"; j += char(34); j += ":";
    j += char(34); j += trab[i].nombre; j += char(34); j += ",";
    j += char(34); j += "cargas"; j += char(34); j += ":";
    j += String(trab[i].cargas); j += ",";
    j += char(34); j += "peso"; j += char(34); j += ":";
    j += String(trab[i].pesoTotal, 3); j += ",";
    j += char(34); j += "pago"; j += char(34); j += ":";
    j += String(trab[i].pagoTotal, 3);  // ← 3 decimales
    j += "}";
  }
  j += "]";
  return j;
}

void servirLogin(AsyncWebServerRequest* req) {
  String h = "";
  h += "<!DOCTYPE html><html><head>";
  h += "<meta charset=UTF-8>";
  h += "<meta name=viewport content=width=device-width,initial-scale=1>";
  h += "<title>Login</title>";
  h += "<style>";
  h += "body{font-family:Arial;background:#1e1e2e;display:flex;align-items:center;justify-content:center;height:100vh;margin:0}";
  h += ".card{background:#313244;padding:40px;border-radius:16px;width:300px}";
  h += "h2{color:#cba6f7;text-align:center;margin-bottom:20px}";
  h += "label{color:#cdd6f4;font-size:.9em;display:block;margin-bottom:4px}";
  h += "input{width:100%;padding:10px;border-radius:8px;border:1px solid #45475a;background:#1e1e2e;color:white;font-size:1em;margin-bottom:14px;box-sizing:border-box}";
  h += ".btn{width:100%;padding:12px;background:#cba6f7;color:#1e1e2e;border:none;border-radius:8px;font-size:1em;font-weight:bold;cursor:pointer}";
  h += ".err{color:#f38ba8;text-align:center;margin-top:10px;display:none}";
  h += "</style></head><body>";
  h += "<div class=card>";
  h += "<h2>Sistema Cafetero</h2>";
  h += "<label>Usuario</label>";
  h += "<input type=text id=u placeholder=admin>";
  h += "<label>Contrasena</label>";
  h += "<input type=password id=p placeholder=1234>";
  h += "<button class=btn onclick=login()>Entrar</button>";
  h += "<p class=err id=err>Credenciales incorrectas</p>";
  h += "</div><script>";
  h += "function login(){";
  h += "var u=document.getElementById('u').value;";
  h += "var p=document.getElementById('p').value;";
  h += "fetch('/login?user='+encodeURIComponent(u)+'&pass='+encodeURIComponent(p))";
  h += ".then(function(r){return r.text();})";
  h += ".then(function(t){";
  h += "if(t==='OK'){window.location.href='/panel';}";
  h += "else{document.getElementById('err').style.display='block';}";
  h += "});}";
  h += "document.addEventListener('keypress',function(e){if(e.key==='Enter')login();});";
  h += "</script></body></html>";
  req->send(200, "text/html", h);
}

void servirPanel(AsyncWebServerRequest* req) {
  String h = "";
  h += "<!DOCTYPE html><html><head>";
  h += "<meta charset=UTF-8>";
  h += "<meta name=viewport content=width=device-width,initial-scale=1>";
  h += "<title>Panel</title>";
  h += "<style>";
  h += "body{font-family:Arial;background:#1e1e2e;color:white;padding:20px;margin:0}";
  h += ".top{background:#313244;padding:12px 20px;border-radius:12px;display:flex;justify-content:space-between;align-items:center;margin-bottom:24px;flex-wrap:wrap;gap:10px}";
  h += ".top span{color:#cba6f7;font-weight:bold;font-size:1.1em}";
  h += ".btns{display:flex;gap:8px}";
  h += ".btn{padding:8px 14px;border:none;border-radius:8px;cursor:pointer;font-weight:bold}";
  h += ".bg{background:#a6e3a1;color:#1e1e2e}.br{background:#f38ba8;color:#1e1e2e}";
  h += ".card{background:#313244;padding:24px;border-radius:12px;margin-bottom:20px}";
  h += "h2{color:#cba6f7;margin-bottom:16px}";
  h += ".fila{display:flex;gap:10px;margin-bottom:8px}";
  h += "input{flex:1;padding:10px;border-radius:8px;border:1px solid #45475a;background:#1e1e2e;color:white;font-size:1em}";
  h += ".badd{background:#89b4fa;color:#1e1e2e;padding:10px 16px;border:none;border-radius:8px;cursor:pointer;font-weight:bold}";
  h += ".bdel{background:#f38ba8;color:#1e1e2e;padding:5px 10px;border:none;border-radius:6px;cursor:pointer;font-weight:bold}";
  h += "table{width:100%;border-collapse:collapse;margin-top:12px}";
  h += "th{color:#cba6f7;padding:10px;text-align:left;border-bottom:1px solid #45475a}";
  h += "td{padding:10px;border-bottom:1px solid #45475a;color:#cdd6f4}";
  h += "tr:hover td{background:#3d3f53}";
  h += ".badge{background:#1e1e2e;color:#a6e3a1;padding:2px 8px;border-radius:20px;font-size:.85em;margin-left:8px}";
  h += "</style></head><body>";
  h += "<div class=top><span>Gestion de Trabajadores</span>";
  h += "<div class=btns>";
  h += "<button class='btn bg' onclick='location.href=\"/sistema\"'>Ver Sistema</button>";
  h += "<button class='btn br' onclick=logout()>Cerrar sesion</button>";
  h += "</div></div>";
  h += "<div class=card><h2>Agregar Trabajador</h2>";
  h += "<div class=fila>";
  h += "<input type=text id=nombre placeholder='Nombre del trabajador'>";
  h += "<button class=badd onclick=agregar()>Agregar</button>";
  h += "</div></div>";
  h += "<div class=card>";
  h += "<h2>Trabajadores <span class=badge id=count>0</span></h2>";
  h += "<table><thead><tr><th>#</th><th>Nombre</th><th>Accion</th></tr></thead>";
  h += "<tbody id=tabla></tbody></table></div>";
  h += "<script>";
  h += "function cargar(){";
  h += "fetch('/listaNombres').then(function(r){return r.json();}).then(function(d){";
  h += "document.getElementById('count').innerText=d.length;";
  h += "var h2='';";
  h += "for(var i=0;i<d.length;i++){";
  h += "h2+='<tr><td>'+(i+1)+'</td><td>'+d[i]+'</td>';";
  h += "h2+='<td><button class=bdel onclick=\"eliminar('+i+')\">Eliminar</button></td></tr>';";
  h += "}";
  h += "document.getElementById('tabla').innerHTML=h2||'<tr><td colspan=3 style=text-align:center;color:#585b70;padding:16px>Sin trabajadores</td></tr>';";
  h += "});}";
  h += "function agregar(){";
  h += "var n=document.getElementById('nombre').value.trim();";
  h += "if(!n){alert('Ingresa un nombre');return;}";
  h += "fetch('/agregarTrab?nombre='+encodeURIComponent(n)).then(function(r){return r.text();}).then(function(t){";
  h += "if(t==='OK'){document.getElementById('nombre').value='';cargar();}else alert(t);";
  h += "});}";
  h += "function eliminar(i){";
  h += "if(!confirm('Eliminar este trabajador?'))return;";
  h += "fetch('/eliminarTrab?id='+i).then(function(){cargar();});}";
  h += "function logout(){fetch('/logout').then(function(){location.href='/';});}";
  h += "document.getElementById('nombre').addEventListener('keypress',function(e){if(e.key==='Enter')agregar();});";
  h += "cargar();";
  h += "</script></body></html>";
  req->send(200, "text/html", h);
}

void servirSistema(AsyncWebServerRequest* req) {
  String h = "";
  h += "<!DOCTYPE html><html><head>";
  h += "<meta charset=UTF-8>";
  h += "<meta name=viewport content=width=device-width,initial-scale=1>";
  h += "<title>Sistema Cafetero</title>";
  h += "<style>";
  h += "body{font-family:Arial;background:#1e1e2e;color:white;padding:20px;margin:0}";
  h += ".top{background:#313244;padding:12px 20px;border-radius:12px;display:flex;justify-content:space-between;align-items:center;margin-bottom:24px;flex-wrap:wrap;gap:10px}";
  h += ".top span{color:#cba6f7;font-weight:bold;font-size:1.1em}";
  h += ".btns{display:flex;gap:8px;flex-wrap:wrap}";
  h += ".btn{padding:8px 14px;border:none;border-radius:8px;cursor:pointer;font-weight:bold}";
  h += ".bb{background:#89b4fa;color:#1e1e2e}.by{background:#fab387;color:#1e1e2e}";
  h += ".bg{background:#a6e3a1;color:#1e1e2e}.br{background:#f38ba8;color:#1e1e2e}";
  h += ".wrap{background:#313244;border-radius:12px;padding:24px;overflow-x:auto}";
  h += "h2{color:#cba6f7;margin-bottom:16px}";
  h += "table{width:100%;border-collapse:collapse;min-width:500px}";
  h += "thead tr{background:#45475a}";
  h += "th{padding:12px 16px;text-align:center;color:#cba6f7;border:1px solid #585b70}";
  h += "th:nth-child(2){text-align:left}";
  h += "td{padding:10px 16px;border:1px solid #45475a;text-align:center;color:#cdd6f4}";
  h += "td:nth-child(2){text-align:left;color:white;font-weight:bold}";
  h += "tr:hover td{background:#3d3f53}";
  h += ".tot td{background:#1e1e2e;color:#a6e3a1;font-weight:bold}";
  h += ".live{background:#a6e3a1;color:#1e1e2e;border-radius:20px;padding:2px 10px;font-size:.75em;font-weight:700;margin-left:8px}";
  h += "</style></head><body>";
  h += "<div class=top>";
  h += "<span>Sistema de Pesaje <span class=live>LIVE</span></span>";
  h += "<div class=btns>";
  h += "<button class='btn bb' onclick='location.href=\"/panel\"'>Panel</button>";
  h += "<button class='btn bg' onclick=descargar()>Descargar Reporte</button>";
  h += "<button class='btn by' onclick=reiniciar()>Reiniciar</button>";
  h += "<button class='btn br' onclick=logout()>Cerrar sesion</button>";
  h += "</div></div>";
  h += "<div class=wrap><h2>Registro de Cargas y Pagos</h2>";
  h += "<table>";
  h += "<thead><tr><th>#</th><th>Trabajador</th><th>Cargas</th><th>Peso Total</th><th>Pago Total COP</th></tr></thead>";
  h += "<tbody id=tbody></tbody>";
  h += "<tfoot><tr class=tot><td colspan=2>TOTALES</td>";
  h += "<td id=tc>0</td><td id=tp>0.000 g</td><td id=tpg>$0.000</td>";
  h += "</tr></tfoot></table></div>";
  h += "<script>";
  h += "function cargar(){";
  h += "fetch('/datos').then(function(r){return r.json();}).then(function(d){";
  h += "var h2='',tc=0,tp=0,tpg=0;";
  h += "for(var i=0;i<d.length;i++){";
  h += "tc+=d[i].cargas;tp+=d[i].peso;tpg+=d[i].pago;";
  h += "h2+='<tr><td>'+(i+1)+'</td><td>'+d[i].nombre+'</td>';";
  h += "h2+='<td>'+d[i].cargas+'</td>';";
  h += "h2+='<td>'+d[i].peso.toFixed(3)+' g</td>';";
  h += "h2+='<td>$'+d[i].pago.toFixed(3)+' COP</td></tr>';";  // ← 3 decimales
  h += "}";
  h += "document.getElementById('tbody').innerHTML=h2||'<tr><td colspan=5 style=text-align:center;color:#585b70;padding:20px>Esperando datos...</td></tr>';";
  h += "document.getElementById('tc').innerText=tc;";
  h += "document.getElementById('tp').innerText=tp.toFixed(3)+' g';";
  h += "document.getElementById('tpg').innerText='$'+tpg.toFixed(3)+' COP';";  // ← 3 decimales
  h += "});}";
  h += "function reiniciar(){";
  h += "if(!confirm('Reiniciar todos los contadores?'))return;";
  h += "fetch('/reiniciar').then(function(){cargar();});}";
  h += "function descargar(){";
  h += "var a=document.createElement('a');";
  h += "a.href='/reporte';a.download='reporte_cafetero.txt';";
  h += "document.body.appendChild(a);a.click();document.body.removeChild(a);}";
  h += "function logout(){";
  h += "descargar();";
  h += "setTimeout(function(){fetch('/logout').then(function(){location.href='/';});},1500);}";
  h += "cargar();setInterval(cargar,5000);";
  h += "</script></body></html>";
  req->send(200, "text/html", h);
}

void setup() {
  Serial.begin(115200);

  IPAddress ip(172, 20, 10, 5);
  IPAddress gateway(172, 20, 10, 1);
  IPAddress subnet(255, 255, 255, 240);
  IPAddress dns(8, 8, 8, 8);
  WiFi.config(ip, gateway, subnet, dns);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Conectando WiFi");
  int t = 0;
  while (WiFi.status() != WL_CONNECTED && t < 30) {
    delay(500); Serial.print("."); t++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("\nIP: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi no conectado");
  }

  configTime(-5 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(LORA_BAND)) {
    Serial.println("LoRa ERROR"); while (true);
  }
  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  Serial.println("LoRa OK 915MHz");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* req) { servirLogin(req); });

  server.on("/login", HTTP_GET, [](AsyncWebServerRequest* req) {
    if (req->hasParam("user") && req->hasParam("pass")) {
      if (req->getParam("user")->value() == LOGIN_USER &&
          req->getParam("pass")->value() == LOGIN_PASS) {
        sesionActiva = true;
        req->send(200, "text/plain", "OK");
      } else { req->send(200, "text/plain", "ERROR"); }
    } else { req->send(400); }
  });

  server.on("/panel", HTTP_GET, [](AsyncWebServerRequest* req) {
    if (!sesionActiva) { req->redirect("/"); return; }
    servirPanel(req);
  });

  server.on("/sistema", HTTP_GET, [](AsyncWebServerRequest* req) {
    if (!sesionActiva) { req->redirect("/"); return; }
    servirSistema(req);
  });

  server.on("/listaNombres", HTTP_GET, [](AsyncWebServerRequest* req) {
    if (!sesionActiva) { req->send(403); return; }
    req->send(200, "application/json", jsonNombres());
  });

  server.on("/lista", HTTP_GET, [](AsyncWebServerRequest* req) {
    req->send(200, "application/json", jsonNombres());
  });

  server.on("/agregarTrab", HTTP_GET, [](AsyncWebServerRequest* req) {
    if (!sesionActiva) { req->send(403); return; }
    if (!req->hasParam("nombre")) { req->send(400, "text/plain", "Falta nombre"); return; }
    if (numNombres >= MAX_TRAB) { req->send(200, "text/plain", "Maximo alcanzado"); return; }
    String n = req->getParam("nombre")->value();
    n.trim();
    if (n.length() == 0) { req->send(200, "text/plain", "Nombre vacio"); return; }
    nombresReg[numNombres++] = n;
    Serial.println("Agregado: " + n);
    req->send(200, "text/plain", "OK");
  });

  server.on("/eliminarTrab", HTTP_GET, [](AsyncWebServerRequest* req) {
    if (!sesionActiva) { req->send(403); return; }
    int id = req->getParam("id")->value().toInt();
    if (id < 0 || id >= numNombres) { req->send(400); return; }
    for (int i = id; i < numNombres - 1; i++) nombresReg[i] = nombresReg[i + 1];
    numNombres--;
    req->send(200, "text/plain", "OK");
  });

  server.on("/datos", HTTP_GET, [](AsyncWebServerRequest* req) {
    if (!sesionActiva) { req->send(403); return; }
    req->send(200, "application/json", jsonDatos());
  });

  server.on("/reiniciar", HTTP_GET, [](AsyncWebServerRequest* req) {
    if (!sesionActiva) { req->send(403); return; }
    for (int i = 0; i < numTrab; i++) {
      trab[i].cargas = 0; trab[i].pesoTotal = 0; trab[i].pagoTotal = 0;
    }
    req->send(200, "text/plain", "OK");
  });

  server.on("/reporte", HTTP_GET, [](AsyncWebServerRequest* req) {
    if (!sesionActiva) { req->send(403); return; }
    String r = generarReporte();
    AsyncWebServerResponse* res = req->beginResponse(200, "text/plain", r);
    res->addHeader("Content-Disposition", "attachment; filename=reporte_cafetero.txt");
    req->send(res);
  });

  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest* req) {
    sesionActiva = false;
    req->send(200, "text/plain", "OK");
  });

  server.begin();
  Serial.println("Servidor activo en 172.20.10.5");
}

void loop() {
  int tam = LoRa.parsePacket();
  if (tam > 0) {
    String pkt = "";
    while (LoRa.available()) pkt += (char)LoRa.read();
    Serial.print("LoRa RX (RSSI:");
    Serial.print(LoRa.packetRssi());
    Serial.print(" dBm): ");
    Serial.println(pkt);
    procesarLoRa(pkt);
  }
}