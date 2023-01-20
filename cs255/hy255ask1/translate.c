/*Anagnwstakis Emmanouil
  Askisi 1
  translate.c*/
#include <stdio.h>

void initializeLowerGR(char lowerGR[25]);
void initializeLowerENG(char lowerENG[25]);
void initializeUpperGR(char upperGR[24]);
void initializeUpperENG(char upperENG[24]);
void initializeUpperGRMT(char upperGRMT[7]);
void initializeLowerGRMT(char lowerGRMT[7]);

/*topo8etei ston pinaka pou pernei san orisma
ta mikra grammata tou ellinikou alfavitou*/
void initializeLowerGR(char lowerGR[25]){
    int i;
    for(i = 225; i <= 249; i++){
       lowerGR[i-225] = (char)i;
    }
}

/*topo8etei ston pinaka pou pernei san orisma
stis antistoixes 8eseis tou pinaka twn mikrwn ellinikwn
ta grammata twn mikrwn agglikwn xarakthrwn pou apaitounai gia tin
antikatastash*/
void initializeLowerENG(char lowerENG[25]){
    int i;
    char c = 'a';
    for(i = 0; i < 25; i++){
       if(c == 'b'){
          lowerENG[i] = 'v';
       }
       else if(c == 'c'){
          lowerENG[i] = 'g';
       }
       else if(c == 'f'){
          lowerENG[i] = 'z';
       }
       else if(c == 'g'){
          lowerENG[i] = 'h';
       }
       else if(c == 'h'){
          lowerENG[i] = '8';
       }
       else if(c == 'j'){
          lowerENG[i] = 'k';
       }
       else if(c == 'k'){
          lowerENG[i] = 'l';
       }
       else if(c == 'l'){
          lowerENG[i] = 'm';
       }
       else if(c == 'm'){
          lowerENG[i] = 'n';
       }
       else if(c == 'q'){
          lowerENG[i] = 'r';
       }
       else if(c == 'r'){
          lowerENG[i] = 's';
       }
       else if(c == 'u'){
          lowerENG[i] = 'y';
       }
       else if(c == 'v'){
          lowerENG[i] = 'f';
       }
       else if(c == 'w'){
          lowerENG[i] = 'x';
       }
       else{
          lowerENG[i] = c;
       }
       c++;
    }

    lowerENG[24]='w';
}

/*Pernei enan pinaka san orisma kai ton arxikopoiei me
ta kefalaia grammata tou ellinikou alfabitou.*/
void initializeUpperGR(char upperGR[24]){
    int i;
    for(i = 193; i <= 217; i++){
       if(i == 210){
          continue;
       }
       if(i < 210){
          upperGR[i-193] = (char)i;
       }
       if(i > 210){
          upperGR[i-194] = (char)i;
       }
    }
}

/*Pernei enan pinaka san orisma kai topothetei stis antistoixes
8eseis me ton upperGR ta agglika grammata pou apaitountai gia na
ginei h swsth antistoixish.*/
void initializeUpperENG(char upperENG[24]){
     int i;
     char c = 'A';
     for(i = 0; i < 24; i++){
          if(c == 'B'){
             upperENG[i] = 'V';
          }
          else if(c == 'C'){
             upperENG[i] = 'G';
          }
          else if(c == 'F'){
             upperENG[i] = 'Z';
          }
          else if(c == 'G'){
             upperENG[i] = 'H';
          }
          else if(c == 'H'){
             upperENG[i] = '8';
          }
          else if(c == 'J'){
             upperENG[i] = 'K';
          }
          else if(c == 'K'){
             upperENG[i] = 'L';
          }
          else if(c == 'L'){
             upperENG[i] = 'M';
          }
          else if(c == 'M'){
             upperENG[i] = 'N';
          }
          else if(c == 'Q'){
             upperENG[i] = 'R';
          }
          else if(c == 'R'){
             upperENG[i] = 'S';
          }
          else if(c == 'S'){
             upperENG[i] = 'T';
          }
          else if(c == 'T'){
             upperENG[i] = 'Y';
          }
          else if(c == 'U'){
             upperENG[i] = 'F';
          }
          else if(c == 'V'){
             upperENG[i] = 'X';
          }
          else if(c == 'X'){
             upperENG[i] = 'W';
          }
          else{
            upperENG[i] = c;
          }
          c++;
     }
}

/*Pernei enan pinaka san orisma kai topothetei se
ayton ta mikra grammata tou ellhnikou alfabitou
me tono.*/
void initializeLowerGRMT(char lowerGRMT[7]){
   int i;
   for(i = 220; i <= 223; i++){
       lowerGRMT[i-220] = (char)i;
   }

   for(i = 252; i <= 254; i++){
      lowerGRMT[i-248] = (char)i;
   }
}

/*Pernei enan pinaka san orisma kai topothetei se
ayton ta kefalaia grammata tou ellinikou alfabitou
me tono.*/
void initializeUpperGRMT(char upperGRMT[7]){
    int i;
    for(i = 182; i <= 191; i++){
       if(i == 183 || i == 187 || i == 189){
          continue;
       }
       else if(i == 182){
          upperGRMT[i-182] = (char)i;
       }
       else if(i > 183 && i < 187){
          upperGRMT[i-183] = (char)i;
       }
       else if(i == 188){
          upperGRMT[i-184] = (char)i;
       }
       else if(i > 189){
          upperGRMT[i-185] = (char)i;
       }
    }
}

/*Periexei 6 katastaseis gia tin ylopoihsh tou kanona 4.
H NOTHING ousiastika xrhsimopoieitai otan dn exei diabastei
kanena symbolo ek twn m,n,M,N, h ok xrhsimopoieitai otan teleiwsei
ena B,D,b,d kai oson afora tis upoloipes 4 i kathemia antiproswpeyei
to diabasma enos ek twn m,n,M,N antistoixa.*/
enum state{
   NOTHING,
   OK,
   m,
   n,
   M,
   N
};

/*To i xrisimopoieitai gia indexing twn pinakwn, to count metraei posa kena kai newline diabasthkan
sth seira , wste na brei to telos tou input file, to nonEng metraei tous mh agglikous xarakthres dhladh
ousiastika tsekarei an o xarakthras einai ellhnikos h agglikos, oi pinakes xrhsimopoiountai gia na apo8ikeyoun
ta grammata gia ta mappings, to ch einai o xaraktiras pou diabazetai apo to input file ka8e fora kai h temp apo8ikeyei
ka8e fora enan xarakthra ek twn m,n,M,N epeidh ayta den ektypwnontai sthn epanalhpsh pou diabazontai
alla sthn epomenh, giati prepei na elegxtei an akolou8ei p,P,t i T.*/
int main(){
    int i,count = 0,nonEng = 0;
    char lowerGR[25],lowerENG[25],upperGR[24],upperENG[24],ch,lowerGRMT[7],upperGRMT[7],temp;
    enum state s = NOTHING;
    initializeLowerGR(lowerGR);
    initializeLowerENG(lowerENG);
    initializeUpperGR(upperGR);
    initializeUpperENG(upperENG);
    initializeLowerGRMT(lowerGRMT);
    initializeUpperGRMT(upperGRMT);

    ch = getchar();
    while(ch != EOF){
       if(ch == (char)238){
          putchar('k');
          putchar('s');
          nonEng++;
       }
       else if(ch == (char)248){
          putchar('p');
          putchar('s');
          nonEng++;
       }
       else if(ch == (char)206){
          putchar('K');
          putchar('S');
          nonEng++;
       }
       else if(ch == (char)216){
          putchar('P');
          putchar('S');
          nonEng++;
       }
       else{
          if(ch == (char)236 && s == NOTHING){
             s = m;
             temp = 'm';/*sxolio*/
             nonEng++;
          }
          else if(ch == (char)240 && s == m){
             s = OK;
             nonEng++;
             putchar('b');
          }
          else if(ch == (char)208 && s == m){
             s = OK;
             nonEng++;
             putchar('b');
          }
          else if(ch == (char)204 && s == NOTHING){
             s = M;
             temp = 'M';/*sxolio*/
             nonEng++;
          }
          else if(ch == (char)240 && s == M){
             s = OK;
             nonEng++;
             putchar('B');
          }
          else if(ch == (char)208 && s == M){
             s = OK;
             nonEng++;
             putchar('B');
          }
          else if(ch == (char)237 && s == NOTHING){
             /*putchar('n');*/
             s = n;
             temp = 'n';/*sxolio*/
             nonEng++;
          }
          else if(ch == (char)244 && s == n){
             s = OK;
             nonEng++;
             putchar('d');
          }
          else if(ch == (char)212 && s == n){
             s = OK;
             nonEng++;
             putchar('d');
          }
          else if(ch == (char)205 && s == NOTHING){
             s = N;
             temp = 'N';/*sxolio*/
             nonEng++;
          }
          else if(ch == (char)244 && s == N){
             s = OK;
             nonEng++;
             putchar('D');
          }
          else if(ch == (char)212 && s == N){
             s = OK;
             nonEng++;
             putchar('D');
          }
          else if(s != NOTHING && s != OK){
             putchar(temp); /*sxolio*/
             s = NOTHING;
          }

          for(i = 0; i < 25; i++){
             if(ch == lowerGR[i] && s == NOTHING){
                putchar(lowerENG[i]);
                nonEng++;
             }
          }

          for(i = 0; i < 24; i++){
             if(ch == upperGR[i] && s == NOTHING){
                putchar(upperENG[i]);
                nonEng++;
             }
          }

          for(i = 0; i < 7; i++){
             if(ch == lowerGRMT[i] && i == 0){
                putchar('a');
                putchar('\'');
                nonEng++;
             }
             else if(ch == lowerGRMT[i] && i == 1){
                putchar('e');
                putchar('\'');
                nonEng++;
             }
             else if(ch == lowerGRMT[i] && i == 2){
                putchar('h');
                putchar('\'');
                nonEng++;
             }
             else if(ch == lowerGRMT[i] && i == 3){
                putchar('i');
                putchar('\'');
                nonEng++;
             }
             else if(ch == lowerGRMT[i] && i == 4){
                putchar('o');
                putchar('\'');
                nonEng++;
             }
             else if(ch == lowerGRMT[i] && i == 5){
                putchar('y');
                putchar('\'');
                nonEng++;
             }
             else if(ch == lowerGRMT[i] && i == 6){
                putchar('w');
                putchar('\'');
                nonEng++;
             }
          }

          for(i = 0; i < 7; i++){
             if(ch == upperGRMT[i] && i == 0){
                putchar('\'');
                putchar('A');
                nonEng++;
             }
             else if(ch == upperGRMT[i] && i == 1){
                putchar('\'');
                putchar('E');
                nonEng++;
             }
             else if(ch == upperGRMT[i] && i == 2){
                putchar('\'');
                putchar('H');
                nonEng++;
             }
             else if(ch == upperGRMT[i] && i == 3){
                putchar('\'');
                putchar('I');
                nonEng++;
             }
             else if(ch == upperGRMT[i] && i == 4){
                putchar('\'');
                putchar('O');
                nonEng++;
             }
             else if(ch == upperGRMT[i] && i == 5){
                putchar('\'');
                putchar('Y');
                nonEng++;
             }
             else if(ch == upperGRMT[i] && i == 6){
                putchar('\'');
                putchar('W');
                nonEng++;
             }
          }

          if(ch == (char)250){
             putchar('i');
             putchar('"');
             nonEng++;
          }
          else if(ch == (char)251){
             putchar('y');
             putchar('"');
             nonEng++;
          }
          else if(ch == (char)192){
             putchar('i');
             putchar('\'');
             putchar('"');
             nonEng++;
          }
          else if(ch == (char)224){
             putchar('y');
             putchar('\'');
             putchar('"');
             nonEng++;
          }
          count--;
       }
       if(ch == ' '){
          putchar(' ');
          count++;
          nonEng++;
       }
       else if(ch == '\n'){
          putchar('\n');
          count++;
          nonEng++;
       }

       if(nonEng == 0){
          putchar(ch);
       }
       else{
          nonEng=0;
       }

       if(s == OK){
          s = NOTHING;
       }
       ch = getchar();
       if(count==2){
          ch=EOF;
       }
    }
    return 0;
}
