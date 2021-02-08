# ADO.NET 시작하기

```csharp
// 연결 개체 생성
SqlConnection connection = new SqlConnection();
connection.ConnectionString = "server=localhost;database=Chinook;uid=sa;password=****";
```

- SqlConnection 클래스 : MSSQL 연결을 담당하는 클래스 개체
- ConnectionString : 연결에 필요한 정보가 들어있는 텍스트

```csharp
// 커맨드 개체를 생성
SqlCommand command = new SqlCommand();
command.Connection = connection;
// 기본 타입이 Text이기 때문에 Text타입을 쓰면 쓰지 않아도 된다.
command.CommandType = System.Data.CommandType.Text;
command.CommandText = "select count(*) from Album";
```

- SqlCommand 클래스 : MSSQL에 명령을 전달하기 위한 클래스 개체
- Connection : SqlCommand 개체 연결 정보를 전달
- CommandType : 명령 전달 방식
- CommandText : 전달할 명령이 들어있는 텍스트

```csharp
// 연결
connection.Open();
// 커맨드 개체를 실행, 쿼리문의 결과값을 가져온다
int count = (int)command.ExecuteScalar();
// 열결 해제
connection.Close();
```

- Open() : 데이터베이스와 연결한다
- 커맨드의 실행은 결과값에 따라 다른 메서드를 사용한다.
- Close() : 데이터베이스와 연결을 끊는다. 가비지 컬렉터와 상관없기 때문에 꼭 닫아줘야 한다.

# Data Access Object

- 위에서 작업한 일련의 작업을 하나의 클래스로 바꾸고, 메인에서는 해당 클래스의 개체를 생성하여 사용해보자
- 데이터베이스에 대한 작업들을 하나의 클래스로 정리한다. DAO에는 작업들을 의미하는 메서드가 존재한다.

```csharp
// ----- AlbumDao 클래스 GetCount 메서드 -----
public int GetCount()
{
	// SqlConnection connection = ...
	command.CommandType = System.Data.CommandType.StoredProcedure;
	command.CommandText = "Album_count";
	int count = (int)command.ExecuteScalar();
	connection.Close();
	return count;
}
public void Insert(...) { }
public void Update(...) { }
// ...

// ----- Unit Test - GetCountTest -----
AlbumDao albumDao = new AlbumDao();
int count = albumDao.GetCount();
Assert.IsTrue(count > 0);
```

- 나중에는 여러 테이블의 Dao를 하나의 static 클래스로 묶어서 사용하면 편리하다

```csharp
// static 클래스는 static 맴버만 사용하겠다는 제약이다
public static class Dao
{
	static Dao()
	{
		Album = new AlbumDao();
		Track = new TrackDao();
	}
	public static AlbumDao Album { get; }
	public static TrackDao Track { get; }
}
// 실제 사용 시
Dao.Album.GetByPK(1);
```

# Data Transfer Object

- 다른 말로는 Entity, Value Object 라고도 부른다.
- 데이터베이스의 테이블을 클래스 단위로 그대로 가져오는 것을 의미하며, 클래스 안에는 테이블의 요소 개체가 필드(프로퍼티)로 존재한다.

```csharp
public class Album
{
	public int AlbumId { get; set; }
	public string Name { get; set; }
	public int ArtistId { get; set; }
	public override string ToString() { return $"{AlbumId}\t{ArtistId}\t{Name}"; }
}
```

- DTO는 테이블의 값을 프로그램 내의 개체처럼 사용하기 위해 사용한다.

```csharp
// AlbumDao 클래스 GetAll 메서드
public List<Album> GetAll()
{
	// connection
	command.CommandText = "select AlbumId, Name, ArtistId from Album";
	List<Album> list = new List<Album>();
	SqlDataReader reader = command.ExecuteReader();
	while(reader.Read())
	{
		Album album = new Album();
		album.AlbumId = reader.GetInt32(0); // (int)reader["AlbumId"];
		album.Name = reader.GetString(1); // (string)reader[1];
		album.ArtistId = reader.GetInt32(0);

		list.Add(album);
	}
	reader.Close();
	connection.Close();
}

// ----- Unit Test - GetAllTest -----
AlbumDao dao = new AlbumDao();
List<Album> list = dao.GetAll();
Assert.IsTrue(list.Count > 0);
```

# SqlCommand

## CommandType

- Text와 StoredProcedure가 대표적이고, 기본값은 Text이다.
- Text 방식은 쿼리문을 직접 입력해 사용하는 방식이다.
- StoredProcedure 방식은 데이터베이스에 저장된 프로시저의 이름을 입력해 프로시저를 사용하는 방식이다.

```csharp
command.CommandType = System.Data.CommandType.Text;
command.CommandText = "select count(*) from Album";

command.CommandType = System.Data.CommandType.StoredProcedure;
command.CommandText = "Album_count";
```

## Command 입력

- 데이터베이스 연결 후 Command를 이용한 동작을 의미한다.
- Command에 동작이 되도록 하려면, 동작을 CommandText에 입력한다. 추가로 쿼리문에 파라미터가 필요할 경우, AddWithValue() 메서드를 사용해 추가한다.

```csharp
command.CommandText = 
	"select AlbumId, Name, ArtistId from Album where AlbumId = @AlbumId";
command.Parameters.AddWithValue("@AlbumId", albumId);
```

## Command 동작

- 동작의 결과로 인해 반환되는 반환값에 따라 종류가 나뉜다.
- ExecuteScalar : 쿼리문의 결과가 단 하나의 값일 경우 사용한다. 반환값은 object형이기 때문에, 저장하기 위해서 형변환을 해줘야 한다
- ExecuteReader : 쿼리문의 결과가 컬럼 단위로 올 경우 사용한다. 반환값은 SqlDataReader타입으로 오게 되는데, SqlDataReader타입으로 받은 값을 Read() 메서드를 사용하여 한 줄씩 읽어 원하는 형태로 저장하는 방식으로 값을 가져온다.
- ExecuteNonQuery : 결과가 반환되지 않는 Select문 이외의 쿼리문을 실행할 때 사용한다. 반환값으로는 쿼리문에 영향을 받은 행의 수를 반환한다.

```csharp
// ExecuteScalar 예제
command.CommandText = "select count(*) from Album";
int count = (int)command.ExecuteScalar();

// SqlDataReader 예제
command.CommandText = "select AlbumId, Name, ArtistId from Album";
SqlDataReader reader = command.ExecuteReader();
while(reader.Read())
{
	Album album = new Album();
	album.AlbumId = reader.GetInt32(0); // (int)reader["AlbumId"];
	album.Name = reader.GetString(1); // (string)reader[1];
	album.ArtistId = reader.GetInt32(0);

	list.Add(album);
}

// ExecuteNonQuery 예제
command.CommandText = "insert into Album values (@Name, @ArtistId)";
command.Parameters.AddWithValue("@Name", entity.Name);
command.Parameters.AddWithValue("@ArtistId", entity.ArtistId);
command.ExecuteNonQuery();
```