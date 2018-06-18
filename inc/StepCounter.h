#ifndef STEPCOUNTER_H_
#define STEPCOUNTER_H_

void Work();
void TIM3_IRQHandler(void);
void CheckStep();
void Clear();
void sendStep(int step);


#endif

