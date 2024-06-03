
class MotorDriver {
  private:
    //void start(byte pwm = 255, bool dir = 0);
	uint8_t st = 0;
    uint8_t speed = 0.0;
    bool dir = 0;
    bool direction = 0;
    uint8_t setpoint = 0.0;
    uint8_t speed_step = 20;
	bool MODE;
    uint8_t PWM, INA, INB, CSENSE, ENA, ENB, NTC, FINE_CORSA;

    void _write(uint8_t pwm, bool d) {
		analogWrite_(PWM, pwm*2, 512);
      //if(!MODE){
      digitalWrite(INA, !d);
	  //} else {
      //  digitalWrite(INA, pwm);
      //}
      digitalWrite(INB, d);
      direction = d;
    }
	
	void analogWrite_(uint8_t pin, uint16_t val, uint16_t max){
	  pinMode(pin, OUTPUT);
	  if (val == 0) digitalWrite(pin, LOW);
	  else if (val >= max)  digitalWrite(pin, HIGH);
	  else{
		switch(digitalPinToTimer(pin)){
			// XXX fix needed for atmega8
			#if defined(TCCR0) && defined(COM00) && !defined(__AVR_ATmega8__)
			case TIMER0A:
			// connect pwm to pin on timer 0
			TCCR0 |= 1<<COM00;
			OCR0 = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR0A) && defined(COM0A1)
			case TIMER0A:
			// connect pwm to pin on timer 0, channel A
			TCCR0A |= 1<<COM0A1;
			OCR0A = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR0A) && defined(COM0B1)
			case TIMER0B:
			// connect pwm to pin on timer 0, channel B
			TCCR0A |= 1<<COM0B1;
			OCR0B = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR1A) && defined(COM1A1)
			case TIMER1A:
			// connect pwm to pin on timer 1, channel A
			TCCR1A |= 1<<COM1A1;
			OCR1A = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR1A) && defined(COM1B1)
			case TIMER1B:
			// connect pwm to pin on timer 1, channel B
			TCCR1A |= 1<<COM1B1;
			OCR1B = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR1A) && defined(COM1C1)
			case TIMER1C:
			// connect pwm to pin on timer 1, channel C
			TCCR1A |= 1<<COM1C1;
			OCR1C = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR2) && defined(COM21)
			case TIMER2:
			// connect pwm to pin on timer 2
			TCCR2 |= 1<<COM21;
			OCR2 = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR2A) && defined(COM2A1)
			case TIMER2A:
			// connect pwm to pin on timer 2, channel A
			TCCR2A |= 1<<COM2A1;
			OCR2A = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR2A) && defined(COM2B1)
			case TIMER2B:
			// connect pwm to pin on timer 2, channel B
			TCCR2A |= 1<<COM2B1;
			OCR2B = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR3A) && defined(COM3A1)
			case TIMER3A:
			// connect pwm to pin on timer 3, channel A
			TCCR3A |= 1<<COM3A1;
			OCR3A = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR3A) && defined(COM3B1)
			case TIMER3B:
			// connect pwm to pin on timer 3, channel B
			TCCR3A |= 1<<COM3B1;
			OCR3B = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR3A) && defined(COM3C1)
			case TIMER3C:
			// connect pwm to pin on timer 3, channel C
			TCCR3A |= 1<<COM3C1;
			OCR3C = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR4A)
			case TIMER4A:
			//connect pwm to pin on timer 4, channel A
			TCCR4A |= 1<<COM4A1;
			#if defined(COM4A0)		// only used on 32U4
			TCCR4A &= ~(1<<COM4A0);
			#endif
			OCR4A = val;	// set pwm duty
			break;
			#endif
			
			#if defined(TCCR4A) && defined(COM4B1)
			case TIMER4B:
			// connect pwm to pin on timer 4, channel B
			TCCR4A |= 1<<COM4B1;
			OCR4B = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR4A) && defined(COM4C1)
			case TIMER4C:
			// connect pwm to pin on timer 4, channel C
			TCCR4A |= 1<<COM4C1;
			OCR4C = val; // set pwm duty
			break;
			#endif
			
			#if defined(TCCR4C) && defined(COM4D1)
			case TIMER4D:
			// connect pwm to pin on timer 4, channel D
			TCCR4C |= 1<<COM4D1;
			#if defined(COM4D0)		// only used on 32U4
			TCCR4C &= ~(1<<COM4D0);
			#endif
			OCR4D = val;	// set pwm duty
			break;
			#endif

			
			#if defined(TCCR5A) && defined(COM5A1)
			case TIMER5A:
			// connect pwm to pin on timer 5, channel A
			TCCR5A |= 1<<COM5A1;
			OCR5A = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR5A) && defined(COM5B1)
			case TIMER5B:
			// connect pwm to pin on timer 5, channel B
			TCCR5A |= 1<<COM5B1;
			OCR5B = val; // set pwm duty
			break;
			#endif

			#if defined(TCCR5A) && defined(COM5C1)
			case TIMER5C:
			// connect pwm to pin on timer 5, channel C
			TCCR5A |= 1<<COM5C1;
			OCR5C = val; // set pwm duty
			break;
			#endif

			case NOT_ON_TIMER:
			default:
			if (val < 128) {
				digitalWrite(pin, LOW);
				} else {
				digitalWrite(pin, HIGH);
			}
		}
	  }
	}

  public:
    MotorDriver(bool mode, uint8_t pwm, uint8_t ina, uint8_t inb, uint8_t csense = 0, uint8_t ena = 0, uint8_t enb = 0, uint8_t ntc = 0, uint8_t fc = 0) {
      MODE = mode;
	  PWM = pwm;
      INA = ina;
      INB = inb;
      CSENSE = csense;
      ENA = ena;
      ENB = enb;
      FINE_CORSA = fc;
      NTC = ntc;
    }

    void begin() {
      pinMode(PWM, OUTPUT);
      pinMode(INA, OUTPUT);
      pinMode(INB, OUTPUT);
	  
      if (CSENSE) pinMode(CSENSE, INPUT);
      if (ENA) pinMode(ENA, INPUT);
      if (ENB) pinMode(ENB, INPUT);
      if (FINE_CORSA) pinMode(FINE_CORSA, INPUT);
      if (NTC) pinMode(NTC, INPUT);
      stop();
    }



    void start(byte v, bool d) {
	  st = d + 1;
      setpoint = v;
      dir = d;
	  _write(speed, dir);
    }

    void stop(bool br = 0) {
      digitalWrite(PWM, LOW);
      if (!MODE){
        digitalWrite(INA, br);
        digitalWrite(INB, br); 
      } else{
        digitalWrite(INA, LOW);
        digitalWrite(INB, LOW);
      }
	  st = 0;
      setpoint = 0;
      speed = 0;
      //preset_pressione = 0;
    }
	
	void brake(){
		digitalWrite(PWM, LOW);
		if (!MODE){
          digitalWrite(INA, HIGH);
  	      digitalWrite(INB, HIGH);
        } else {
          digitalWrite(INA, LOW);
          digitalWrite(INB, LOW);
        }
		st = 0;
		speed = 0;
	}

    float getCurrent() {
      if (CSENSE) {
        float c = analogRead(CSENSE) * 34.87723214;// := 5000.0 / 0.140 / 1024.0;  // corrente in mA
        return c;
	  }
	  return -1;
    }

    float getTemperature() {
      if (NTC) {
        int Vo;
        float R1 = 10000;
        float logR2, R2, T;
        float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
        Vo = analogRead(NTC);
        R2 = R1 * (1023.0 / (float)Vo - 1.0);
        logR2 = log(R2);
        T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
        T = T - 273.15;
        return T;
      }
      return -1;
    }
	
	bool getEndstopHit(){
	  if (FINE_CORSA) return digitalRead(FINE_CORSA);
	  return 0;
	}
	
	bool getDirection(){
	  return direction;
	}
	
	uint8_t getState(){
	  return st;
	}
    
    uint8_t getSpeed(){
      return setpoint;
    }

    /*
        void set_pressione() {
          int diff = (int)pressione - (int)setpoint_pressione;
          if (diff > press_err_margin || diff < -(int)press_err_margin) {
            if (diff > 0) {
              dir = 1;
            } else if (diff < 0) {
              dir = 0;
            }

            if ((diff < press_slow_margin) && (diff > -(int)press_slow_margin)) {
              setpoint = 100;
            } else {
              setpoint = 255;
            }
          } else {
            stop();
            CAN_send_parameter(0x00, 500, 2, CAN_press_id);
            preset_pressione = 0;
          }
        }
    */

    void loop() {
      /*if (emergenza) {
        setpoint = 0;
        speed = 0;
        //preset_pressione = 0;
        //preset_altezza = 0;
        stop(1);
        } else {*/
        
      int16_t diff = (int16_t)speed - (int16_t)setpoint;
      if (((st != 0) && (diff != 0)) || (dir != direction)) { // se non � spento e Se cambia qualche parametro
        if ((diff < 0) && (speed <= 255 - speed_step)) {
          speed += speed_step;
        } else if ((diff > 0) && (speed >= speed_step)) {
          speed -= speed_step;
        }
        if ((diff < speed_step) && (diff > -(speed_step))) {
          speed = setpoint;
        }

        if (dir != direction) {
          brake();
        }

		
        _write(speed, dir);
      }
      //}
    }
};