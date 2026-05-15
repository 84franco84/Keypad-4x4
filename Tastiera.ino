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