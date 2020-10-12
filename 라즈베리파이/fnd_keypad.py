import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

FND_DIGIT_PIN = [8, 10, 12, 16]
FND_DATA_PIN = [22,24,26,18,32,36,38,40]
FND_DATA = [0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90]

KEY_C = [19, 21, 23, 29]
KEY_R = [31, 33, 35, 37]

def keypad_initial():   # 키패드 초기화
    for i in KEY_R: # 가로는 출력으로
        GPIO.setup(i, GPIO.OUT, initial=GPIO.LOW)
    for i in KEY_C: # 세로는 입력으로
        GPIO.setup(i, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

def keypad_getkey():    # 키패드 값 읽기
    res = 0
    for i in range(0,4):
        GPIO.output(KEY_R[i], GPIO.HIGH)    # 가로 부분을 하나씩 HIGH로
        for k in range(0,4):    # 세로 부분의 입력값을 확인해 HIGH라면 가로x세로의 입력 확인
            if(GPIO.input(KEY_C[k])==GPIO.HIGH):
                res = i * 4 + (k + 1)
        GPIO.output(KEY_R[i], GPIO.LOW) # 한 가로 부분의 검사가 끝나면 LOW로
    return res  # 위치(결과)값 리턴

def fnd4_initial(str_num):  # FND 초기화
    for i in FND_DATA_PIN:
        GPIO.setup(i, GPIO.OUT, initial=GPIO.LOW)
    for i in FND_DIGIT_PIN:
        GPIO.setup(i, GPIO.OUT, initial=GPIO.LOW)
    fnd4_number_display(str_num)

def fnd4_cntl(data, digit): # data : 표시할 데이터, digit : 표시할 위치
    for i in range(0, 8):
        GPIO.output(FND_DATA_PIN[i], FND_DATA[int(data)] & (0x01<<i))
    GPIO.output(FND_DIGIT_PIN[digit-1], GPIO.HIGH)
    
def fnd4_clear_digit(): # FND 전체 화면 LOW
    for i in range(0,4):
        GPIO.output(FND_DIGIT_PIN[i], GPIO.LOW)

def fnd4_number_display(str_num):   # FND에 실제 숫자를 출력하는 함수
    str_num = "%04d" % int(str_num)
    fnd4_cntl(str_num[0],1)
    time.sleep(0.001)
    fnd4_clear_digit()
    fnd4_cntl(str_num[1],2)
    time.sleep(0.001)
    fnd4_clear_digit()
    fnd4_cntl(str_num[2],3)
    time.sleep(0.001)
    fnd4_clear_digit()
    fnd4_cntl(str_num[3],4)
    time.sleep(0.001)
    fnd4_clear_digit()

try:    # 초기화(setup) 부분
    cnt = 0
    fnd4_initial(str(cnt))
    keypad_initial()
    
    while True: # 반복(loop) 부분
        temp = 0
        temp = keypad_getkey()  # 키패드 입력값 확인
        if temp != 0:   # 키패드가 입력되었다면 해당 값 받기
            cnt = temp
        fnd4_number_display(str(cnt))   # 입력받은 숫자 출력하기
        
finally:
    GPIO.cleanup()
