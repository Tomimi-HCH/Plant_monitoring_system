#ifndef __LED_H
#define __LED_H

#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC

// 函数声明
extern void LedOn(void);
extern void LedOff(void);
extern void BlueShine(void);

#endif /* __LED_H */
