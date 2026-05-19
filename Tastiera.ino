#include <Arduino.h>
#include "Tastiera.h"

#define led0 A0
#define led1 A1

void setup()
{
Tasti.begin();
Serial.begin(9600);
//
pinMode(led0, OUTPUT);
digitalWrite(led0,LOW);
pinMode(led1, OUTPUT);
digitalWrite(led1,LOW);
}
/* ----------------------- Tasti non numerici ----------------------------------
Alla pressione del tasto:
t_key  (col4, riga1)
t_led  (col4, riga2)
t_freq (col4, riga3)
t_invio (col4, riga4)
t_ast  (col3, riga4)
t_canc (col1, riga4)

Al rilascio del tasto:
t_key_off (col4, riga1)
t_led_off (col4, riga2)
...
------------------------------------------------------------------------------*/

// Utilizzo della libreria Tastiera
void loop()
{
Tasti.leggi_tasti();
//
if (t_key)  	// col=4 riga=1
	digitalWrite(led0,HIGH);

if (t_invio)  // col=4 riga=4
	digitalWrite(led0,LOW);

if (t_ast)    // col=3 riga=4
	digitalWrite(led1,HIGH);

if (t_ast_off) // rilascio del tasto sopra
	digitalWrite(led1,LOW);

if (Tasti.get_tasto_numerico) // uso dei tasti numerici
	{
	Serial.println("Valore del tasto numerico premuto:");
	Serial.println(Tasti.val_tasto);
	}
}