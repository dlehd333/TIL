# UnManaged Code(Native Code)

- 전통적으로 우리가 생각하는 프로그래밍은 Native code이다
- 컴파일하면, OS가 해석 가능한 기계어로 바로 번역된다

# Managed Code

- 컴파일하면, Native처럼 기계어로 바로 번역되지 않고 임시 코드로 변환된다
- 이후, OS에 설치된 전용 컴파일러에서 기계어로 번역된다
- 이처럼 프로그램을 실제 실행하는 시점에 기계어로 번역하는 컴파일 기법을 JIT 컴파일(Just In Time) 또는 동적 번역(Dynamic Translation)이라고 한다

# Managed vs UnManaged

## 1. 메모리의 관리

- 프로그램 실행시 사용한 메모리를 프로그램이 끝날 때 모두 OS에 반납해야 하는데, UnManaged에서는 직접 반납해야 한다. 이 경우, 반납하지 않게 되면 시스템 에러로 이어질 수 있다
- managed code는 Garbage Collection을 지원하여, 프로그램에서 메모리 해제를 하지 않더라도 알아서 해준다. 그래서 대체로 managed code에서는 포인터를 지원하지 않는다
- 하지만, Managed는 메모리의 구체적인 관리를 할 수 없기 때문에 프로그래밍의 자유도가 UnManaged보다 낮으며, 비정기적인 메모리 정리가 이루어진다

## 2. OS 종속성

- UnManaged는 OS에 종속적이다. 같은 코드를 컴파일해도 OS와 H/W에 따라 그 내용이 달라질 수 있어 생각지 못한 문제가 생길 수 있다.
- 그래서, 다른 OS로 Porting할 떄 마다 컴파일을 다시 해야 하고, 코드의 내용 또한 변경해야 하는 불편함이 있다.
- Managed는 어디서 작성하든 똑같은 소스를 사용해 똑같은 결과를 보여준다. 이런것이 되는 이유는, 컴파일 될 때 바로 OS가 이해할 수 있는 기계어로 변환되는게 아니고 임시 코드(IL)로 변환되기 때문이다.
- 이 IL코드는 실제로 OS에서 실행할 수 없다. 실행되기 위해서는 각 OS에 설치되어 있는 JIT(Just In Time) 컴파일러가 OS용 코드로 변환해주어야 한다. 이로 인해, JIT 컴파일러가 설치되어 있는 OS라면 어디서나 같은 동작을 하게 된다
- 하지만 반대로, JIT 컴파일을 지원하는 컴파일러(가상머신)가 해당 OS에 깔려 있어야만 해당 프로그램이 작동한다. 이는 단점이 될 수도 있다.

## 3. 실행속도

- Managed는 UnManaged에 비해 컴파일 과정이 복잡하기 때문에 실행속도가 느린 편이다.
- 하지만 현대에 이르러서는, 컴파일러의 성능이 좋아지고 고도의 최적화가 진행되어, 속도 차이를 단점으로 꼽기에는 무리가 있다.

## 4. 대표적인 프로그램

- Java이전, C/C++ 등의 전통적인 언어는 대부분 UnManaged(Native) 언어이다.
- Managed 언어의 형태로 나온 첫 언어는 Java이며, 이후 Microsoft에서 이에 대항하기 위에 만든 것이 C#이다.
- Java는 JVM(Java Virtual Machine)이 JIT 컴파일러 역할을 하며, C#은 .NET 프레임워크가 해당 역할을 하고 있다
- JVM(자바가상머신)에서 사용되는 언어는 Java, Scala, Kotiln 등이 있다
- .NET 프레임워크에서 사용되는 언어는 C#, VB .NET, C++ .NET 등이 있다

### <출처>

- ssaturn - [Managed Code vs Native Code의 차이]([https://ssaturn.tistory.com/99](https://ssaturn.tistory.com/99))
- Dongkey - [Managed(매니지드) 언어 vs Unmanaged(언매니지드) 언어]([https://dongkey2183.tistory.com/27](https://dongkey2183.tistory.com/27))
- 사용자 쩡니남편 - [※IT 개념정리]([https://betrider.tistory.com/entry/※IT-개념정리](https://betrider.tistory.com/entry/%E2%80%BBIT-%EA%B0%9C%EB%85%90%EC%A0%95%EB%A6%AC))