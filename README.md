# Arduino_bet_game
Simple bet game by Arduino

**This is a simple game that you can bet which is the lucky fruit.**

- There are 5 fruits:
  1. Apple (represent 0 on the seven segment display, yellow light),
  2. Banana(represent 1 on the seven segment display, blue light),
  3. Cherry (represent 2 on the seven segment display, red light),
  4. Orange (represent 3 on the seven segment display, yellow light),
  5. Lemon(represent 4 on the seven segment display, blue light)
    
- In the begining, you have 5 chips. You can bet what ever you want with these five chips by keyboard.
- After enter numbers, it started to random pick the lucky fruit(number). 
- The result will show both on screen and seven segment display. 
- If you win, your chip will add 3 times.

**Bet**

![bet](https://github.com/Snoopy1994/Arduino_bet_game/blob/main/bet.png)

**Win**
- I bet each fruit for one chip. 
- 5 Chips -> 0 Chips
![win](https://github.com/Snoopy1994/Arduino_bet_game/blob/main/win.png)
- The lucky fruit is Banana(number:1).
- 0 Chips -> 3 Chips
- My chips add 3. 

**Lose**
- I bet Apple for one chip. 
- 3 Chips - 1 Chip -> 2 Chips
![lose](https://github.com/Snoopy1994/Arduino_bet_game/blob/main/lose.png)
- The lucky fruit is Cherry(number:2).
- Total fund: 2 Chips

(Continue until Chip = 0)
