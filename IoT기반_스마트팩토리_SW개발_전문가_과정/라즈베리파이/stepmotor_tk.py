import RPi.GPIO as GPIO
import time
import tkinter as tk
import threading

from functools import partial

GPIO.setmode(GPIO.BOARD)

STEP_PIN = [31, 33, 35, 37]

GPIO.setup(STEP_PIN, GPIO.OUT, initial=GPIO.LOW)

def step_rotate():  # 스텝모터 회전 함수(쓰레드)
    while True:
        for i in (range(0,4) if dirr==1 else reversed(range(0,4))): # 방향에 따라 회전
            GPIO.output(STEP_PIN[i], (GPIO.HIGH if dirr==1 else GPIO.LOW))
            GPIO.output(STEP_PIN[i-1], (GPIO.LOW if dirr==1 else GPIO.HIGH))
            time.sleep(0.0025)

        if thread_stop == 1:    # 프로세스 종료 상황 시 쓰레드 종료
            break

def ch_dir(val):    # 스텝모터 방향 변경 함수(버튼 커맨드)
    global dirr
    dirr = val

try:
    thread_stop = 0 # 쓰레드 종료 알림 변수
    dirr = 1    # 스텝모터 방향 변수
    
    t1 = threading.Thread(target=step_rotate)   # 쓰레드 생성(스텝모터 회전)
    t1.start()
    
    root = tk.Tk()  # 윈도우 객체 생성
    
    # 라디오버튼, 선택한 버튼에 따라 방향이 정해짐
    radio1 = tk.Radiobutton(root, text='정방향', value=1, command=partial(ch_dir, 1))
    radio2 = tk.Radiobutton(root, text='역방향', value=2, command=partial(ch_dir, -1))
    
    radio1.pack()
    radio2.pack()
    root.mainloop() # 윈도우 출력
    
finally:
    thread_stop = 1
    t1.join()
    GPIO.cleanup()
