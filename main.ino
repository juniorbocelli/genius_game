//-----------------------#define e Variáveis------------------------//
#define LED_A 4
#define LED_B 5
#define LED_C 6
#define LED_D 7
 
#define BUTTON_A 8
#define BUTTON_B 9
#define BUTTON_C 10
#define BUTTON_D 11
 
#define BUZZER 12
 
#define TOM_A 1200
#define TOM_B 1600
#define TOM_C 2000
#define TOM_D 2400
 
#define TEMPO_PISCA 600
#define TEMPO_ENTRE 150

#define NIVEL_MAXIMO 10
 
int QT_SEQ = 1;

int GANHANDO = 0;

int TIPO_JOGO = 0;
 
int sorteados[NIVEL_MAXIMO]; // QT_SEQ é o tamanho da sequência dos leds
 
//--------------Declaração da função de cada elemento---------------//
void setup(){
  //Serial.begin(9600);
  
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_D, OUTPUT);
  
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);
  
  pinMode(BUZZER, OUTPUT);
  
  //randomSeed(analogRead(0)); //Sorteia uma nova sequencia toda vez que liga o Arduino
}
 
//----------Loop do sorteio, leitura de botão e comparação----------//
void loop(){
  //Acende tudo
  digitalWrite(LED_A, HIGH);
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_C, HIGH);
  digitalWrite(LED_D, HIGH);
  
  //le_botao(); //Jogador aperta qlqer botão e já inicia o sorteio
  
  if(le_botao() != -1){
    GANHANDO = 1;
    QT_SEQ = 1;
    TIPO_JOGO = le_botao();
  }
  
  //Apaga tudo
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_C, LOW);
  digitalWrite(LED_D, LOW);
  delay(500);
  
  if(TIPO_JOGO == 0){
    while(GANHANDO == 1 && QT_SEQ <= NIVEL_MAXIMO){
      
      //-----------------------Sorteio da sequência-----------------------//
      //QT_SEQ é o tamanho da sequência - quantas vezes os LEDs piscam
      for(int jogada = 0; jogada < QT_SEQ; jogada ++){
        if(jogada == QT_SEQ - 1){
          sorteados[jogada] = random(4);
        }
        pisca_led(sorteados[jogada]);
        delay(TEMPO_ENTRE);
      }//Fim do sorteio
      
      //---------------------Comparação da sequência----------------------//
      int vez; //Definido fora do for para poder verificar numero de acertos no final
      for(vez = 0; vez < QT_SEQ; vez ++){
        if(le_botao() == sorteados[vez]){
          pisca_led(sorteados[vez]);
        }else{
          pisca_led(sorteados[vez]);
          break; //Sai do for
        }
      }
      
      //----------------------------Resultado-----------------------------//
      if(vez == QT_SEQ){
        //Acertou a sequência
        delay(500);
        QT_SEQ = QT_SEQ + 1;
      }else{
        //Errou a sequência
        delay(500);
        for(int i = 0; i < 3; i++){
          tone(BUZZER, 200);
          delay(200);
          tone(BUZZER, 300);
          delay(200);
        }
        noTone(BUZZER);
        GANHANDO = 0;
      }
    }
    //Se venceu todos o NIVEL_MAXIMO, toca música da vitória
    if(GANHANDO == 1){
      for(int i = 0; i < 3; i++){
        tone(BUZZER, 2000);
        delay(200);
        tone(BUZZER, 4000);
        delay(200);
      }
      noTone(BUZZER);
      GANHANDO = 0;
    }
  }else if(TIPO_JOGO == 1){
    while(GANHANDO == 1 && QT_SEQ <= NIVEL_MAXIMO){
      //-----------------------Sorteio da sequência-----------------------//
      //QT_SEQ é o tamanho da sequência - quantas vezes os LEDs piscam
      for(int jogada = 0; jogada < QT_SEQ; jogada ++){
        sorteados[jogada] = random(4);
        pisca_led(sorteados[jogada]);
        delay(TEMPO_ENTRE);
      } //Fim do sorteio
      
      //---------------------Comparação da sequência----------------------//
      int vez; //Definido fora do for para poder verificar numero de acertos no final
      for(vez = 0; vez < QT_SEQ; vez ++){
        if(le_botao() == sorteados[vez]){
          pisca_led(sorteados[vez]);
        }else{
          pisca_led(sorteados[vez]);
          break; //Sai do for
        }
      }
      //----------------------------Resultado-----------------------------//
      if(vez == QT_SEQ){
        //Acertou a sequência
        delay(500);
        for(int i = 0; i < 3; i++){
          tone(BUZZER, 2000);
          delay(200);
          tone(BUZZER, 4000);
          delay(200);
        }
        QT_SEQ = QT_SEQ + 1;
        noTone(BUZZER);
      }else{
        //Errou a sequência
        delay(500);
        for(int i = 0; i < 3; i++){
          tone(BUZZER, 200);
          delay(200);
          tone(BUZZER, 300);
          delay(200);
        }
        noTone(BUZZER);
        GANHANDO = 0;
      }
    }
  }
} //Fim do loop
 
//------------------------Função piscar LED-------------------------//
void pisca_led(int posicao){
  Serial.println(posicao);
  if(posicao == 0){
    digitalWrite(LED_A, HIGH);
    tone(BUZZER, TOM_A);
    delay(TEMPO_PISCA);
    digitalWrite(LED_A, LOW);
  }else if(posicao == 1){
    digitalWrite(LED_B, HIGH);
    tone(BUZZER, TOM_B);
    delay(TEMPO_PISCA);
    digitalWrite(LED_B, LOW);
  }else if(posicao == 2){
    digitalWrite(LED_C, HIGH);
    tone(BUZZER, TOM_C);
    delay(TEMPO_PISCA);
    digitalWrite(LED_C, LOW);
  }else if(posicao == 3){
    digitalWrite(LED_D, HIGH);
    tone(BUZZER, TOM_D);
    delay(TEMPO_PISCA);
    digitalWrite(LED_D, LOW);
  }
  delay(100);
  noTone(BUZZER);
}//Fim do pisca_led

//------------------------Função ler os botões----------------------//
int le_botao(){
  int result = -1; //-1 indica que nenhum botão foi apertado
  while(result == -1){
    if(digitalRead(BUTTON_A) == LOW){
      result = 0;
    }else if(digitalRead(BUTTON_B) == LOW){
      result = 1;
    }else if(digitalRead(BUTTON_C) == LOW){
      result = 2;
    }else if(digitalRead(BUTTON_D ) == LOW){
      result = 3;
    }
  }
  return result; //Retorna o inteiro int le_botao
}