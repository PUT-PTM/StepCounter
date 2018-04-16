#ifndef GPIO_H_
#define GPIO_H_

void initGPIODiodes(void);
void initExtBtns(void);
void initExtRGBTim4(void);
void initLedSegment(void);
void setLedSegment(int number);
void resetLedSegment(int number);
void setLedSegmentAndResetOthers(int number);
void resetNumberOnSegment(void);
void setNumberOnSegments(int number);
void setNumber0(void);
void setNumber1(void);
void setNumber2(void);
void setNumber3(void);
void setNumber4(void);
void setNumber5(void);
void setNumber6(void);
void setNumber7(void);
void setNumber8(void);
void setNumber9(void);
void setNumberDot(void);

#endif
