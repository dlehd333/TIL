import RPi.GPIO as GPIO # 라이브러리
import time

GPIO.setmode(GPIO.BOARD)    # 핀번호 사용 방식 설정

LED1, SW = 11, 13   # 핀 번호 저장
flag_LED = 0

def myFunc(channel):    # 인터럽트 서비스 루틴, 스위치 토글 상태를 변경
    global flag_LED, SW
    if flag_LED == 0:
        flag_LED = 1
    else:
        flag_LED = 0

GPIO.setup(LED, GPIO.OUT)   # 핀의 설정. 입력으로 사용할지 출력으로 사용할지 설정.
GPIO.setup(SW, GPIO.IN)
GPIO.add_event_detect(SW, GPIO.RISING, callback=myFunc, bouncetime=300) # 인터럽트에 인터럽트 서비스 루틴 설정

try:
    while True: # loop 구간. 스위치 토글 상태에 따라 LED를 조절한다
        if flag_LED == 0:
            GPIO.output(LED, GPIO.LOW)
        else:
            GPIO.output(LED, GPIO.HIGH)
            time.sleep(0.3)
            GPIO.output(LED, GPIO.LOW)
            time.sleep(0.3)
finally:    # 마지막에 사용한 핀을 해제해준다
    GPIO.cleanup()