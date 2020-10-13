# Tkinter 버튼 command에 인수 넣기
## partials

- functools 모듈에서 partial 객체를 사용하는 방법

```python
from functools import partial
```

- functools는 호출 가능한 기존의 객체, 함수를 사용하여 다른 함수를 반환하거나 활용할 수 있게 해준다
- functools partial 함수는 기존 파이썬 함수를 재사용하여 일부 위치 매개변수 또는 키워드 매개변수를 고정한 상태에서 원래의 함수처럼 작동하는 새로운 객체(partial object)를 반환한다

```python
# python build-in function int(x, base=10)
int('101', base=2) # out : 5
basetwo = partial(int, base=2) # base인자를 2로 고정
basetwo('101') # out : 5
```

- 위 예제는 int()함수를 재활용해서 base인자를 2로 고정해 새로 만든 basetwo()라는 이름의 함수이다
- 새로 만들어진 객체는 아래와 같은 속성을 가지고 있다

```python
basetwo.func # int
basetwo.args # ()
basetwo.keywords # {'base':2}
```

## lambda

- 람다 표현식(almbda expression)을 사용하면 함수를 간편하게 작성할 수 있어, 다른 함수의 인수로 넣을 때 주로 사용한다
- 람다 표현시은 아래와 같이 lambda에 매개변수를 지정하고 :(콜론) 뒤에 반환값으로 사용할 식을 지정한다

```python
# lambda 인자 : 표현식
>>> lambda x : x + 10
<function <lambda> at 0x02C27270>
```

- 콘솔에 그대로 실항하면 함수 객체가 나오는데, 이 상태로는 함수를 호출 할 수 없다. 왜냐하면 람다 표현식은 이름이 없는 함수를 만들기 때문이다. 그래서 람다 표현식을 익명 함수(anonymous function)로 부르기도 한다
- 그래서 람다 표현식으로 만든 익명 함수를 호출하려면 람다 표현식을 변수에 할당해주면 된다. 또한 함수를 인자로 받는 함수에 사용할 수 있다.

```python
plus_ten = lambda x : x + 10
plus_ten(1) # 11
```

## Tkinter 버튼 command에 인수 넣기

### 1. partials를 사용

```python
from functools import partial
def change_label_number(num):
	# ...
buttonExample = tk.Button(app, text="Increase", width=30,
                          command=partial(change_label_number, 2))
```

- partial(change_label_number, 2)는 호출될 때, 마치 change_label_number함수에 2를 인자로 넣어 동작하는 함수처럼 동작하는 호출 가능한 객체를 반환한다

### 2. lambda를 사용

```python
def change_label_number(num):
	# ...
buttonExample = tk.Button(app, text="Increase", width=30,
                          command=lambda: change_label_number(2))
```

- lambda:change_label_number(2)는 인자가 따로 필요하지 않아 인자 목록을 비워두고, 표현식만 사용하여 change_label_number함수에 2를 인자로 넣어 동작하는 함수를 익명 함수로 불러올 수 있다

# 출처

- [Tkinter 버튼 명령에 인수를 전달하는 방법](https://www.delftstack.com/ko/howto/python-tkinter/how-to-pass-arguments-to-tkinter-button-command/) - DelftStack

