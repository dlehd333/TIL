# RPi.GPIO 라이브러리

- 라즈베리 파이의 확장 커넥터 핀을 범용 입출력(GPIO) 핀으로 제어하기 위한 파이썬 라이브러리
- 해당 라이브러리는 ```import RPi.GPIO as GPIO```처럼 추가한다

## RPi.GPIO 라이브러리 메서드
- import한 라이브러리는 ```GPIO.매서드명()```처럼 사용한다
- setmode(numbering)
    - 확정 커넥터 핀의 번호 할당 방법을 지정한다
    - GPIO.BOARD : 커넥터 핀 번호(물리적 핀 번호)
    - GPIO.BCM : CPU 핀 번호
- setup(channel, input/output, [pull_up_down 또는 initial])
    - 사용할 GPIO 판을 어떻게 사용할 것인지 설정
    - channel : 핀 번호
    - input/output : 입력(GPIO.IN), 출력(GPIO.OUT)
    - pull_up_down : 풀업 설정, 입력 핀이면 GPIO.PUD_UP, 출력 핀이면 GPIO.PUD_DOWN
    - initial : 출력핀일떄 초기 상태를 지정. 하이는 GPIO.HIGH, 로우는 GPIO.LOW
- output(channel, state)
    - channel로 지정한 핀에 state로 지정한 값을 출력
    - state : 0/GPIO.LOW/False 또는 1/GPIO.HIGH/True
- cleanup(channel)
    - channel에서 사용한 GPIO를 개방, 인수가 없으면 모든 GPIO를 개방
    - 프로그램이 종료될 때 사용한 GPIO를 개방해주지 않거나, 예외상황에서 종료될 경우 OS는 GPIO의 사용이 끝났음을 인지하지 못하고 계속 사용하는 것으로 판단한다. 재실행할 경우, 이미 할당된 GPIO라고 Warnning 메시지가 뜬다.
    - 그러므로, 프로그램을 종료할 때 반드시 실행해줘야 한다
- input(channal)
    - channel로 지정한 핀의 입력값을 리턴
    - 입력값은 0(0V) 또는 1(5V)

# try except 구문

- 프로그램 실행 중에 발생하는 오류를 예외(exception) 또는 런타임 오류(runtime error)라고 한다. 실행 중에 예기치 못한 상황이 발생해서 프로그램이 죽기도 하는데, 이런 상황에서 프로그램이 안정적으로 구동될 수 있도록 예외상황에 대한 처리를 잘해주어야 한다.
- 발생할 수 있는 예외상황을 고려해 if문 등으로 처리할 수도 있지만, 프로그래밍의 구조적인 문제로 인하여 조건문만으로 처리 불가능한 예외 상황이 발생할 경우에 대비해 사용하는 것이 try except 구문이다

```python
try:
	[코드]
except:
	[예외 발상시 실행하는 코드]
```

- try 아래에 예외가 발상할 수 있는 코드를 작성하고, 예외가 발생하면 except 블록을 실행하게 된다
- except 구문을 사용할 때 특정 에러를 입력하면, 특정 에러에 대응하는 코드를 사용할 수 있다
- except 구문을 통해 발생한 예외의 종류를 알 수 있다

```python
# 해당 구문을 여러개 사용해 여러 에러에 대응 할 수 있다
except KeyboardInterrupt:
	[KeyboardInterrupt 예외가 발생할 때 실행하는 코드]
except IndexError:
	[IndexError 예외가 발생할 때 실행하는 코드]

# 해당 구문을 사용하면 발생한 예외가 어떤것인지 확인할 수 있다
except Exception as e:
	print("예외 상황 발생 :", e)
```

- 여기에 추가적으로 else 구문을 사용하면 예외가 발생하지 않았을 때 코드를 실행할 수 있다
- 그리고, 예외가 발생하든 안하든 무조건 실행하는 코드를 넣을수도 있습니다. finally 구문을 사용하면 됩니다. finally 구문은 try에서 발생할 수 있는 각종 예외상황에 대해 어떻게든 수행하는 성질을 가지고 있어 자주 사용된다

```python
else:
	[예외가 발생하지 않았을 때 실행하는 코드]
finally:
	[무조건 실행하는 코드]
```

# 스위치

## 개요

- 입력 회로에 주로 사용된다. 즉, GPIO.input()메서드를 통해 스위치의 상태를 확인한다.
- 스위치를 켜거나 끄는 조작을 통해 라즈베리 파이에 전자 신호를 보낸다. 종류나 형태에 따라 다양한 스위치가 있다
- 버튼 스위치는 버튼을 누를때만 전기가 통하는 형태이다

## 버튼 스위치의 연결

- 스위치 회로와 연결된 핀은 입력 상태로, HIGH또는 LOW를 받아야 한다
- HIGH와 LOW의 중간값을 받으면 입력이 불안정해져 프로그램과 회로의 오동작의 원인이 된다
- 저항을 사용하여 항상 한쪽 레벨이 되도록 회로룰 구성한다
- 이때 VCC에 연결해 하이레벨이 되게 만드는 저항을 풀업 저항, GND에 연결해 로우레벨이 되게 하는 저항을 풀다운 저항이라고 한다.