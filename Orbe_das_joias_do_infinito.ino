// BlueBox 12
// Autor: Filipeflop

// Inclusão de bibliotecas nativas da IDE do Arduino
#include <SPI.h>
#include <Wire.h>
// Inclusão de bibliotecas instaladas
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
// Inclusão da página pitches.h
#include "pitches.h"

// Variáveis que recebem o tamanho da tela do OLED
const byte TELA_LARGURA = 128; // largura do OLED display, em pixels
const byte TELA_ALTURA = 32; // altura do OLED display, em pixels

// Declaração para o display SSD1306 conectar no modo I2C(pinos SDA e SCL)
const int OLED_RESET = -1; // Comando padrão para o Arduino não utilizar nenhum de seus pinos como reset para o display
Adafruit_SSD1306 display(TELA_LARGURA, TELA_ALTURA, &Wire, OLED_RESET); // Criação do objeto "display"

// Notas de "Come get your love"
int come_get[] = {
  NOTE_E1, NOTE_B0, NOTE_A1, NOTE_E1, NOTE_B0, NOTE_A1,
  NOTE_E1, NOTE_E1, NOTE_B0, NOTE_A1, NOTE_E1, NOTE_B0, NOTE_A1
};

// Duração das notas musicais de "Come get your love"
int duracao_come_get[] = {
  4, 8, 8, 4, 8, 4,
  8, 8, 8, 8, 8, 8, 8
};

// Notas de "Iron Man"
int iron_man[] = {
  NOTE_B5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_E5,
  NOTE_G5,
  NOTE_F5, NOTE_G5, NOTE_F5, NOTE_G5, NOTE_F5, NOTE_G5, NOTE_D5, NOTE_E5
};

// Duração das notas musicais de "Iron Man"
int duracao_iron_man[] = {
  4, 4, 8, 8, 4,
  8,
  16, 16, 16, 16, 8, 8, 8, 4
};

// Notas de "Pina Colada song"
int pina_colada[] = {
  NOTE_F1, NOTE_A2, NOTE_G1, NOTE_F1,
  NOTE_D2, NOTE_C1, NOTE_G1, NOTE_D2, NOTE_G2,
  NOTE_F1, NOTE_A2, NOTE_G1, NOTE_F1,
  NOTE_D2, NOTE_C1, NOTE_G1, NOTE_D2, NOTE_G2
};

// Duração das notas musicais de "Pina Colada song"
int duracao_pina_colada[] = {
  4, 4, 6, 2,
  4, 4, 6, 4, 2,
  4, 4, 6, 2,
  4, 4, 6, 4, 2
};

// Variáveis que indicam os pinos utilizados para o Sensor, Buzzer e Fita de Led
const int pinoSensor = 5;
const int pinoBuzzer = 4;
const int pinoLed = 6;

// Variável que indica o número de LEDs na fita
const int numLEDs = 8;

// Variável que indica vibração
bool vibrou = false; // Inicialmente falsa 

// Variável "seletora" de músicas e
// Variável que indica o número total de músicas no projeto
volatile byte musica = 1;
volatile byte musicaTotal = 3;

// Variável "seletora" de mensagens
// Variável que indica o número total de mensagens no projeto
volatile byte mensagem = 1;
volatile byte mensagemTotal = 3;

// Variável "seletora" de cores
// Variável que indica o número total de cores no projeto
volatile byte cor = 1;
volatile byte corTotal = 6;

// Criação do objeto "fitaLED" para uso da NeoPixel
Adafruit_NeoPixel fitaLED(numLEDs, pinoLed, NEO_GRB + NEO_KHZ800);

// Definição de algumas cores em formato RGB
uint32_t azul = fitaLED.Color(0,0,255);
uint32_t verde = fitaLED.Color(0,128,0);
uint32_t amarelo = fitaLED.Color(255,215,0);//(218,165,32);
uint32_t branco = fitaLED.Color(255,255,255);
uint32_t vermelho = fitaLED.Color(218,0,0);
uint32_t roxo = fitaLED.Color(128,0,128);//(138,43,226);

void setup() {

  // Configurando a comunicação serial com a interface da IDE do Arduino
  Serial.begin(9600);
  
  // Configurando entradas e saídas
  pinMode(pinoSensor, INPUT);
  pinMode(pinoBuzzer, OUTPUT);

  // Inicializando o objeto OLED e definindo o endereço I2C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Limpando o buffer
  display.clearDisplay();

  // Configurações básicas OLED
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Configurações básicas Fita de LED
  fitaLED.begin();
  fitaLED.show(); // Inicializando todos os LEDs para off

  // Avisando o usuário que o programa está inicializando
  Serial.println("BlueBox 12");
  Serial.println("Inicializando.");

}

void loop() {

  // Verificando vibração
  if(digitalRead(pinoSensor) == HIGH){
    Serial.println("O Arduino detectou vibração.");
    vibrou = true;
  }

  // Música tocando, letras passando e cores aparecendo
  while(vibrou){

    // De acordo com o contador da mensagem, uma mensagem diferente aparece no display
    if(mensagem == 1){
      Serial.println("Mensangem 1 aparecendo no display");
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("Quanto poder!");
      display.display();
      display.startscrollleft(0x00, 0x07);
    }
    else if(mensagem == 2) {
      Serial.println("Mensangem 2 aparecendo no display");
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("Eson...");
      display.display();
      display.startscrollleft(0x00, 0x07);
    } else {
      Serial.println("Mensangem 3 aparecendo no display");
      display.clearDisplay();
      display.setCursor(0,20);
      display.println("Que universo!");
      display.display();
      display.startscrollleft(0x00, 0x07);
    }

    // De acordo com o contador da cor da FitaLED, a cor vai variar
    if(cor == 1){
      Serial.println("Cor branca na fita de LED");
      fitaLED.clear();
      fitaLED.fill(branco, 0);
      fitaLED.show();
    }
    else if(cor == 2){
      Serial.println("Cor verde na fita de LED");
      fitaLED.clear();
      fitaLED.fill(verde, 0);
      fitaLED.show();
    }
    else if(cor == 3){
      Serial.println("Cor vermelha na fita de LED");
      fitaLED.clear();
      fitaLED.fill(vermelho, 0);
      fitaLED.show();
    }
    else if(cor == 4){
      Serial.println("Cor azul na fita de LED");
      fitaLED.clear();
      fitaLED.fill(azul, 0);
      fitaLED.show();
    }
    else if(cor == 5){
      Serial.println("Cor amarelo na fita de LED");
      fitaLED.clear();
      fitaLED.fill(amarelo, 0);
      fitaLED.show();
    } else {
      Serial.println("Cor roxo na fita de LED");
      fitaLED.clear();
      fitaLED.fill(roxo, 0);
      fitaLED.show();
    }

    // A partir do contador "musica", define-se qual música vai tocar
    if(musica == 1){
      Serial.println("Tocando a música 'Come get your love'");
      // Percorrendo cada nota de "Come get your love" e tocando ele no Buzzer
      for (int nota = 0; nota < 13; nota++) {

      // Calculando a duração da nota a partir das oitavas definidas em "duracaoNotas"
      int duracaoNota = 1000 / duracao_come_get[nota] * 2;
      // Ativa o buzzer com a nota percorrida pelo for loop e pelo tempo determinado em duracaoNotas
      tone(pinoBuzzer, come_get[nota], duracaoNota);
  
      // Para distinguir as notas, é importante fazer uma pausa entre elas
      // A duração de uma nota + 30% dessa duração funciona bem!
      int pausaEntreNotas = duracaoNota * 1.30;
      delay(pausaEntreNotas);
      // Faz com que o buzzer pare de tocar
      noTone(pinoBuzzer);
    }
      
      // Colocar próxima música na sequência para ser tocada
      if(musica == musicaTotal){
        musica = 1;
      } else {
        musica++;
      }

      //Colocar próxima mensagem na sequência para aparecer no OLED
      if(mensagem == mensagemTotal){
        mensagem = 1;
      } else {
        mensagem++;
      }

      //Colocar próxima cor na sequência para aparecer na Fita
      if(cor == corTotal){
        cor = 1;
      } else {
        cor++;
      }
      
      // Depois da música, o while loop precisa ser interrompido
      // para o sistema poder receber novo estímulo de vibração
      vibrou = false;
    }
    else if(musica == 2){
      Serial.println("Tocando a música 'Iron Man'");
      // Percorrendo cada nota de "Iron Man"
      for (int nota = 0; nota < 16; nota++) {

        // Calculando a duração da nota a partir das oitavas definidas em "duracaoNotas"
        int duracaoNota = 1000 / duracao_iron_man[nota] * 2;
        // Ativa o buzzer com a nota percorrida pelo for loop e pelo tempo determinado em duracaoNotas
        tone(pinoBuzzer, iron_man[nota], duracaoNota);
    
        // Para distinguir as notas, é importante fazer uma pausa entre elas
        // A duração de uma nota + 30% dessa duração funciona bem!
        int pausaEntreNotas = duracaoNota * 1.30;
        delay(pausaEntreNotas);
        // Faz com que o buzzer pare de tocar
        noTone(pinoBuzzer);
      }
      
      // Colocar na sequência para ser tocada
      if(musica == musicaTotal){
        musica = 1;
      } else {
        musica++;
      }

      //Colocar próxima mensagem na sequência para aparecer no OLED
      if(mensagem == mensagemTotal){
        mensagem = 1;
      } else {
        mensagem++;
      }

      //Colocar próxima cor na sequência para aparecer na Fita
      if(cor == corTotal){
        cor = 1;
      } else {
        cor++;
      }
      
      // Depois da música, o while loop precisa ser interrompido
      // para o sistema poder receber novo estímulo de vibração
      vibrou = false; 
    } else {
      Serial.println("Tocando a música 'Pina Colada' is coming to town'");
      // Percorrendo cada nota de "Pina Colada"
      for (int nota = 0; nota < 18; nota++) {

        // Calculando a duração da nota a partir das oitavas definidas em "duracaoNotas"
        int duracaoNota = 1000 / duracao_pina_colada[nota] * 2;
        // Ativa o buzzer com a nota percorrida pelo for loop e pelo tempo determinado em duracaoNotas
        tone(pinoBuzzer, pina_colada[nota], duracaoNota);
    
        // Para distinguir as notas, é importante fazer uma pausa entre elas
        // A duração de uma nota + 30% dessa duração funciona bem!
        int pausaEntreNotas = duracaoNota * 1.30;
        delay(pausaEntreNotas);
        // Faz com que o buzzer pare de tocar
        noTone(pinoBuzzer);
      }
      
      // Colocar na sequência para ser tocada
      if(musica == musicaTotal){
        musica = 1;
      } else {
        musica++;
      } 

      //Colocar próxima mensagem na sequência para aparecer no OLED
      if(mensagem == mensagemTotal){
        mensagem = 1;
      } else {
        mensagem++;
      }

      //Colocar próxima cor na sequência para aparecer na Fita
      if(cor == corTotal){
        cor = 1;
      } else {
        cor++;
      }
      
      // Depois da música, o while loop precisa ser interrompido
      // para o sistema poder receber novo estímulo de vibração
      vibrou = false;
    }
  }
}
