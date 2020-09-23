# Reentrant VS Thread-safe

# Thread-safe(쓰레드 안전)

- 메뉴얼 표기시 MT-safe, MT-safety, Thread-safe라고 표기한다
- 멀티 스레드 환경에서 안전하게 결과를 내어주는 것
- thread-safe 함수는 mutex등을 사용하여 전역변수에 대한 동시접근을 막아서 멀티스레드 환경에서 안전하게 결과를 보장한다
- 여러 쓰레드에 의해 동시에 수행되더라도, 실행결과의 정확성이 보장되는 것

# Reentrant(재진입성)

- 둘 이상의 쓰레드에 의해 호출되었을 때, 호출된 순서에 상관없이 하나가 수행되고 난 다음 다른 함수 호출이 수행된 것처럼 제대로 된 결과를 내어주는 것
- reentrant 함수는 (1) 전역변수 사용안함 (2) static변수 사용안함 (3)stack변수만 사용 으로 보장된다
- reentrant 함수가 필요한 상황은 (1)시그널 핸들러를 사용 가능한지, (2)멀티 쓰레드 환경에서 사용 가능한지 이다.
- 여러 쓰레드에 의해 코드가 동시에 수행될 수 있고, 그런 경우에도 실행결과의 정확성이 보장되는 것

# Thread-safe의 한계

- 전역변수를 사용하는 함수가 있다고 할 때, 전역변수를 사용하는 부분을 lock 동기화 하여 동시에 전역변수에 접근하지 못하게 한다. 이런 경우 한 프로세스(쓰레드)가 함수에 진입하여 실행중에 시그널이 발생하여 시그널 핸들러가 호출되 lock 되어있는 전역변수를 호출하여 수행 결과가 바뀌거나, 시그널 핸들러에서 다시 이 함수를 호출하면 deadlock이 걸릴 수 있다.
- 또한, thread-safe한 코드는 reentrant한 코드보다 효율성이 떨어질 가능성이 높다. 해당 코드를 수행하고 있는 thread가 공유 자원에 대한 lock이 풀리기를 기다리는 동안은 다른 thread의 수행을 막아버리기 때문이다.

# Signal handler

- 시그널이란, 프로세스에 뭔가 발생했음을 알리는 간단한 메시지를 비동기적으로 보내는것이다. 시그널을 받은 프로세스는 행동 중이더라도 시그널에 따른 기본 동작을 수행하거나, 특별히 지정된 함수를 수행하거나, 무시할 수 있다.
- 시그널 핸들러(signal handler)란, 시그널 처리를 위해 지정하는 함수를 의미한다. 시그널을 받으면 기존 처리 작업을 중지한 후 시그널 핸들러를 호출하여, 시그널 핸들러의 동작이 완료되면 기존 처리 작업을 수행한다.

# Reentrant VS Thread-safe

- reentrant와 Thread-safe의 가장 큰 차이는 코드가 어떤한 경우에도 병렬 실행을 보장할 수 있느냐의 여부이다.
- reentrant는 SUSv3 표준안에 의하면 "reentrant 함수는 둘 이상의 쓰레드에 의해서 호출될 경우에 순서에 구애받지 않고, 서로 동일한 코드가 겹쳐서 실행되어도 작동이 보장되어야 함"을 말하고 있다. 즉, **reentrant 함수는 재귀호출을 포함한 병렬 실행을 완벽히 보장하는 코드**를 의미한다.
- Thread-safe는 SUSv3 표준안에 의하면 "복수의 쓰레드에서 호출 될 수 있고 병렬로 실행 될 수도 있다. 다만 완벽한 병렬을 보장하지는 않고 정적 공간(전역변수)이나 공유 객체가 있다면 MUTEX와 같은 메커니즘으로 보호해야 한다. 그리고 뮤텍스 락으로 보호되는 서브 루틴은 직렬로 실행된다"고 말하고 있다. 따라서 **'오직 쓰레드의 안전'만을 만족하는 코드라면, 정적 공간이나 공유 객체를 사용하면 진입순서에 따라 실행 결과가 달라질 수 있다.**
- 즉, **모든 reentrant 함수는 thread-safe를 만족하지만, 그 역은 성립하지 않고**, reentrant 함수는 정적 공간이나 공유 객체를 사용하지 않아야 한다는 것을 알 수 있다.
- 함수를 만들었는데 병렬 실행이 가능하고 정적 공간을 사용하지 않는 구조라면 reentrant 함수라고 말할 수 있고, 병렬 실행이 가능하지만 서브 루틴에서 static 변수나 공유 객체 등을 사용하며 이를 lock으로 보호해두었다면 thread-safe만 만족하는 함수라고 말할 수 있다.

# reentrant 함수로 변경

- **규칙1. 전역 공간이나 static 영역, 공유 객체(Heap 등)는 사용하지 않는다**
- **규칙2. 원래 함수의 리턴값은 인수 리스트에 포인터 변수 형태로 대체한다**
- 규칙3. 리턴값은 int를 사용하고, 성공시 0, 실패시 -1을 리턴한다(관습적)
- 규칙4. 함수이름의 맨 뒤에 _r을 붙여서 만든다(관습적)

---

## 참고한 사이트

이즈군 - 함수, 서브루틴의 재진입성(Reentrant)이란? Thread-safe와 reentrancy.

- [http://blog.naver.com/PostView.nhn?blogId=complusblog&logNo=220985740336](http://it.plusblog.co.kr/220985740336)

김윤수 - Reentrant 와 Thread-safe 의 차이

- [https://yesarang.tistory.com/214](https://yesarang.tistory.com/214)

규한아빠 - reentrant function thread-safe function

- [https://stoneshim.tistory.com/42](https://stoneshim.tistory.com/42)

risinsun - thread safe와 reentrance

- [http://blog.daum.net/risinsun2/12](http://blog.daum.net/risinsun2/12)

sunyzero - C언어:reentrant (재진입성) 함수와 쓰레드안전(MultiThread-safe)

- [https://sunyzero.tistory.com/97](https://sunyzero.tistory.com/97)

12bme - [시스템프로그래밍]시그널

- [https://12bme.tistory.com/224](https://12bme.tistory.com/224)