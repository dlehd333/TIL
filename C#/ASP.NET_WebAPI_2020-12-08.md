# SDK vs API

- Software Development Kit : 함수, 에뮬레이터, 개발 문서, 개발 도구 등을 하나로 묶은 것
- Application Programming Interface : 함수 라이브러리. 다른 시스템, 디바이스에서 작용하기 위해 사용한다. API는 함수 또는 객체지향 언어로 제공된다.

# WebAPI

- WebAPI 이전에는 통신 프로토콜, 포트 오픈의 위험성 등 어려운 요소가 있었다.
- 이런 문제점들을 해결하고 모든 디바이스, 모든 시스템에서 사용할 수 있는 통신수단으로 지정한 것이 Web이다.
- WebAPI는 두 시스템 간에 통신을 위한 방법이다. 통신에 사용되는 수단으로 Web에서 사용되던 HTTP 프로토콜을 사용한다.
- 데이터 전달을 위해 '직렬화'가 사용되고, 직렬화에 대표적으로 XML/JSON이 사용된다.

# ASP.NET 시작하기

- Visual Studio Installer를 통해, "ASP.NET 및 웹 개발" 항목을 설치한다
- "ASP.NET 웹 애플리케이션(.NET Framework)"으로 프로젝트를 생성한다
- "새 ASP.NET 웹 애플리케이션 만들기"에서 "Web API"를 선택하고, ```HTTPS에 대한 구성```을 해제해준다. 해당 옵션을 사용하려면 포트에 대한 상용 인증서가 필요하다.
- 프로젝트를 생성하면 웹 페이지 및 웹 API에 필요한 여러 스크립트 및 데이터들이 생성된 상태로 프로젝트가 생성된다. 그대로 실행해보면 웹 사이트 형태로 기본 ASP.NET 페이지가 생성된다.
- App_Start의 WebApiConfig파일에 가면 기본 경로가 나온다. 이 경로는 바꿀일이 거의 없다

```csharp
routeTemplate: "api/{controller}/{id}"
```

- Controllers로 가면, HomeController와 ValuesController가 있다. ValuesController에서 Values가 컨트롤러의 이름이며, 해당 컨트롤러의 이름으로 경로를 입력하면 해당 경로의 대한 XML데이터를 확인할 수 있다.

```csharp
localhost:1234/api/values
localhost:1234/api/values/1 -> api의 values컨트롤의 id가 1인곳
```

- 컨트롤러는 Controllers 폴더에서 우클릭 후 "추가 - 컨트롤러"로 추가한다
- 기본적으로 "API를 사용하기 위해서는 Web API 2 컨트롤러 - 비어있음" 또는 "읽기/쓰기 동작이 포함된 Web API 2 컨트롤러"를 사용한다

# HTTP Method

- GET(read) : 일반적인 URL 요청. 리소스를 조회하고 자세한 정보를 가져온다.
- POST(insert) : 일반적인 요청과 함께 입력된 정보가 함께 전달됨. 리소스를 생성하는 역할을 한다. HTTP의 Body(크롬으로 확인 시 Header의 Form Data)에 입력된 정보가 들어간다.
- PUT(update) : 리소스를 수정한다
- DELETE(delete) : 리소스를 삭제한다
- 실제 HTTP에는 더 많은 메서드가 존재한다.
- Controller에도 Get, Post, Put, Delete의 메서드를 사용한다. 물론 이름을 바꾸어 사용해도 되지만 권장되지 않는다. 이런 사항을 convention rule이라고 부른다.

# 직렬화/역직렬화

- 리소스를 전달하기 위해서는 직렬화가 필요하다.
- 직렬화란, 개체로 저장되어 있는 데이터를 텍스트로 만들어 구분자로 나열하는 것이다. 구분자로 나뉘어진 데이터들 각각은 token이라고 부른다.

```csharp
// 이게 직렬화
string text = $"{album.AlbumId}\t{album.Name}\t{album.ArtistId}";
// 이건 저장
File.WriteAllText("1.txt", text);
```

- 역직렬화는 반대로 직렬화한 텍스트를 token 단위로 분해하여 개체로 저장하는 것이다

```csharp
// 이건 불러오기
string text = File.ReadAllText("1.txt");
// 이게 역직렬화
string[] tokens = text.Split('\t');
Album album = new Album();
album.AlbumId = int.Parse(tokens[0]);
album.Name = tokens[1];
album.ArtistId = int.Parse(tokens[2]);
```

- 구조가 단순하고 리소스의 양이 적을 경우 위 처럼 만들면 되지만, 복잡한 구조나 다량의 리소스를 수동으로 직렬화하여 저장하는 것은 쉽지 않다.
- 그래서 VS에서 사용하는 대표적인 라이브러리가 JSON을 사용한 "Newtonsoft.Json"라이브러리이다. 아래는 위의 코드를 라이브러리에 맞게 수정한 것이다.

```csharp
// 직렬화
string json = JsonConvert.SerializeObject(album);
File.WriteAllText("1.txt", json);

// 역직렬화
string json = File.ReadAllText("1.txt");
Album album = JsonConvert.DeserializeObject<Album>(json);
```

- 만일 클래스의 필드 중에 직렬화 하고 싶지  않은 필드가 있다면, 어트리뷰트로 개별로 제어가 가능하다.

```csharp
[JsonObject(MemberSerialization.OptIn)]
// Fields - 
// OptIn - JsonProperty 어트리뷰트가 붙은 필드만 직렬화한다
// OptOut - JsonProperty 어트리뷰트가 붙은 필드만 제외하고 직렬화한다
public class Album
{
	[JsonProperty]
	public int AlbumId{ get; set; }
	// ...
	public string NameAndArtist{ get { return Name + ArtistId; } }
}
```

- 하지만, EntityFramework처럼 생성된 Entity 클래스를 고칠 수 없는 상황이라면 .NET의 '버디 클래스'(메타 데이터 클래스) 를 이용한다.

```csharp
// 참조 추가 - 어셈블리 - System.ComponentModel.DataAnnotations
// 해당 클래스의 메타 데이터 클래스 지정
[MetaDataType(typeof(AlbumMetaData))]
[JsonObject(MemberSerialization.OptIn)]
public partial class Album
{
	// ...
}

public class AlbumMetaData
{
	[JsonProperty]
	public int AlbumId{ get; set; }
	// ...
}
```

# Entity Framework의 사용

- 프로젝트에 Entity Framework로 데이터베이스를 불러오고, 빌드해준다
- 컨트롤러를 생성하는데, "Entity Framework를 사용하며 동작이 포함된 Web API 2 컨트롤러"를 선택한다
- 모델 클래스(테이블) 및 컨텍스트 클래스(Entities)를 추가하고, 이름을 설정해주면 생성된다
- 생성된 컨트롤러에서 메서드의 이름을 변경하거나 내용을 수정해도 되지만, 인자로 받아들이는 'id'값을 변경하면 안된다. 기본 주소로 설정된 이름이기 때문이다.
- 실제 ASP.NET에서 직렬화를 진행하고 실행하면, 오류가 발생하는데 이는 데이터가 실제 엔티티가 아닌 프록시 인스턴스로 반환하기 때문이다.
- 지금은 프록시를 필요로 하지 않기 때문에 컨트롤러의 생성자 단에서 해당 옵션을 해제해주면 정상적으로 직렬화된 Entity 데이터가 전달된다.

```csharp
_context.Configuration.ProxyCreationEnabled = false;
```

# GET 이외의 메서드 테스트

- GET 메서드는 프로젝트를 실행하고, 브라우저 상에서 경로를 입력하면 테스트가 가능하다.
- 하지만, 다른 메서드를 테스트하기 위해서는 다른 클라이언트 도구가 필요하다.
- 여기서는 Postman이라는 도구를 사용한다. 회원 가입하고 설치해준다.
- + 를 눌러 Request를 추가해주고, 메서드와 URL(URI)을 입력하여 테스트할 수 있다.

```csharp
< 테스트 방법 >
Method : POST - URL : api/Albums - Body_x-www-form-urlencoded : 입력값
Method : PUT - URL : api/Album/350 - Body_x-www-form-urlencoded : 수정값
Method : DELETE - URL : api/Album/349 (GET과 동일)

< Body_x-www-form-urlencoded 입력예시 >
AlbumId:350
Name:ABC
ArtistId:3
```

# 클라이언트 프로젝트

## **※ 서버가 웹에 게시되어야 실행이 가능하다 ※**

- 우리는 아래와 같은 코드가 작동하도록 하는 클라이언트 콘솔 프로젝트를 만들고 싶다. 하지만 저 4줄 만으로는 부족한 부분이 너무 많다.

```csharp
// example code
WebApi api = new WebApi("http://localhost:54581/api/albums");
Album album = api.Get(1);
album.ArtistId = 5;
api.Update(album);
```

- 그래서 C# WebAPI 클라이언트를 생성해주는 도구인 NSwagStudio을 사용하여 간단한 웹 클라이언트를 만들어보자
1. NSwagStudio를 다운받는다 : [Github](https://github.com/RicoSuter/NSwag/wiki/NSwagStudio)
2. Rutime - Default로 설정
3. Web API via reflection - .NET Assembly Paths (...) 항목에 "프로젝트명.dll"파일을 불러온다
4. Load Assemblies 버튼을 눌러 적용해준다
5. 우측의 Output에서 "CSharp Client"를 체크하고 CSharp Client 메뉴의 Settings에서 namespace를 변경해준다.
6. Generate Outputs를 눌러 API 사양과 C# 코드를 생성한다
7. C# 코드를 복사하여 해당 코드로 생성된 클래스 파일을 추가해준다

```csharp
// 첫번째 인자로 입력된 url이 "BaseUrl"이다
AlbumsClient api = new AlbumsClient("http://localhost:54581/",
	new System.Net.Http.HttpClient());
// -------------------------------------------------------------------------------
// 생성된 클라이언트는 기본적으로 비동기를 사용한다. 값을 받기 위해 Result를 사용했다
Album album = api.GetAlbumAsync(1).Result; // GET
album.ArtistId = 2;
// 리턴값이 없거나, 리턴값을 사용하지 않으려는 비동기 메서드의 경우 Wait()메서드를 사용해준다
api.PutAlbumAsync(1, album).Wait(); // PUT
// -------------------------------------------------------------------------------
// 앨범 테이블에 값을 추가한다
Album album new Album();
album.Name = DateTime.Now.ToString();
album.ArtistId = 1;
// 리턴값은 추가한 데이터. 재사용을 위해 리턴값을 받는다
album = api.PostAlbumAsync(album).Result; // POST
// 해당 앨범 데이터의 이름(Name)을 수정한다
album.Name = DateTime.Now.ToString();
api.PutAlbumAsync(album.AlbumId, album).Wait(); // PUT
// 해당 앨범 데이터를 삭제한다
api.DeleteAlbumAsync(album.AlbumId).Wait(); // DELETE
```