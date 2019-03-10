/*
    Name:       Rose_Cloud.ino
    Created:	10.03.2019 11:49:30
    Author:     IBOOK\velse
*/


#define CAP1_PIN 7
#define CAP2_PIN 8
#define BLUE_PIN 11
#define GREEN_PIN 10
#define RED_PIN 9
#define COMMON_ANODE

int val_1 = 0;             // таймер ёмкости
int val_2 = 0;
int active_color = BLUE_PIN;
boolean flag_1 = false;
boolean flag_2 = false;        // значение кнопки
boolean turn = false;

void setup()
{
	
	pinMode(RED_PIN, OUTPUT);
	pinMode(GREEN_PIN, OUTPUT);
	pinMode(BLUE_PIN, OUTPUT);

}

void loop()
{

	pinMode(CAP1_PIN, OUTPUT);       
	pinMode(CAP1_PIN, INPUT);        

	switch (active_color) {                 
	case RED_PIN:                         
		active_color = BLUE_PIN;              
		break;                            
	case GREEN_PIN:                       
		active_color = RED_PIN;            
		break;                            
	case BLUE_PIN:                        
		active_color = GREEN_PIN;         
		break;                            
	}

	while (digitalRead(CAP1_PIN) == LOW) {
		val_1++;                        //считаем, за сколько зарядилась ёмкость
	}

	while (digitalRead(CAP2_PIN) == LOW) {
		val_2++;                        //считаем, за сколько зарядилась ёмкость
	}

	if (val_1 > 20 && flag_1 == false)      // 7-20 величина гистерезиса
	{

		if (!turn)
		for (int i = 0; i <= 255; i++) {        //  в цикле меняем значение от 0 до 255 
			analogWrite(active_color, i);      //  и записываем его в пин, соответствующий текущему активному цвету
			delay(5);                         //  Задержка в 5 мс
		}
		else
			for (int i = 255; i >= 0; i--) {        //  в цикле меняем значение от 255 до 0
				analogWrite(active_color, i);      //  и записываем его в пин, соответствующий текущему активному цвету
				delay(5);                         //  Задержка в 5 мс
			}
		turn = !turn;

		flag_1 = true;
		delay(500);

	}

	if (val_2 > 20 && flag_2 == false)      // 7-20 величина гистерезиса
	{

		if (!turn)
			for (int i = 255; i >= 0; i--) {        //  в цикле меняем значение от 255 до 0
				analogWrite(active_color, i);      //  и записываем его в пин, соответствующий текущему активному цвету
				delay(5);                         //  Задержка в 5 мс
			}	
		else
			for (int i = 0; i <= 255; i++) {        //  в цикле меняем значение от 0 до 255 
				analogWrite(active_color, i);      //  и записываем его в пин, соответствующий текущему активному цвету
				delay(5);                         //  Задержка в 5 мс
			}
		turn = !turn;

		flag_2 = true;
		delay(500);

	}

	if (val_1 < 7 && flag_1 == true)       // 7-20 величина гистерезиса
	{

		flag_1 = false;
		delay(500);

	}

	if (val_2 < 7 && flag_2 == true)       // 7-20 величина гистерезиса
	{

		flag_2 = false;
		delay(500);

	}

	val_1 = 0;
	val_2 = 0;

}

void setColor(int red, int green, int blue)

{

	#ifdef COMMON_ANODE
		red = 255 - red;
		green = 255 - green;
		blue = 255 - blue;
	#endif

	analogWrite(RED_PIN, red);
	analogWrite(GREEN_PIN, green);
	analogWrite(BLUE_PIN, blue);

}