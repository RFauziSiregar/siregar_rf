int Xa[5];
boolean bin_Xa[5][8], child_Xa[5][8];
float result_Xa[5];
float optimum, minimum, sum;
float function[5];
float BB = -5.12;
float BA = 5.12;
float F[5];
float Fn[5];
float Value_Xa;
float parent[2];
int it_parent[2];
int repeat=0;
int getvalue;
int roulete;

void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(A0));
  Serial.begin(9600);

  //1. Awakening Pupulation
  //Encoding
  for(int i=0; i<5; i++){ 
    Xa[i] = random(1,255);
    dectobin(Xa[i],bin_Xa[i]);
  }

 // float tim = millis(); 
  while(optimum <0.009){
    //Decoding
    for(int i=0; i<5; i++){
      Xa[i] = bintodec(bin_Xa[i]);
      result_Xa[i] = BB + (BA - BB) / 255 * Xa[i];
    }

    //2. Evalution 
    //Calculate Output Function
    for(int i=0; i<5; i++){
      function[i] = 13 + pow((result_Xa[i] - 5.0), 2);
    }

    //Calculate Fitness
    optimum=0.0; minimum=10.0; sum=0.0;
    for(int i=0; i<5; i++){
      F[i] = 1.0 / (function[i] + 0.1);
      if(optimum < F[i]){
        optimum = F[i];
        getvalue = i;
        for(int j=0; j<8; j++){
          child_Xa[0][j] = bin_Xa[i][j];
        }
      }
      if(minimum > F[i]){
        minimum = F[i];
      }
    }

    for(int i=0; i<5; i++){
      Fn[i] = F[i] - minimum;
      sum = sum + Fn[i];
    }

    for(int i=0; i<5; i++){
      Fn[i] = F[i] / sum * 100.0;
    }

   Value_Xa = (float) bintodec(child_Xa[0]) / 255.0 * (BA-BB) + BB;
   Serial.print("iteration:");
   Serial.println(repeat+1);
   Serial.print("Value of (F):");
   Serial.println(optimum);
   Serial.print("Value of (X):");
   Serial.println(Value_Xa);
   Serial.print("Value of (Y):");
   Serial.println(function[getvalue]);
   repeat++;

    //3. Roulete Wheel
    parent[0] = random(1,99); 
    parent[1] = random(1,99);
    it_parent[0] = 0; 
    it_parent[1] = 0;
    for(int i=0; i<5; i++){
      parent[0]-=Fn[i]; 
      parent[1]-=Fn[i];
      if(parent[0] <= 0 && it_parent[0] == 0){
        it_parent[0] = i;
      }
      if(parent[1] <= 0 && it_parent[1] == 0){
        it_parent[1] = i; 
      }
    }

   //4. Cross Over
   //child-2
   for(int i=0; i<3; i++){
    child_Xa[1][i] = bin_Xa[it_parent[0]][i];
   }
   for(int i=3; i<8; i++){
    child_Xa[1][i] = bin_Xa[it_parent[1]][i];
   }
   //child-3
   for(int i=0; i<3; i++){
    child_Xa[2][i] = bin_Xa[it_parent[1]][i];
   }
   for(int i=3; i<8; i++){
    child_Xa[2][i] = bin_Xa[it_parent[0]][i];
   }
   //child-4
   for(int i=0; i<6; i++){
    child_Xa[3][i] = bin_Xa[it_parent[0]][i];
   }
   for(int i=6; i<8; i++){
    child_Xa[3][i] = bin_Xa[it_parent[1]][i];
   }
   //child-5
   for(int i=0; i<6; i++){
    child_Xa[4][i] = bin_Xa[it_parent[1]][i];
   }
   for(int i=6; i<8; i++){
    child_Xa[4][i] = bin_Xa[it_parent[0]][i];
   }

   //5. Mutation
   for(int i=0; i<5; i++){
    roulete = random(2,8);
    child_Xa[i][roulete]^=1;
   }
   for(int i=0; i<5; i++){
    for(int j=0; j<8; j++){
      bin_Xa[i][j] = child_Xa[i][j];
    }
   }

  }
 // float timend = millis() - tim;
 // Serial.print("Millis:");
 // Serial.println(timend);

}

void loop() {
  // put your main code here, to run repeatedly:
  

}

void dectobin(int dec, boolean bin[]){
  for(int i=7; i>=0 ; i--){
    if(pow(2, i) <= dec){
      dec = dec - pow(2, i);
      bin[8-(i+1)] = 1;
    }
  }
}

int bintodec(boolean bin[]){
  int dec = 0;
  for(int i=7; i>=0; i--){
    int power = 1;
    for(int j=1; j<=i; j++){
      power*=2;
    }
    dec = dec + (bin[7-i]*power);
  }
  return dec;
}
