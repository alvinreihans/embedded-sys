int led1 = D0;
int led2 = D1;
int led3 = D2;
int led4 = D3;
int led5 = D4;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

void loop() {
  digitalWrite(led2, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led1, HIGH);
  digitalWrite(led3, HIGH);
  delay(350);
  digitalWrite(led1, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led4, HIGH);
  delay(350);
  digitalWrite(led2, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led5, HIGH);
  delay(350);
  digitalWrite(led3, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led1, HIGH);
  digitalWrite(led4, HIGH);
  delay(350);
  digitalWrite(led4, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led5, HIGH);
  delay(350);
}
