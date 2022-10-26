/*
 * File:   Teste_LCD.c
 * Author: Marcelo
 *
 * Created on 22 de Março de 2021, 20:23
 */

// PIC16F628A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000 // 4MHz

#include "lcd.h"
#include "teclado.h"
#define LED_1 PORTAbits.RA1
#define LED_2 PORTAbits.RA2
#define LED_6 PORTAbits.RA6
#define LED_7 PORTAbits.RA7

unsigned char LED;
int CONTADOR;
int indice = 0;
int n = 0;
void prototype();
void preencher_sorteio(unsigned char *cartela, int n);
void esvaziar_sorteio(char *cartela);

void main(void) {
    unsigned char i;
    unsigned char tecla;
    
    PCONbits.OSCF = 1; // OSCF: INTOSC Oscillator Frequency bit. 1 = 4 MHz typical

    TRISA = 0x30;
    TRISB = 0xE7;
    
    PORTA = 0x00;
    PORTB = 0x00;

    lcd_init();
    
    lcd_cmd(L_CLR); // Limpar LCD
    lcd_cmd(L_L1); // Pirmeira linha da tela
    lcd_str("Mega-sena"); // Coloca o conteudo na linha apontada
    __delay_ms(2000); // <- REMOVER
    
    while (1) {
        prototype();
    }
}

void prototype(){
    unsigned char tecla;
    char cartela[16] = "__-__-__-__-__-__";
    
    
    if(indice == 0){
        lcd_cmd(L_CLR); // Limpar LCD
        lcd_cmd(L_L1); // Pirmeira linha da tela
        lcd_str("Aperte a tecla #");
        lcd_cmd(L_L2); // Pirmeira linha da tela
        lcd_str("para começar");
        
        __delay_ms(2000); // <- REMOVER
        
        lcd_cmd(L_CLR); // Limpar LCD
        lcd_cmd(L_L1); // Pirmeira linha da tela
        tecla = tc_tecla(3000); // Insere o valor na variavel tecla
        lcd_dat(tecla + 0x30);
        
        if(tecla == 12){
            indice = 1;
        } else {
            indice = 0;
        }
    }
    if(indice == 1){
        lcd_cmd(L_CLR); // Limpar LCD
        lcd_cmd(L_L1); // Pirmeira linha da tela
        lcd_str("Aperte a tecla *");
        lcd_cmd(L_L2); // Pirmeira linha da tela
        lcd_str("para sortear ");
        //lcd_str(n + 0x30);
        
        __delay_ms(2000); // <- REMOVER
        
        lcd_cmd(L_CLR); // Limpar LCD
        tecla = tc_tecla(3000); // Insere o valor na variavel tecla
        lcd_dat(tecla + 0x30);
        
        if(tecla == 10){
            indice = 2; // Segue para a proxima etapa
        } else {
            
            lcd_cmd(L_CLR); // Limpar LCD
            lcd_cmd(L_L1); // Pirmeira linha da tela
            lcd_str("Você pressionou");
            lcd_cmd(L_L2); // Pirmeira linha da tela
            lcd_str("a tecla errada");
            
            __delay_ms(2000); // <- REMOVER
            
            indice = 1; // Retorna para a insercao do N
        }
    }
    if(indice == 2){
        n = n+1;
        preencher_sorteio(&cartela, n);
        
        lcd_cmd(L_CLR); // Limpar LCD
        lcd_cmd(L_L1); // Pirmeira linha da tela
        lcd_str(cartela);
        
        __delay_ms(2000); // <- REMOVER
        
        if(n == 6){
            indice = 4;
        }
        indice = 1;
    }
    if(indice == 4){
        lcd_cmd(L_CLR); // Limpar LCD
        lcd_cmd(L_L1); // Pirmeira linha da tela
        lcd_str("Pressione #");
        lcd_cmd(L_L2); // Pirmeira linha da tela
        lcd_str("para recomecar");
        
        __delay_ms(2000); // <- REMOVER
            
        tecla = tc_tecla(3000); // Insere o valor na variavel tecla
        lcd_dat(tecla + 0x30);
        
        if(tecla == 12){
            indice = 1;
            n = 0;
            esvaziar_sorteio(&cartela);
        } else {
            indice = 4;
        }
    }
    
}

void preencher_sorteio(unsigned char *cartela, int n){
    //"--.--.--.--.--.--"
    int dezena = 5; // Numero aleatorio 0-5
    int unidade = 9; // Numero aleatorio 1-9
    
    if(dezena == 0 && unidade == 0){
        dezena = 0;
        unidade = 1;
    }
    
    switch(n){
        case 1:
            cartela[0] = (char) dezena + 0x30;
            cartela[1] = (char) unidade + 0x30;
            break;
        case 2:
            cartela[3] = (char) dezena + 0x30;
            cartela[4] = (char) unidade + 0x30;
            break;
        case 3:
            cartela[6] = (char) dezena + 0x30;
            cartela[7] = (char) unidade + 0x30;
            break;
        case 4:
            cartela[9] = (char) dezena + 0x30;
            cartela[10] = (char) unidade + 0x30;
            break;
        case 5:
            cartela[12] = (char) dezena + 0x30;
            cartela[13] = (char) unidade + 0x30;
            break;
        case 6:
            cartela[15] = (char) dezena + 0x30;
            cartela[16] = (char) unidade + 0x30;
            break;
        default:
            break;
    }
}

void esvaziar_sorteio(char *cartela){
    //"--.--.--.--.--.--"
    cartela[0] = '-';
    cartela[1] = '-';
    
    cartela[3] = '-';
    cartela[4] = '-';

    cartela[6] = '-';
    cartela[7] = '-';

    cartela[9] = '-';
    cartela[10] = '-';

    cartela[12] = '-';
    cartela[13] = '-';

    cartela[0] = '-';
    cartela[1] = '-';

}