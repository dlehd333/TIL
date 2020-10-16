import RPi.GPIO as GPIO
import I2C_LCD_driver
import serial
import time
import threading

GPIO.setmode(GPIO.BOARD)
mylcd = I2C_LCD_driver.lcd()
ser = serial.Serial('/dev/ttyAMA0', 9600)

FND_DATA_PIN = [31,32,33,35,36,37,38,40]  # A,B,C,D,E,F,G,DP
FND_DIGIT_PIN = [21,22,23,24]   # com port
FND_DATA = [0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90]  # 숫자 정보

SW1, SW2 = 11, 13   # 스위치 핀

res = ""    # 입력버퍼
x = y = 0   # 입력받은 숫자 저장할 변수

fnd_count = 0   # fnd 작동에 사용할 카운트, start/stop변수
fnd_plus = True

thread_stop = 0 # 쓰레드 종료 처리 변수

def fnd4_initial(str_num):  # fnd 초기화
    for i in FND_DATA_PIN:
        GPIO.setup(i, GPIO.OUT, initial=GPIO.LOW)
    for i in FND_DIGIT_PIN:
        GPIO.setup(i, GPIO.OUT, initial=GPIO.LOW)
    fnd4_number_display(str_num)

def fnd4_clear_digit(): # fnd com포트 전체 끄기
    for i in range(0,4):
        GPIO.output(FND_DIGIT_PIN[i], GPIO.LOW)
    
def fnd4_cntl(data, digit): # fnd 한칸에 숫자 입력
    for i in range(0,8):
        GPIO.output(FND_DATA_PIN[i], FND_DATA[int(data)] & (0x01<<i))
    fnd4_clear_digit()
    GPIO.output(FND_DIGIT_PIN[int(digit)], GPIO.HIGH)

def fnd4_number_display(str_num):   # fnd 전체 출력 
    str_num = "%04d" % int(str_num)
    for i in range(0,4):
        fnd4_cntl(str_num[i], str(i))
        time.sleep(0.0001)
        fnd4_clear_digit()
        
def fnd_output():   # fnd 출력 함수(쓰레드)
    global fnd_count
    while True:
        fnd4_number_display(str(fnd_count))
        
        if thread_stop == 1:
            break

def fnd_func(channel):  # 스위치 인터럽트 콜백함수
    global fnd_count, fnd_plus
    if channel == SW1:
        fnd_plus = not fnd_plus
    elif channel == SW2:
        fnd_count = 0

try:
    fnd4_initial(str(fnd_count))
    GPIO.setup(SW1, GPIO.IN)    # 핀 설정
    GPIO.setup(SW2, GPIO.IN)
    GPIO.add_event_detect(SW1, GPIO.RISING, callback=fnd_func, bouncetime=300)  # 인터럽트 이벤트 설정
    GPIO.add_event_detect(SW2, GPIO.RISING, callback=fnd_func, bouncetime=300)
    
    thread1 = threading.Thread(target=fnd_output)
    thread1.start() # 쓰레드 초기화 및 시작
    
    while True:
        res = ser.readline()    # 입력받음
        
        res = res.decode()  # BYTE타입 변환
        if 'x' in res:  # 맨 앞 문자 검사하여 가공
            x = int(res[1:])
        elif 'y' in res:
            y = int(res[1:])
        
        strdata = "x:"+str(x)+" y:"+str(y)  # 가공한 문자 합침
        print(strdata)  # 출력
        
        mylcd.lcd_clear()   # LCD에 출력
        mylcd.lcd_display_string("joystick data",1)
        mylcd.lcd_display_string(strdata,2)
        
        if fnd_plus:    # fnd 카운트 값 증가
            fnd_count += 1
            
            
        time.sleep(0.05)

finally:    # 종료 시
    thread_stop = 1 # 쓰레드 종료 명령
    thread1.join()  # 쓰레드 종료시까지 대기
    ser.close() # 시리얼 닫기
    GPIO.cleanup()  # GPIO 해제