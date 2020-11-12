# ORM(Object-Relational DB Mapping)

- 사물을 추상화시켜 이해하려는 객체지향적 사고방식과 DataModel을 정형화시켜 관리하려는 RDB사이를 연결하는 계층의 역할로 제시된 패러다임.
- RDB 모델을 객체지향의 Entity 형태로 투영시키는 방식을 의미한다.
- Entity Framework는 ORM의 기능을 하지만 정확히 ORM이라고 하기 어렵다. 그 이유는 다른 ORM과 다르게, Entity Framework를 사용하면 SQL 쿼리를 전혀 사용하지 않고 오로지 C# 만으로 데이터베이스를 관리하기 때문이다.

# Entity Framework 시작하기

- 프로젝트를 생성할 떄, 프로그램이 시작될 ```콘솔 앱```, 재사용 가능한 데이터를 보관할 ```클래스 라이브러리```, 추가로 테스트를 진행할 ```단위 테스트 프로젝트```를 만들어 준다. 이후 프로그램이 작동할 프로젝트를 Winform등의 다른 프로젝트로 만들 수 있다.
- 콘솔 앱 프로젝트에 ```새 항목```을 추가하는데, ```ADO.NET 엔티티 데이터 모델```을 선택하고, ```데이터베이스의 EF Designer```를 선택하여 생성해준다.
- 불러올 테이블을 선택할 때 ```sysdiagrams``` 테이블이 있는데, 이는 SSMS에서 사용하기 위해 생성한 지원 개체로 체크를 해제해준다.
- 추가로 '단수와 복수를 구분' 옵션을 체크해줬다.
- 우선 테이블을 잘 불러왔는지 확인하기 위해 코드를 작성해본다.

```csharp
// ChinookEntities -> Chinook 데이터베이스를 불러올 떄 생성된 엔티티의 기본 이름
// 추가로 클래스를 전혀 생성하지 않고 메인에서 작성한 코드이다
ChinookEntities context = new ChinookEntities();
int count = context.Albums.Count();
List<Album> albums = context.Albums.ToList();
Album album = context.Albums.Where(x => x.AlbumId == 1).FirstOrDefault();
var query = from x in context.Artists
	where x.ArtistId < 5
	select x.Name;
string[] names = query.ToArray();
```

- 코드를 보면, SQL문이 전혀 없고 메서드나 LINQ로 작업을 진행한다.
- 값을 확인하기 위해 콘솔로 출력하거나 단위테스트를 진행할 수도 있지만, 로그를 출력하도록 하면 작업 내용을 출력할 수 있다

```csharp
static void PrintLog(string sql)
{
	Console.WriteLine(sql);
}

// Action<string> System.Data.Entity.Database.Log
context.Database.Log = PrintLog;
```

```
2020-11-12 오후 4:06:41 +09:00
에서 열린 연결
SELECT
    [GroupBy1].[A1] AS [C1]
    FROM ( SELECT
        COUNT(1) AS [A1]
        FROM [dbo].[Album] AS [Extent1]
    )  AS [GroupBy1]

-- 2020-11-12 오후 4:06:41 +09:00
에서 실행 중
-- 2ms 후에 완료됨. 결과: SqlDataReader

2020-11-12 오후 4:06:41 +09:00
에서 끊어진 연결
```

- 이제 우리가 이전에 ADO.NET에서 사용한 방식대로 설계하기 위해 DB테이블을 Data프로젝트(클래스 라이브러리)에 추가하고, 이전처럼 DAO 클래스를 만들어주자

```csharp
class AlbumDao{
	internal AlbumDao() { }
	public int GetCount() {
		ChinookEntities context = new ChinookEntities();
		int count = context.Albums.Count();
		context.Dispose(); // 연결 해제
		return count;
}
```

- 지금으로도 메서드의 길이가 매우 줄어들지만, using문을 사용하면 조금 더 짧게 줄일 수 있다. using문으로 context를 생성하면 using문이 끝나면 자동으로 연결을 해제(Dispose)한다

```csharp
using (ChinookEntities context = new ChinookEntities())
{
	// Count
	return context.Albums.Count();
	// All
	return context.Albums.ToList();
	// Get by PK
	return context.Albums
	.Where(x => x.AlbumId == albumId)
	.FirstOrDefault();
	// Get MaxId
	var query = from x in context.Albums
	orderby x.AlbumId descending
	select x.AlbumId;
	return query.FirstOrDefault();
	// Get by ArtistId
	var query = from x in context.Albums
	where x.ArtistId == artistId
	select x;
	return query.ToList();
} // 종료시 Dispose
```

- Insert나 Update 등의 작업을 할 때는, context에 작업을 해준 뒤, SaveChanges() 메서드를 사용해 DB에 적용해줘야 한다.

```csharp
using(var context = new ChinookEntities())
{
	// Insert
	context.Albums.Add(album);
	// Update
	context.Entry(album).State = 
		System.Data.Entity.EntityState.Modified;
	// Delete
	context.Entry(album).State = 
		System.Data.Entity.EntityState.Deleted;
	// 변경사항 적용
	context.SaveChanges();
}
```