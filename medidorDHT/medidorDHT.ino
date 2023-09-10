// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Substitua pelas suas credenciais de rede
const char* ssid = "Casa 01";
const char* password = "08951329666";

#define DHTPIN 27     // Pino digital conectado ao sensor DHT

//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT11     

DHT dht(DHTPIN, DHTTYPE);

// Cria o objeto AsyncWebServer na porta 80.
AsyncWebServer server(80);

String readDHTTemperature() {
  // As leituras do sensor também podem ter até 2 segundos 
  // Ler a temperatura como Celsius (o padrão)
  float t = dht.readTemperature();
  // Leia a temperatura como Fahrenheit (isFahrenheit = true)
  //float t = dht.lerTemperatura(verdadeira);
  // Verifica se alguma leitura falhou e sai mais cedo (para tentar novamente).
  if (isnan(t)) {    
    Serial.println("Falha ao ler o sensor DHT!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity() {
  // SAs leituras do sensor também podem ter até 2 segundos.
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>Sistema DHT</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperatura</span> 
    <span id="temperatura">%TEMPERATURA%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidade</span>
    <span id="humidade">%HUMIDADE%</span>
    <sup class="units">&percnt;</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperatura").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperatura", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidade").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidade", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// substitui o espaço reservado por valores DHT
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURe"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  return String();
}

void setup(){
  // Serial porta para fins de depuração
  Serial.begin(9600);

  dht.begin();
  
  // Connectar a Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Tela ESP32 Local IP Endereço
  Serial.println(WiFi.localIP());

  // Rota para raiz/página da web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperatura", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidade", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });

  // Inicio Servidor
  server.begin();
}
 
void loop(){
  
}

