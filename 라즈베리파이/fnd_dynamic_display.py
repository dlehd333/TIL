# 공용 양극
import RPi.GPIO as GPIO # 라이브러리
import time
import random

GPIO.setmode(GPIO.BOARD)

FND_COM_PIN = [8, 10, 12, 16]
FND_DATA_PIN = [22,24,26,18,32,36,38,40]
FND_DATA = [0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90] # 숫자 정보

start = time.time() # 시작 시간 입력. 이후 현재 시간과 비교해 진행 시간을 구한다

## function
def showNum(com, data): # 숫자를 입력하는 함수, 인자는 위치와 숫자
    global FND_COM_PIN, FND_DATA_PIN, FND_DATA
    for i in range(4):  # 지정 위치를 제외한 다른 위치는 꺼준다
        if com == i:
            GPIO.output(FND_COM_PIN[i], GPIO.HIGH)
        else:
            GPIO.output(FND_COM_PIN[i], GPIO.LOW)
    for i in range(8):  # 숫자를 입력한다
        GPIO.output(FND_DATA_PIN[i], (FND_DATA[data]>>i) & 0x01)
    time.sleep(0.005)   # 잔상 조절을 위한 딜레이

## setup
for i in FND_COM_PIN:   # com핀, 처음에는 다 꺼준다
    GPIO.setup(i, GPIO.OUT, initial=GPIO.LOW)

for i in FND_DATA_PIN:  # data핀, 처음에는 다 꺼준다
    GPIO.setup(i, GPIO.OUT, initial=GPIO.HIGH)

## loop
try:
    while True:
        num = int(time.time() - start)  # 프로그램 진행 시간을 구해준다
        # 자리별로 숫자를 출력해준다
        showNum(0, int((num % 10000) / 1000))
        showNum(1, int((num % 1000) / 100))
        showNum(2, int((num % 100) / 10))
        showNum(3, int(num % 10))
finally:
    GPIO.cleanup()