#include "Tastiera.h"

/************************* Tastiera per Mega/Due ******************************/

// Pin su Arduino relativi a Riche e Colonne 4x4
//Righe
#define r1 10
#define r2 11
#define r3 12
#define r4 13
// Colonne
#define c1 6
#define c2 7
#define c3 8
#define c4 9

// ATTENZIONE sono a logica negata
void Tasti_::begin(void)
{
// 4,5,6,7 come OUT (Digitali)
pinMode(c1,OUTPUT);
pinMode(c2,OUTPUT); 
pinMode(c3,OUTPUT);
pinMode(c4,OUTPUT);
// Tutti alti (logica negata-> LOW tasto attivo)
digitalWrite(c1, HIGH);
digitalWrite(c2, HIGH);
digitalWrite(c3, HIGH); 
digitalWrite(c4, HIGH);
// Input 0,1,2,3
pinMode(r1,INPUT_PULLUP);
pinMode(r2,INPUT_PULLUP); 
pinMode(r3,INPUT_PULLUP);
pinMode(r4,INPUT_PULLUP);

// Inizializz. Tasto_Old allo Start
for (byte i=0;i<=3;i++)
   for (byte n=0;n<=3;n++)
      {
		tasto_old[i][n]=false;
		timer_t_on[i][n]=0xFFFFFFFF;
		timer_t_off[i][n]=0xFFFFFFFF;
		ab_timer_on[i][n]=false;
		ab_timer_off[i][n]=false;
		}
}

/* ------------------------- Uso delle variabili -------------------------------
// tasto_real[][] indica la situazione istantanea del tasto
// tasto_on[][] rimane alto solo un loop alla pressione  del tasto
// tasto_off[][] rimane basso solo un loop al rilascio del tasto
// vedi Tastiera.h per le corrispondenze con on e off dei tasti
// val_tasto in mancanza di evento vale sempre 100 altrimenti in caso di
// pressione (OFF/ON) ha un valore pari al tasto numerico premuto,
// per solo un loop
------------------------------------------------------------------------------*/

// fornisce il tasto_real[][] la situzione reale del tasto
void Tasti_::leggi_tasti(void)
{
int col, rig, val_rig;

for(col=c1;col<=c4;col++)  // va da 6 a 9
   {
   // mette il pin della colonna a 0: logica negata
   digitalWrite(col,LOW);
   for(rig=r1;rig<=r4;rig++)  // legge le righe (va da 10 a 13)
      {
      // Logica negata: Tasti.tasto_real premuto legge 0
      val_rig=digitalRead(rig);
      // Torno a logica diretta con tasto_real[][]
      if (val_rig==LOW)
         tasto_real[col-c1][rig-r1]=true;
      else
         tasto_real[col-c1][rig-r1]=false;
      }
   digitalWrite(col,HIGH);
   }
// Richiama la funzione seguente
tasto_on_off();
}

// Fornisce i gradini su tasto_on[][] e su tasto_off[][] e sull gradino ON/OFF il valore del numerico tasto_cr
bool Tasti_::tasto_on_off(void)
{
int i,n;
// Resetta tutte le variabili tasto per nuova lettura cosicche' tasto_on e _off
// rimangono a true un solo loop
for (i=0;i<=3;i++)
   for (n=0;n<=3;n++)
      {
      tasto_on[i][n]=false;
      tasto_off[i][n]=false;
      }
tasto_cr=100;

// Imposta i tasti validi per un loop all'evento "premi o rilascia""
for (i=0;i<=3;i++)
   for (n=0;n<=3;n++)
      {
      if (tasto_real[i][n] && !tasto_old[i][n])
			{
			timer_t_on[i][n]=millis();
			ab_timer_on[i][n]=true;
			}
		if (millis()>=timer_t_on[i][n]+50 && ab_timer_on[i][n])
			{
			timer_t_on[i][n]=0xFFFFFFFF;
         ab_timer_on[i][n]=false;
      	if (tasto_real[i][n])
				{
				tasto_on[i][n]=true;
				tasto_cr=10*(i+1)+n+1;  // esprime il valore unico: col*10 + riga;
                                 	// es. tasto_cr=11;  vale per un l'ultimo tasto premuto!!! Default=100 cioe' nessun tasto premuto;
				}
			}
      if (!tasto_real[i][n] && tasto_old[i][n])
			{
			timer_t_off[i][n]=millis();
         ab_timer_off[i][n]=true;
			}
      if (millis()>=timer_t_off[i][n]+50 && ab_timer_off[i][n])
			{
         timer_t_off[i][n]=0xFFFFFFFF;
			ab_timer_off[i][n]=false;
      	if (!tasto_real[i][n])
				tasto_off[i][n]=true;
			}
      tasto_old[i][n]=tasto_real[i][n];
      }


// Tasti numerici, ritorna il valore solo nel gradino OFF/ON (premere solo un tasto alla volta, restituisce l'ultimo)
switch (tasto_cr)
  {
  case 11: val_tasto=1; break;
  case 21: val_tasto=2; break;
  case 31: val_tasto=3; break;
  case 12: val_tasto=4; break;
  case 22: val_tasto=5; break;
  case 32: val_tasto=6; break;
  case 13: val_tasto=7; break;
  case 23: val_tasto=8; break;
  case 33: val_tasto=9; break;
  case 24: val_tasto=0; break;
  case 34: val_tasto=10; break;  // Fa da punto
  case 100: val_tasto=100; break;
  default: val_tasto=100; break; // Default: nessun tasto premuto
  }
if (val_tasto<=9)
	get_tasto_numerico=true;
else
	get_tasto_numerico=false;
}

Tasti_ Tasti;