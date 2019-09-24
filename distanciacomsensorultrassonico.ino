#define trigPin D1
#define echoPin D2

void setup() {
  
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(trigPin, LOW);
}

long duracao;
float distancia, aux;

void loop() {

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH ,1000000);
  aux = duracao;
  distancia = (aux*340/10000)/2;
  Serial.print("Distancia: ");
  Serial.println(distancia);

  Serial.print("Duracao: ");
  Serial.println(duracao);


  if (distancia>= 1200)
  {
   digitalWrite(2, 1);
  }
  else if (distancia>= 1200 &&  distancia <= 40000)
  {
     digitalWrite(2, 0);  
    
  }

  
}
