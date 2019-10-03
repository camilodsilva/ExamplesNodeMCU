#include <ESP8266WiFi.h>

// nome da rede
const char* ssid = "linopunk";
// senha da rede
const char* password = "12345678";

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
      
        buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
        buf += "<!DOCTYPE html>";
        buf += "<html>";
        buf += "<head>";
        buf += "    <meta charset=\"utf-8\" />";
        buf += "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">";
        buf += "    <title>BSA QUIZ</title>";
        buf += "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
        buf += "    <style>";
        buf += "        * {";
        buf += "            margin: 0;";
        buf += "            padding: 0;";
        buf += "            outline: 0;";
        buf += "            box-sizing: border-box;";
        buf += "        }";
        buf += "";
        buf += "        html,";
        buf += "        body {";
        buf += "            font-family: Calibri;";
        buf += "            height: 100%;";
        buf += "        }";
        buf += "";
        buf += "        body {";
        buf += "            background-color: #e8e8e8;";
        buf += "        }";
        buf += "";
        buf += "        header {";
        buf += "            display: flex;";
        buf += "            justify-content: center;";
        buf += "        }";
        buf += "";
        buf += "        header div {";
        buf += "            font-size: 50px;";
        buf += "            padding: 70px 100px;";
        buf += "            color: #168460;";
        buf += "        }";
        buf += "";
        buf += "        section {";
        buf += "            display: flex;";
        buf += "            flex-direction: column;";
        buf += "            justify-content: flex-start;";
        buf += "            align-items: center;";
        buf += "            text-align: center;";
        buf += "            height: 70%;";
        buf += "        }";
        buf += "";
        buf += "        .title-container {";
        buf += "            padding: 50px;";
        buf += "            font-size: 25px;";
        buf += "            width: 70%;";
        buf += "            border: 1px solid #ddd;";
        buf += "            box-shadow: 0px 0px 3px 2px #cac3c3;";
        buf += "            background-color: #fff;";
        buf += "            color: #444";
        buf += "        }";
        buf += "";
        buf += "        .question-container {";
        buf += "            display: flex;";
        buf += "            justify-content: center;";
        buf += "            align-items: center;";
        buf += "            margin: 20px;";
        buf += "            height: auto;";
        buf += "            width: 70%;";
        buf += "            border: 1px solid #ddd;";
        buf += "            box-shadow: 0px 0px 3px 2px #cac3c3;";
        buf += "            background-color: #fff;";
        buf += "        }";
        buf += "";
        buf += "        .questions {";
        buf += "            list-style: none;";
        buf += "            line-height: 50px;";
        buf += "            width: 100%;";
        buf += "        }";
        buf += "";
        buf += "        li:first-child {";
        buf += "            color: #444;";
        buf += "            border-top: none;";
        buf += "        }";
        buf += "";
        buf += "        li {";
        buf += "            color: #444;";
        buf += "            cursor: pointer;";
        buf += "            border-top: 1px solid #cac3c3;";
        buf += "            padding: 15px 240px;";
        buf += "            transition: all 0.3s;";
        buf += "            font-size: 20px;";
        buf += "        }";
        buf += "";
        buf += "        li:hover {";
        buf += "            background-color: #16846057;";
        buf += "        }";
        buf += "";
        buf += "        .question-selected {";
        buf += "            color: #fff !important;";
        buf += "            background-color: #168460;";
        buf += "        }";
        buf += "";
        buf += "        a {";
        buf += "            text-decoration: none;";
        buf += "            color:  #168460;";
        buf += "        }";
        buf += "    </style>";
        buf += "</head>";
        buf += "<body>";
        buf += "    <header>";
        buf += "        <div>";
        buf += "            BSA Quiz";
        buf += "        </div>";
        buf += "    </header>";
        buf += "    <section>";
        buf += "        <div class=\"title-container\" id=\"done\">";
        buf += "            <a href=\"http://192.168.43.58/\">Done!</a>";
        buf += "        </div>";
        buf += "        <div class=\"title-container\" id=\"questionTitle\">Question title placeholder?</div>";
        buf += "        <div id=\"questions\" class=\"question-container\">";
        buf += "            <ul class=\"questions\">";
        buf += "                <li id=\"option1\">options a</li>";
        buf += "                <li id=\"option2\">options b</li>";
        buf += "                <li id=\"option3\">options c</li>";
        buf += "                <li id=\"option4\">options d</li>";
        buf += "                <li id=\"option5\">options e</li>";
        buf += "            </ul>";
        buf += "        </div>";
        buf += "    </section>";
        buf += "";
        buf += "    <script>";
        buf += "        (function() {";
        buf += "            questions = [";
        buf += "                {";
        buf += "                    \"title\": \"This is the first question\", ";
        buf += "                    \"options\": [";
        buf += "                        {'text': 'The answer for the first question (a)', 'isCorrect': 'yes'},";
        buf += "                        {'text': 'The answer for the first question (b)', 'isCorrect': 'no'},";
        buf += "                        {'text': 'The answer for the first question (c)', 'isCorrect': 'no'},";
        buf += "                        {'text': 'The answer for the first question (d)', 'isCorrect': 'no'},";
        buf += "                        {'text': 'The answer for the first question (e)', 'isCorrect': 'no'},";
        buf += "                    ]";
        buf += "                },";
        buf += "                {";
        buf += "                    \"title\": \"This is the first question 2\",";
        buf += "                    \"options\": [";
        buf += "                        { 'text': 'The answer for the first question 2 (a)', 'isCorrect': 'yes' },";
        buf += "                        { 'text': 'The answer for the first question 2 (b)', 'isCorrect': 'no' },";
        buf += "                        { 'text': 'The answer for the first question 2 (c)', 'isCorrect': 'no' },";
        buf += "                        { 'text': 'The answer for the first question 2 (d)', 'isCorrect': 'no' },";
        buf += "                        { 'text': 'The answer for the first question 2 (e)', 'isCorrect': 'no' },";
        buf += "                    ]";
        buf += "                },";
        buf += "                {";
        buf += "                    \"title\": \"This is the first question 3\",";
        buf += "                    \"options\": [";
        buf += "                        { 'text': 'The answer for the first question 3 (a)', 'isCorrect': 'no' },";
        buf += "                        { 'text': 'The answer for the first question 3 (b)', 'isCorrect': 'no' },";
        buf += "                        { 'text': 'The answer for the first question 3 (c)', 'isCorrect': 'no' },";
        buf += "                        { 'text': 'The answer for the first question 3 (d)', 'isCorrect': 'no' },";
        buf += "                        { 'text': 'The answer for the first question 3 (e)', 'isCorrect': 'yes' },";
        buf += "                    ]";
        buf += "                },";
        buf += "                {";
        buf += "                    \"title\": \"This is the first question 4\",";
        buf += "                    \"options\": [";
        buf += "                        { 'text': 'The answer for the first question 4 (a)', 'isCorrect': 'no' },";
        buf += "                        { 'text': 'The answer for the first question 4 (b)', 'isCorrect': 'no' },";
        buf += "                        { 'text': 'The answer for the first question 4 (c)', 'isCorrect': 'no' },";
        buf += "                        { 'text': 'The answer for the first question 4 (d)', 'isCorrect': 'yes' },";
        buf += "                        { 'text': 'The answer for the first question 4 (e)', 'isCorrect': 'no' },";
        buf += "                    ]";
        buf += "                },";
        buf += "            ];";
        buf += "";
        buf += "            number = getQueryParam('number');";
        buf += "            done(number);";
        buf += "";
        buf += "            index = nextQuestion();";
        buf += "            question = (questions[index] !== undefined ? questions[index] : questions[0]);";
        buf += "";
        buf += "            start(number);";
        buf += "            loadQuestions(question);";
        buf += "            setCorrectAnswer(question);";
        buf += "        })();";
        buf += "";
        buf += "        function start(number) {";
        buf += "            const li = document.getElementsByTagName('li');";
        buf += "            ";
        buf += "            for(i=0; i<li.length; i++) {";
        buf += "                li[i].addEventListener('click', function(e) {";
        buf += "                    for (j = 0; j < li.length; j++)";
        buf += "                        li[j].removeAttribute('class');";
        buf += "";
        buf += "                    this.setAttribute('class', 'question-selected');";
        buf += "                    ";
        buf += "                    const isCorrect = this.getAttribute('data-correct');";
        buf += "                    const url = buildUrl(++number, isCorrect);";
        buf += "";
        buf += "                    window.location.href = url;";
        buf += "                });";
        buf += "            }";
        buf += "        }";
        buf += "";
        buf += "        function loadQuestions(question) {";
        buf += "            document.getElementById('questionTitle').innerHTML = question.title;";
        buf += "";
        buf += "            const li = document.getElementsByTagName('li');";
        buf += "";
        buf += "            for (i = 0; i < li.length; i++) {";
        buf += "                li[i].innerHTML = question.options[i].text;";
        buf += "            }";
        buf += "        }";
        buf += "";
        buf += "        function setCorrectAnswer(question) {";
        buf += "            const li = document.getElementsByTagName('li');";
        buf += "";
        buf += "            for (i = 0; i < li.length; i++) {";
        buf += "                li[i].setAttribute('data-correct', question.options[i].isCorrect);";
        buf += "            }";
        buf += "        }";
        buf += "";
        buf += "        function getQueryParam(key) {";
        buf += "            var params = new URLSearchParams(window.location.search);";
        buf += "            ";
        buf += "            return params.get(key) !== undefined ? params.get(key) : 0;";
        buf += "        }";
        buf += "";
        buf += "        function buildUrl(number, isCorrect) {";
        buf += "            const url = `http://192.168.43.58/?number=${number}&correct=${isCorrect}`;";
        buf += "";
        buf += "            return url;";
        buf += "        }";
        buf += "";
        buf += "        function nextQuestion() {";
        buf += "            return Math.floor(Math.random() * 4);";
        buf += "        }";
        buf += "";
        buf += "        function done(number) {";
        buf += "            if (number >= 3) {";
        buf += "                document.getElementById('done').style.display = 'block';";
        buf += "                document.getElementById('questionTitle').style.display = 'none';";
        buf += "                document.getElementById('questions').style.display = 'none';";
        buf += "            } else {";
        buf += "                document.getElementById('done').style.display = 'none';";
        buf += "                document.getElementById('questionTitle').style.display = 'block';";
        buf += "                document.getElementById('questions').style.display = 'block';";
        buf += "            }";
        buf += "        }";
        buf += "    </script>";
        buf += "</body>";
        buf += "</html>";

        Serial.println(req);

        //Enviando para o browser a 'pagina' criada.
        client.print(buf);
       
        client.flush();

        if (req.indexOf("correct=yes") != -1)
        {
             digitalWrite(5, 1);

             delay(2000);

             digitalWrite(5, 0);
        }
        else if (req.indexOf("correct=no") != -1)
        {
         digitalWrite(5, 0);
        }
    } 
}
