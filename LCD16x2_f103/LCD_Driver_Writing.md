# Writing LCD Display Driver for STM32f103C8

1. Driver must include macro/function to configure type of LCD.

    >For Example: 
    >
    >- LCD 16 x 2
    >
    >- LCD 16 x 4
    >
    >- LCD 20 x 4
    >
    >- etc

2. Driver must include macro/function to define 4-Bit and 8-Bit data mode.

3. Driver Must include functions followings:

    >- Configure LCD interfacing
    >
    >- Initialize Display
    >
    >- Clear Display
    >
    >- Set Cursor
    >
    >- Rotate text Left
    >
    >- Rotate text Right
    >
    >- Write Character
    >
    >- Write String