## 변수 선언 부분 ##
num1, num2, ch, res, mode = None, None, None, None, None

## 함수 선언 부분 ##
def bit_opt():  # 논리 연산 함수
    global num1, num2, ch, res
    num1 = int(input("논리연산이 선택됐습니다\n첫번째 4비트 값을 입력하세요? "), 2) # 2진수로 입력받는다
    ch = input("계산할 연산자를 입력하세요(&/|/^)? ")
    num2 = int(input("두번째 4비트 값을 입력하세요? "), 2) # 2진수로 입력받는다
    if ch == '&':           # 입력받은 연산자에 따라 계산함
        res = num1 & num2
    elif ch == '|':
        res = num1 | num2
    elif ch == '^':
        res = num1 ^ num2
    print("0b{0:04b} {1:s} 0b{2:04b} = 0b{3:04b}".format(num1, ch, num2, res))
    # 2진수를 나타내는 b타입 서식은 format으로만 구현 가능하다(%에는 없다)
    # 0b1011 & 0b0111 = 0b0011
def art_opt():  # 산술 연산 함수
    global num1, num2, ch, res
    num1 = int(input("산술연산이 선택됐습니다\n첫번째 수를 입력하세요? "))
    ch = input("계산할 연산자를 입력하세요(+/-/*//)? ")
    num2 = int(input("두번째 수를 입력하세요? "))
    if ch == '+':           # 입력받은 연산자에 따라 계산함
        res = num1 + num2
    elif ch == '-':
        res = num1 - num2
    elif ch == '*':
        res = num1 * num2
    elif ch == '/':
        res = num1 // num2
    print("{0:d} {1:s} {2:d} = {3:d}".format(num1, ch, num2, res))
    # 16 + 14 = 30
def bit_shift():    # 비트 시프트 함수
    global num1, num2, ch, res
    num1 = int(input("비트연산이 선택됐습니다\n4비트 값을 입력하세요? "), 2)  # 2진수로 입력받는다
    ch = input("계산할 연산자를 입력하세요(<</>>)? ")
    num2 = int(input("시프트 횟수를 입력하세요? "))
    if ch == '<<':          # 시프트 연산자에 따라 시프트 횟수만큼 이동함
        res = num1 << num2
    elif ch == '>>':
        res = num1 >> num2
    print("0b{0:08b} 입니다.".format(res))
    # 1011 << 4 -> 0b10110000
    # 정수의 사이즈 제한이 없어 왼쪽 시프트 사용시 계속 값이 커지게 된다
    # 값의 범위가 지정된 서식을 넘어설 경우 값의 범위를 우선하여 출력하게 된다
    # 1011 << 5 -> 0b101100000 # 왼쪽으로 8bit 이상도 커지고, 서식을 넘어서서 값의 범위만큼 출력

## 메인(main) 코드 부분 ##
mode = int(input("""1. 논리연산
2. 산술연산
3. 시프트연산
? """))
# 이렇게 작성하면 여러줄의 긴 문장 뒤에 입력을 받을 수도 있다

if mode == 1:   # if문을 사용해 입력받은 숫자에 따라 연산을 진행한다
    bit_opt()
elif mode == 2:
    art_opt()
elif mode == 3:
    bit_shift()