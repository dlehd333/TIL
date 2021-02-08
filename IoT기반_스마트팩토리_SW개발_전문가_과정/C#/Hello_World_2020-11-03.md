# C# 이란

- C# C언어 패밀리(C, C++)의 파생이지만, Java의 영향을 많이 받은 언어이다
- 하지만, 시간이 지나면서 Java와 C#의 모양은 많이 달라졌다
- C#은 Managed Code로, .net framework 아래에서 작동한다

# C#의 프로그램 구조

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
- Main 메서드는 C#의 특별한 메소드로, C언어의 main처럼 진입점(Entry Point)역할을 한다. 그러므로, Main 메서드는 프로그램에 1개만 있어야 한다.
- C언어와 똑같이 프로그램 시작 시 실행되고, Main 메서드가 종료되면 프로그램이 종료된다.
- C#은 모든 프로그램이 클래스 안에 들어있어야 한다는 제약이 있다. 그래서 Main도 클래스 안에 존재한다.

# CLR(Common Language Runtime)

- C#으로 만든 프로그램의 실행 환경을 의미한다. .NET 프레임워크에 포함되어 있다.
- C#은 코드를 컴파일하게 되면, 바로 기계어가 나오지 않고 중간 언어인 IL(Intermediate Language)파일이 나온다.
- 이 IL을 나중에 JIT(Just In TIme) 컴파일로 바이너리로 만들어 실행하게 된다

추가 : [Managed Code](./Managed_Code_2020-11-03.md)

# BCL(Base Class Library)

- C#의 표준 라이브러리를 BCL(Base Class Library)이라고 부른다.
- C#은 라이브러리로 제공하는 클래스들을 네임스페이스로 묶어서 제공하고 있어서, 다른 네임스페이스를 통해 클래스 명칭등을 사용할 수도 있다.
- using [네임스페이스] (```using System```)로 입력하여, 사용가능한 네임스페이스를 불러올 수 있다.

추가 : [.NET의 구성요소](/.NET/.NET의_구성요소_2020-11-04.md)

# 출력

- 기본적인 출력 메서드는 WriteLine()이다. System 네임스페이스 아래 Console 클래스에 WriteLine() 메서드를 사용한 것이다. WriteLine() 메서드는 대부분의 타입을 지원한다
```csharp
public static void WriteLine();
public static void WriteLine(int value);
public static void WriteLine(double value);
public static void WriteLine(string value);
public static void WriteLine(string format, params object[] arg);
```
- 무엇이든 전달하면 화면에 출력된다. 인수없이 단독으로 호출하면 다음 줄로 개행만 한다.
- 개행하지 않고 여러 개의 변수를 한 줄에 출력하려면 Write() 메서드를 사용한다.
```csharp
using System;
Console.Write("hello world"); // 출력 후 커서가 그대로 있음
Console.WriteLine("hello world"); // 출력 후 한줄 내림

System.Console.Write("hello world"); // using을 사용하지 않고 사용할 때!
```

# 입력

- 기본적인 입력 메서드는 ReadLine()이다. System 네임스페이스의 Console 클래스의 메서드이다.

```csharp
public static string ReadLine()
```

- 문자열로 입력받기 때문에 형식이 간단하며, 인수없이 그냥 호출한다.
- 정수나 실수가 필요하다면 문자열로 받은 후, 변환해서 사용해야 한다.

```csharp
string str;
str = Console.ReadLine();
int integer;
integer = Convert.ToInt32(str);

// 위 과정을 한번에 실행할 수도 있다
int integer = Convert.ToInt32(Console.ReadLine());
```

- 문자열이나 정수가 아닌 키 자체를 입력받을 때는 ReadKey() 메서드를 사용한다. 역시나 System 네임스페이스의 Console 클래스의 메서드이다

```csharp
public static ConsoleKeyInfo ReadKey([bool intercept])
// 괄호 안 대괄호([])는 생략 가능을 의미
```

- 키 하나만 입력받기 때문에 엔터키를 누르지 않아도 즉시 리턴된다
- 커서 이동키나 펑션키, Del등의 기능키도 입력받는다, 단 조합키인 Ctrl, Alt, Shift는 키 입력으로 간주하지 않는다
- intercept는 입력받은 키를 화면으로 다시 출력할 것인지 지정한다. 생략하면 false가 적용된다.
- 입력받은 키 정보를 ConsoleKeyInfo 구조체로 리턴하며 Key맴버에 사용자가 누른 키의 이름이 전달된다. 키의 이름은 ConsoleKey 열거형으로 정의되어 있다. 대표적인 이름은 다음과 같다.

|열거형|키|
|---|---|
|A~Z|A~Z 키|
|D0~D9|0~9 숫자키|
|F1~F24|F1~F24 펑션키|
|NumPad0~NumPad9|NumPad의 숫자키0~9|
|Insert,Delete|Insert,Delete키|
|Home,End|Home,End키|
|PageDown,PageUp|PgDn,PgUp키|
|Enter,Escape|Enter,Esc키|
|SpaceBar,Tab|공백키,Tab키|
|BackSpace|←키(BS)|
|LeftArrow,RightArrow,UpArrow,DownArrow|커서 이동키|
|PrintScreen|PtrSc키|

```csharp
// 키입력 예제
ConsoleKeyInfo cki;
int x = 10, y = 10;
while(true)
{
	Console.Clear(); // 콘솔 지우기
	Console.SetCursorPosition(x,y); // 커서 이동
	Console.Write("#");
	cki = Console.ReadKey();
	switch(cki.Key){
	case ConsoleKey.LeftArrow:
		x--; break;
	case ConsoleKey.RightArrow:
		x++; break;
	case ConsoleKey.UpArrow:
		y--; break;
	case ConsoleKey.DownArrow:
		y++; break;
	default:
		break;
	}
}
```