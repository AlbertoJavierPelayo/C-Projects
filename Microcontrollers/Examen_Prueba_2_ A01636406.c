/*
 * main implementation: use this 'C' sample to create your own application

 *
 */


/*
 * Desarrolla un sistema basado en una tarjeta Freedom KL25 que cumpla con las siguientes características:

    El sistema es un sistema autónomo para llevar medicinas a pacientes Covid.
    Tiene dos motores que se mueven de manera independiente para poder provocar los giros. PWM
    Ambos deben de moverse usando la funcionalidad de PWM sin interrupciones
    En una memora IIC vienen pares de valores: dirección y tiempo en esa dirección. 
    Toda la ruta está definida por esta secuencia de pares.
    En cada momento que cambia de dirección se debe de mandar vía UART la nueva dirección y el nuevo tiempo.
    Para cada motor hay una señal analógica que monitorea la corriente del motor. 
    Si pasa de un umbral, definido por el diseñador, de cuando debe de detenerse el motor. 
    Al detectar el exceso en corriente, ambos motores deben de detenerse.
 * 
 */


#include "derivative.h" /* include peripheral declarations */

//Constantes y Variables

#define SLAVE_ADDR 0x1D     /* 001 1101. */
#define ERR_NONE 0
#define ERR_NO_ACK 0x01
#define ERR_ARB_LOST 0x02
#define ERR_BUS_BUSY 0x03

unsigned short periodo_pwm;

int rv;
unsigned char datos_memoria[3];
int count;
unsigned char dir=0x00;
unsigned char convert;

unsigned char i=0;
unsigned char temp=0;
unsigned char valor_recibido_UART=0;

unsigned char valor_ADC[2]; //guardamos el valor de los adc
unsigned char canal_ADC=0;	//canal del adc
unsigned char conf_canal[2]={(1<<6)+8,(1<<6)+9}; //PTB0 y PTB1


unsigned char mensaje_ASCII[]={"MD:##, MI:##, T:###mS V\n\r"};//EL PWM solo puede ser de 0 a 99


//Pines usados
/*
 * PWM (FTM0) PTA-4
 * PWM (FTM0) PTA-5
 * 
 * I2C	PTE-24
 * I2C	PTE-25
 * 
 * UART PTA-1	RX
 * UART PTA-2	TX
 * 
 * ADC	PTB-0
 * ADC	PTB-1
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
		
	I2C0_F = (1<<6) + 21;  //0x1C;             /* set clock to 97.09KHz @13.981MHz bus clock */ //OJO registro muy importante
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
	//PTB0: Sensor Motor Derecho	OPC8
	//PTB1: Sensor Motor Izq		OPC9
}
void LPTMR0_init (void)
{
	SIM_SCGC5|=1;					//reloj LPTimer
	
	LPTMR0_PSR=5;					//bypass preescaler, LPO (1 KHz) base de tiempo
	LPTMR0_CMR=200-1;				//200 ms
	LPTMR0_CSR=(1<<6)+1;			//Hab intr LPTMR, Hab conteo
	
	NVIC_ISER|=(1<<28);				//Hab LPTMR0 en NVIC
		
}
void  PIT_init (void)
{
	SIM_SCGC6|=(1<<23);			//PIT
	PIT_MCR&=~(1<<1);     		//Enable PITs
		
	PIT_LDVAL0=4000;			//1 ms. Cuenta 4 MHz (250 ns). Timer 32 bits. 
	PIT_TCTRL0= (1<<1)+(1<<0); // TEN=1, Hab Intr
		
	NVIC_ISER|=(1<<22);
}

void pwm_motor(unsigned char duty_cycle, unsigned char motor)
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

int I2C0_burstRead(unsigned char slaveAddr, unsigned char memAddr, int byteCount, unsigned char* data, int* cnt)
{
unsigned char dummy;

	/* send start */
	I2C0_C1 |= (1<<4);           // Tx on 
    I2C0_C1 |= (1<<5);           // become master, start

    /* send slave address and write flag */
    I2C0_D = slaveAddr << 1;	// slaveADDR-0-  0 indica write
    while(!(I2C0_S & 0x02));   // wait for transfer complete
    I2C0_S |= 0x02;            // clear IF    

    if (I2C0_S & 0x01)         /* got NACK from slave */
        return ERR_NO_ACK;

    /* send memory address */
    I2C0_D = memAddr;
    while(!(I2C0_S & 0x02));   /* wait for transfer complete */
    I2C0_S |= 0x02;            /* clear IF */
    if (I2C0_S & 0x01)         /* got NACK from slave */
        return ERR_NO_ACK;
    
    /* restart */
    I2C0_C1 |= 0x04;           /* send Restart */

    /* send slave address and read flag */
    I2C0_D = (slaveAddr << 1) | 1;
    while(!(I2C0_S & 0x02));   /* wait for transfer complete */
    I2C0_S |= 0x02;            /* clear IF */
    if (I2C0_S & 0x01)         /* got NACK from slave */
        return ERR_NO_ACK;

    /* change bus direction to read */
    I2C0_C1 &= ~0x18;          /* Tx off, prepare to give ACK */
    if (byteCount == 1)
        I2C0_C1 |= 0x08;       /* prepare to give NACK */
    dummy = I2C0_D;            /* dummy read to initiate bus read */

    /* read data */
    while (byteCount > 0) {
        if (byteCount == 1)
            I2C0_C1 |= 0x08;       /* prepare to give NACK for last byte */
        while(!(I2C0_S & 0x02));   /* wait for transfer complete */
        I2C0_S |= 0x02;            /* clear IF */
        if (byteCount == 1) {
            I2C0_C1 &= ~0x20;      /* stop the bus before reading last byte */
        }
        *data++ = I2C0_D;          /* read received data */
        byteCount--;
        (*cnt)++;
    }

    return ERR_NONE;
}

//Interrupciones
void UART0_IRQHandler (void)
{

	//ENVIAR
	if ((UART0_S1&(1<<7))==(1<<7))	//por bandera de TDRE    1011010 
	{
		UART0_D=mensaje_ASCII[i++];
		if (mensaje_ASCII[i]==0)
		{
			NVIC_ISER=(1<<15)+(1<<28)+(1<<12)+(1<<22);     //ADC0, LPTimer, UART0, pit
			i=0;
		}
	}
}
void PIT_IRQHandler(void)
{
	if (PIT_TFLG0 == (1<<0))
	   {
		PIT_TFLG0=(1<<0);		  //Apagar bandera
		rv = I2C0_burstRead(SLAVE_ADDR, dir, 3, datos_memoria, &count);
		pwm_motor(datos_memoria[0],0);//motor derecho
		pwm_motor(datos_memoria[1],1);//motor izq
		PIT_LDVAL0=4000*datos_memoria[2];			//4000=1ms y se multiplica por el tiempo en la memoria. Cuenta 4 MHz (250 ns). Timer 32 bits. 
		PIT_TCTRL0= (1<<1)+(1<<0); // TEN=1, Hab Intr
		dir+=3;
		//mensaje_ASCII[]={"MD:##, MI:##, T:### V\n\r"};
		convert=datos_memoria[0];
		if (convert<10)
		{
			mensaje_ASCII[3]='0';
		}
		else
		{
			mensaje_ASCII[3]=(convert%10)+0x30;
			convert/=10;
		}
		mensaje_ASCII[4]=(convert%10)+0x30;
		convert=datos_memoria[1];
		if (convert<10)
		{
			mensaje_ASCII[10]='0';
		}
		else
		{
			mensaje_ASCII[10]=(convert%10)+0x30;
			convert/=10;
		}
		mensaje_ASCII[11]=(convert%10)+0x30;
		convert=datos_memoria[2];
		if (convert<100)
		{
			mensaje_ASCII[16]='0';
		}
		else
		{
			mensaje_ASCII[16]=(convert%10)+0x30;
			convert/=10;
		}
		if (convert<10)
		{
			mensaje_ASCII[17]='0';
		}
		else
		{
			mensaje_ASCII[17]=(convert%10)+0x30;
			convert/=10;
		}
		mensaje_ASCII[18]=(convert%10)+0x30;

		NVIC_ISER|=(1<<22);
		
	   }
	   

}

void LPTimer_IRQHandler()
{
	LPTMR0_CSR=(1<<6)+1+(1<<7); //Apaga la bandera TCF y mantiene la configuracion
	ADC0_SC1A=conf_canal[canal_ADC];
}

void ADC0_IRQHandler()
{
	unsigned short voltaje_mV;
	valor_ADC[canal_ADC]=ADC0_RA;			//leo el resultado de la conversion y se apaga la bandera COCO
	
	voltaje_mV=(valor_ADC[canal_ADC]*3300)/255;
		
	if(voltaje_mV>1800)
	{
			//Desactivar motores
		pwm_motor(0,0);//motor derecho
		pwm_motor(0,1);//motor izq
		
	}
			
	NVIC_ISER=(1<<15)+(1<<28)+(1<<12)+(1<<22);     //ADC0, LPTimer, UART0, pit
	
		
	canal_ADC=canal_ADC^1; //Toggle para cambiar de canal
}





int main(void)
{
	
	clk_init();
	PWM_init();
	I2C_init();
	UART0_init();
	ADC0_init();
	LPTMR0_init();
	PIT_init();
	
	
	
	
	while(1);
	
	return 0;
}
