#include <ESP8266WiFi.h>

// nome da rede
const char* ssid = "*******";
// senha da rede
const char* password = "*********";

WiFiServer server(80); //Shield irá receber as requisições das páginas (o padrão WEB é a porta 80)


void setup()
{         
    pinMode(5, OUTPUT);
    Serial.begin(115200);

    //Conexão na rede WiFi
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi conectado!");

    // Inicia o servidor WEB
    server.begin();
    Serial.println("Server iniciado");

    // Mostra o endereco IP
    Serial.println(WiFi.localIP());

   
}

void loop()
{

    WiFiClient  client = server.available();
 
    if (client) { 
        
        String req = client.readStringUntil('\r');
        
         //Iniciando o buffer que ira conter a pagina HTML que sera enviada para o browser.
        String buf = "";
      
        buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
        buf += "<h3>ESP8266 Servidor Web</h3>";
        buf += "<p>LED <a href=\"?function=led2_on\"><button>LIGA</button></a><a href=\"?function=led2_off\"><button>DESLIGA</button></a></p>";
        buf += "</html>\n";
      
        //Enviando para o browser a 'pagina' criada.
        client.print(buf);
       
        client.flush();

        if (req.indexOf("led2_on") != -1)
        {
             digitalWrite(5, 1);
        }
        else if (req.indexOf("led2_off") != -1)
        {
         digitalWrite(5, 0);
        }
    } 
}
