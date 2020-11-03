# C# 이란

- C# C언어 패밀리(C, C++)의 파생이지만, Java의 영향을 많이 받은 언어이다
- 하지만, 시간이 지나면서 Java와 C#의 모양은 많이 달라졌다
- C#은 Managed Code로, .net framework 아래에서 작동한다

# Hello world

- C#의 프로그램 구조는 네임스페이스 → 클래스 → 매서드로 구성된다. 처음 네임스페이스는 생략이 가능하다

```csharp
namespace HelloWorld
{
	class Program
	{
		static void Main(string[] args) { }
	}
}
```

- C#은 모든 프로그램이 클래스 안에 들어있어야 한다는 제약이 있다. 그래서 Main도 클래스 안에 존재한다.
- C#의 표준 라이브러리를 BCL(Base Class Library)이라고 부른다.
- C#은 라이브러리로 제공하는 클래스들을 네임스페이스로 묶어서 제공하고 있어서, 다른 네임스페이스를 통해 클래스 명칭등을 사용할 수도 있다.
- using [네임스페이스] (```using System```)로 입력하여, 사용가능한 네임스페이스를 불러올 수 있다.
- ```Console.Write()```는 System 네임스페이스 아래 Console 클래스에 Write() 메서드를 사용한 것이다

```csharp
using System;
Console.Write("hello world");
Console.WriteLine("hello world"); // 출력 후 한줄 내림

System.Console.Write("hello world"); // using을 사용하지 않고 사용할 때!
```

- Main 메서드는 C#의 특별한 메소드로, C언어의 main처럼 진입점(Entry Point)역할을 한다. 그러므로, Main 메서드는 프로그램에 1개만 있어야 한다.
- C언어와 똑같이 프로그램 시작 시 실행되고, Main 메서드가 종료되면 프로그램이 종료된다.

## CLR(Common Language Runtime)

- C#으로 만든 프로그램의 실행 환경을 의미한다. .NET 프레임워크에 포함되어 있다.
- C#은 코드를 컴파일하게 되면, 바로 기계어가 나오지 않고 중간 언어인 IL(Intermediate Language)파일이 나온다.
- 이 IL을 나중에 JIT(Just In TIme) 컴파일로 바이너리로 만들어 실행하게 된다

추가 : [Managed Code](./Managed_Code_2020-11-03.md)