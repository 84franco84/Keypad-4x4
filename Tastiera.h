#ifndef Tastiera_h
#define Tastiera_h 
// library interface description
#include <Arduino.h>

/******************************* Tastiera *************************************/
//                   [col][rig] a True per un solo Loop
// Define per i singoli tasti
#define t_1 Tasti.tasto_on[0][0]
#define t_2 Tasti.tasto_on[1][0]
#define t_3 Tasti.tasto_on[2][0]
#define t_key Tasti.tasto_on[3][0]
#define t_4 Tasti.tasto_on[0][1]
#define t_5 Tasti.tasto_on[1][1]
#define t_6 Tasti.tasto_on[2][1]
#define t_led Tasti.tasto_on[3][1]
#define t_7 Tasti.tasto_on[0][2]
#define t_8 Tasti.tasto_on[1][2]
#define t_9 Tasti.tasto_on[2][2]
#define t_freq Tasti.tasto_on[3][2]
#define t_canc Tasti.tasto_on[0][3]
#define t_0 Tasti.tasto_on[1][3]
#define t_ast Tasti.tasto_on[2][3]
#define t_invio Tasti.tasto_on[3][3]

#define t_1_off Tasti.tasto_off[0][0]
#define t_2_off Tasti.tasto_off[1][0]
#define t_3_off Tasti.tasto_off[2][0]
#define t_key_off Tasti.tasto_off[3][0]
#define t_4_off Tasti.tasto_off[0][1]
#define t_5_off Tasti.tasto_off[1][1]
#define t_6_off Tasti.tasto_off[2][1]
#define t_led_off Tasti.tasto_off[3][1]
#define t_7_off Tasti.tasto_off[0][2]
#define t_8_off Tasti.tasto_off[1][2]
#define t_9_off Tasti.tasto_off[2][2]
#define t_freq_off Tasti.tasto_off[3][2]
#define t_canc_off Tasti.tasto_off[0][3]
#define t_0_off Tasti.tasto_off[1][3]
#define t_ast_off Tasti.tasto_off[2][3]
#define t_invio_off Tasti.tasto_off[3][3]

typedef bool tasto_[4][4];
typedef unsigned long timer_t_[4][4];
typedef bool ab_timer_[4][4];

class Tasti_
{
public:
    tasto_ tasto_on;
    tasto_ tasto_off;
	 bool get_tasto_numerico;
    byte val_tasto = 100;
    void begin(void);
    void leggi_tasti(void);
  private:
  	 tasto_ tasto_real;
    tasto_ tasto_old;
	 byte tasto_cr = 100;
	 timer_t_ timer_t_on;
	 timer_t_ timer_t_off;
	 ab_timer_ ab_timer_on;
    ab_timer_ ab_timer_off;
    bool tasto_on_off(void);
};

extern Tasti_ Tasti;

#endif
