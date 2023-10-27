/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
/*
 * 

3.- Desarrolla un sistema basado en el microcontrolador KL25 que cumpla con los siguientes requerimientos:

*Es un sistema de limpia brisas para automóvil

* En operación manual, con un potenciómetro se regula la velocidad de movimiento

* En operación automática, un sensor de agua entrega un voltaje que al superar los 1.8 V debe de activarse 
* el limpia brisas a la mitad de la máxima velocidad

* El limpia brisas se mueve con un motor de corriente directa. Debe de moverse en dos direcciones. 
* Un driver recibe dos PWM, uno para mover el motor en cada dirección.

* Un switch en cada extremo detecta el fin de carrera y manda una interrupción al llegar a cada extremo.

* Cuando se active de manera automática, debe de enviar vía UART el valor recibido del sensor de agua.

* Por cuestiones de mantenimiento, debe de guardarse, cada vez que se active el limpiabrisas, 
* cuanto tiempo duró en funcionamiento. El almacenamiento es en una memoria IIC. 
* Debe de usarse el módulo IIC del KL25.

* Debe de operar todo vía interrupciones.

Debe de entregarse el (los) código(s) fuente, no todo el proyecto. 

Se otorgarán puntos extra si desarrollaste el ejercicio del examen de práctica, anexa tu código también
 * 
 */




#include "derivative.h" /* include peripheral declarations */

//Constantes y Variables

#define SLAVE_ADDR 0x1D     /* 001 1101. */
#define ERR_NONE 0
#define ERR_NO_ACK 0x01
#define ERR_ARB_LOST 0x02
#define ERR_BUS_BUSY 0x03

unsigned char motor=0;

unsigned char estado=0;//saber si esta rpendido o apagado

unsigned short periodo_pwm;
unsigned char i=0;
unsigned char temp=0;
unsigned char valor_recibido_UART=0;

unsigned char valor_ADC[2]; //guardamos el valor de los adc
unsigned char canal_ADC=0;	//canal del adc
unsigned char conf_canal[2]={(1<<6)+8,(1<<6)+9}; //PTB0 y PTB1

long double tiempo=0;


unsigned char mensaje[];
unsigned char send;

//Pines usados
/*
 * PWM (FTM0) PTA-4
 * PWM (FTM0) PTA-5
 * 
 * I2C	PTE-24
 * I2C	PTE-25
 * 
 * tpm1 pte21
 * 
 * UART PTA-1	RX
 * UART PTA-2	TX
 * 
 * ADC	PTB-0
 * ADC	PTB-1
 * 
 * on off pta 10
 * auto-manual pta11
 * limite derecha pta12
 * limite izq pta13
 */

//Funciones
void clk_init (void)
{
	// FIRC = 4 MHz. BusClk = 4 MHz
	// UART0: FIRC. UART1: BusClk. UART2: BusClk. TPM: FIRC. IIC: BusClk
	MCG_C1|=(1<<6) + (1<<1);	//MCGOUTCLK : IRCLK. CG: Clock gate, MCGIRCLK enable pag 116
	MCG_C2|=1;					//Mux IRCLK : FIRC (4 MHz) pag 116
	MCG_SC=0;					//Preescaler FIRC 1:1 pag 116

	SIM_CLKDIV1=0;				//OUTDIV4=OUTDIV1= 1:1 pag 116. Busclk 4 MHz
	SIM_SOPT2|=15<<24;			//Seleccion MCGIRCLK tanto para UART0 como para TPM
}

void PWM_init (void)//PWM - FTM0
{
	SIM_SCGC5|=(1<<9);		//PORTA
	PORTA_PCR4=(3<<8);		//TPM0_CH1	MOTOR DERECHO
	PORTA_PCR5=(3<<8);		//TPM0_CH2	MOTOR IZQ	

	SIM_SCGC6|=(1<<24);		//TPM0
	TPM0_SC=2;				//preescaler de 4 y TPM deshabilitado
	TPM0_SC|=(1<<3);		//Habilitar TPM0
	
   
	periodo_pwm=1000;			//número de cuentas necesarias para el periodo, 1 cuenta 1 us
    
    
    TPM0_C1SC=(9<<2);	//Edge aligned PWM, set ref, clear periodo
    TPM0_C2SC=(9<<2);	//Edge aligned PWM, set ref, clear periodo
    
    TPM0_MOD=periodo_pwm;
    //TPM0_C2V=(periodo_pwm*(100-duty_cycle))/100;
}


void I2C_init(void)
{
	SIM_SCGC5|=(1<<13);    //PORTE 
	//PORTA_PCR14=(1<<8);			//faltar[ia definir el tipo de interrupci[on
	//PORTA_PCR15=(1<<8);			//faltar[ia definir el tipo de interrupci[on
		
	SIM_SCGC4|=(1<<6);		//I2C hab reloj
	PORTE_PCR24=(5<<8);				//IIC
	PORTE_PCR25=(5<<8);				//IIC
		
	//I2C0_F = (1<<6) + 21;  //0x1C;             /* set clock to 97.09KHz @13.981MHz bus clock */ //OJO registro muy importante
	I2C0_C1 = 0x80;               /* enable I2C0 *///1000 0000
}

void UART0_init (void)
{
	SIM_SCGC4|=(1<<10);		//UART0 interface clk
	
	PORTA_PCR1=(2<<8);		//Funcion 2: UART0		Rx
	PORTA_PCR2=(2<<8);		//Funcion 2: UART0    	Tx
		
	UART0_BDH=0;
	UART0_BDL=26;			//Baud rate de 9600 bps. usando un UART clk de 4 MHz
	UART0_C2=(1<<7) + 12;	//Hab Intr de Recepción, Hab TE y RE
	
	//seccion para limpiar UART en Rx
	UART0_S1|=0x1F;//borra 5 banderas poniendolas en 1
	do{
		UART0_S1|=0x1F;	//borra las 5 banderas poniendola en 1
		if ((UART0_S1 & (1<<5))!=0) temp=UART0_D;	//si lee un dato = basura y lo lee en el temp para borrarlo
	}while ((UART0_S1)!=0xC0);	//hasta que ya no haya dato
}


void ADC0_init (void)
{
	SIM_SCGC6|=(1<<27);				//reloj de interfaz ADC0
	NVIC_ISER|=(1<<15);				//Hab ADC0 en NVIC
	//PTB0: POTENCIOMETRO	OPC8
	//PTB1: Sensor LLUVIA	OPC9
}
void LPTMR0_init (void)
{
	SIM_SCGC5|=1;					//reloj LPTimer
	
	LPTMR0_PSR=5;					//bypass preescaler, LPO (1 KHz) base de tiempo
	LPTMR0_CMR=200-1;				//200 ms
	LPTMR0_CSR=(1<<6)+1;			//Hab intr LPTMR, Hab conteo
	
	NVIC_ISER|=(1<<28);				//Hab LPTMR0 en NVIC
		
}


void PORTS_init (void)
{
	SIM_SCGC5|=(1<<9);		
	
	PORTA_PCR10=(1<<8)+(11<<16);//ON OFF, Interrupt on either edge
	PORTA_PCR11=(1<<8)+(11<<16);//entrada manual auito,Interrupt on either edge
	PORTA_PCR12=(1<<8)+(9<<16);//limite derecha, Interrupt on raising edge
	PORTA_PCR13=(1<<8)+(9<<16);//limite izq, Interrupt on raising edge
	
	
	
	NVIC_ISER=(1<<30);
	
	
}
/*
void tiempo_init (void)//FTMI inicialización
{	
	SIM_SCGC5|=(1<<9)+(1<<13);		//PORTA & PORTE
	
	
	PORTE_PCR21=(3<<8);      //TPM1_CH1
	
	SIM_SCGC6|=(1<<25);		 //TPM1
	
	TPM1_SC=(1<<3);			 //reloj interno (4 MHz)
	TPM1_C1SC=(1<<2)+(1<<6); //input capture rising edge, hab intr channel
	
	NVIC_ISER|=(1<<18);		 //NVIC del TPM1 
}
*/

void pwm_motor(unsigned char duty_cycle)
{
	if(motor==0)//Motor Derecho
	{
		TPM0_C1V=(periodo_pwm*(100-duty_cycle))/100;
	}
	else
	{
		TPM0_C2V=(periodo_pwm*(100-duty_cycle))/100;
	}
	
}

int I2C0_byteWrite(unsigned char slaveAddr, unsigned char memAddr, unsigned char data) {

/*Solo para asegurar bus en estado idle	
	int retry = 1000;
    
    while (I2C0_S & (1<<5)) 		{    // wait until bus is available
        if (--retry <= 0)
            return ERR_BUS_BUSY;
        delayUs(100);
    }
*/
	
    /* send start */
    I2C0_C1 |= (1<<4);           // Tx on 
    I2C0_C1 |= (1<<5);           // become master, start bit

    /* send slave address and write flag */
    I2C0_D = slaveAddr << 1;	// slaveADDR-0-  0 indica write
    while(!(I2C0_S & 0x02));   // wait for transfer complete
    //while ((I2C0_S & 0x02)==0);	
    
    
    I2C0_S |= 0x02;            // clear IF 
    /*
    if (I2C0_S & 0x10) {       // arbitration lost
        I2C0_S |= 0x10;        // clear IF 
        return ERR_ARB_LOST;
    }
    */
    
    if (I2C0_S & 0x01)         /* got NACK from slave */
        return ERR_NO_ACK;

    /* send memory address */
    I2C0_D = memAddr;
    while(!(I2C0_S & 0x02));   /* wait for transfer complete */
    I2C0_S |= 0x02;            /* clear IF */
    if (I2C0_S & 0x01)         /* got NACK from slave */
        return ERR_NO_ACK;

    /* send data */
    I2C0_D = data;
    while(!(I2C0_S & 0x02));   /* wait for transfer complete */
    I2C0_S |= 0x02;            /* clear IF */
    if (I2C0_S & 0x01)         /* got NACK from slave */
        return ERR_NO_ACK;

    /* stop */
    I2C0_C1 &= ~0x30;			//~0x30 = 0xCF 1100 1111  Apaga bit 4 y bit 5

    return ERR_NONE;
}



//Interrupciones
void LPTimer_IRQHandler()
{
	LPTMR0_CSR=(1<<6)+1+(1<<7); //Apaga la bandera TCF y mantiene la configuracion
	ADC0_SC1A=conf_canal[canal_ADC];
	tiempo++;
}

void ADC0_IRQHandler()
{
	unsigned short voltaje_mV;
	unsigned short velocidad;
	valor_ADC[canal_ADC]=ADC0_RA;			//leo el resultado de la conversion y se apaga la bandera COCO
	
	voltaje_mV=(valor_ADC[canal_ADC]*3300)/255;

	if(canal_ADC==0)//entrada manual lectura pot
	{
		velocidad=(voltaje_mV*100)/3300;
		
	}
	else//lectura sensor
	{
		mensaje[0]=voltaje_mV;
		if(voltaje_mV>1800) //leer el manual)
		{
			velocidad=50;
		}
	}
	if(estado==1)//se encuentra prendido
	{
		pwm_motor(velocidad);
	}
			
	NVIC_ISER=(1<<15)+(1<<28)+(1<<12)+(1<<22);     //ADC0, LPTimer, UART0, pit
	
		
	//canal_ADC=canal_ADC^1; //Toggle para cambiar de canal
}

void UART0_IRQHandler (void)
{

	//ENVIAR
	if ((UART0_S1&(1<<7))==(1<<7)&&canal_ADC==1)	//por bandera de TDRE    1011010 
	{
		UART0_D=mensaje[i++];
		if (mensaje[i]==0)
		{
			NVIC_ISER=(1<<15)+(1<<28)+(1<<12);     //ADC0, LPTimer, UART0, 
			i=0;
		}
	}
}
/*
void FTM1_IRQHandler(){
	
	if (((TPM1_C0SC & (1<<7)) >> 7) == 1){
		TPM1_C0SC|=(1<<7);		//apagar bandera
		FSA_cont++;
	}
	
	if (((TPM1_C1SC & (1<<7)) >> 7) == 1){
		TPM1_C1SC|=(1<<7);		//apagar bandera
		FSB_cont++;
	}
		
}
*/

void PORTA_IRQHandler()
{
	
	if(GPIOA_PDIR & (1<<10)==0)//ON OFF
	{
		PORTA_PCR10 |= 1<<24;
		estado=estado^1;
		if(estado==0)//apagar
		{
			pwm_motor(0);//apagar motores
			tiempo/=5;//el tiempo sera medido en segundos lo cual son 5 cuentas del LPTMR en 200ms
					
			send=I2C0_byteWrite(SLAVE_ADDR, 0x00, tiempo);
			
		}
		else//prender
		{
			tiempo=0;
			
		}
	}
	if(GPIOA_PDIR & (1<<11)==0)//manual o automatico
	{
			PORTA_PCR11 |= 1<<24;
			canal_ADC=canal_ADC^1;
	}
	if(GPIOA_PDIR & (1<<12)==0)
	{
		PORTA_PCR12 |= 1<<24;
		motor=0;//derecha	
	}
	if(GPIOA_PDIR & (1<<13)==0)
	{
		PORTA_PCR13 |= 1<<24;
		motor=1;//derecha	
	}
	
	
	
}


int main(void)
{
	clk_init();
	PWM_init();
	I2C_init();
	UART0_init();
	ADC0_init();
	LPTMR0_init();
	PORTS_init();
	
	
	while(1);
	
	return 0;
}
