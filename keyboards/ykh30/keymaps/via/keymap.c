#include "kb.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
		KC_ESC, M(0), 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, 
		KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_UP, MO(1), 
		KC_LCTL, KC_Z, KC_X, KC_C, KC_V, LT(1, KC_SPC), KC_B, KC_N, KC_M, KC_LEFT, KC_DOWN, KC_RGHT),

	LAYOUT(
		KC_TRNS, KC_TRNS, 
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, 
		KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_PGUP, KC_ENT, 
		KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END),

	LAYOUT(
		RESET, KC_TRNS, 
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};

#include "quantum.h"
#define delayms 60
uint8_t cw = 0;
uint8_t cw1 = 0xBD;
uint8_t ccw1 = 0xBE;
uint8_t ccw = 0;
int state (void);
int state1 (void);
void dec(uint8_t layer);
void inc(uint8_t layer);


void matrix_init_user(void) {
	DDRD &= ~((1<<5)|(1<<6)|(1<<7)); 
	DDRE &= ~(1<<6);
	DDRF |= ((1<<6)|(1<<7));
	//timer_clear();
	
}

void matrix_scan_user(void) {
	if(IS_LAYER_ON(2)){
		PORTF |= (1<<7);
		PORTF &= ~(1<<6);
		cw = KC_DOWN;
		ccw = KC_UP;
	}
	else if(IS_LAYER_ON(1)){
		PORTF |= (1<<6);
		PORTF &= ~(1<<7);
		cw = KC_PGDOWN;
		ccw = KC_PGUP;
	}
	else{
		cw = KC_AUDIO_VOL_UP;
		ccw = KC_AUDIO_VOL_DOWN;
		PORTF &= ~((1<<6)|(1<<7));	
	
	}
	
	if (state() == 2){
		while(state()!=0);
		register_code(cw);
		unregister_code(cw);
	}
	else if (state() == 3){
		while(state()!=0);
		register_code(ccw);
		unregister_code(ccw);
	}
	
	if (state1() == 2){
		while(state1()!=0);
		//host_consumer_send(0x0070);
		//host_consumer_send(0);
		inc(layer_state);
	}
	else if (state1() == 3){
		while(state1()!=0);
		//host_consumer_send(0x006f);
		//host_consumer_send(0);
		dec(layer_state);
	}
	//timer_clear();
}
	
int state (void){
	if ((!(PIND&(1<<5)))&&(!(PIND&(1<<6)))) return 1;
	if ((!(PIND&(1<<5)))&&(PIND&(1<<6))) return 2;
	if ((!(PIND&(1<<6)))&&(PIND&(1<<5))) return 3;
	else return 0;
}

int state1 (void){
	if ((!(PIND&(1<<7)))&&(!(PINE&(1<<6)))) return 1;
	if ((!(PIND&(1<<7)))&&(PINE&(1<<6))) return 2;
	if ((!(PINE&(1<<6)))&&(PIND&(1<<7))) return 3;
	else return 0;
}
void inc(uint8_t layer){
	switch (layer) {
		case 0: rgblight_increase_val();
		case 1: rgblight_increase_hue();
		case 2: rgblight_increase_sat();
	}
}

void dec(uint8_t layer){
	switch (layer) {
		case 0: rgblight_decrease_val();
		case 1: rgblight_decrease_hue();
		case 2: rgblight_decrease_sat();
	}
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}

}