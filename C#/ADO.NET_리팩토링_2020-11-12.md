# ADO.NET 리팩토링(Refactoring)

## 1. DAO 클래스 외부 접근 제한

- 각 Dao 클래스를 외부에서 접근하지 못하도록 프로젝트 내 사용 가능한 접근자 internal을 사용해주자.

```csharp
public class AlbumDao
{
	internal AlbumDao() { } // 외부에서 접근하지 못하도록 하기 위해
}

// 실제 사용 시
AlbumDao dao = new AlbumDao(); // error - 접근못함
Dao.Album.GetByPK(1);
```

## 2. DAO 클래스 중복 정리

- SqlConnection 개체를 생성하고 연결을 진행하는 부분을 메서드로 통일한다

```csharp
private SqlConnection CreateConnection()
{
	SqlConnection connection = new SqlConnection();
	connection.ConnectionString = "server=10.10.16.150;database=Chinook;uid=sa;Password=3512";
	connection.Open();
	return connection;
}
// ...
SqlCommand command = new SqlCommand();
command.Connection = CreateConnection();
// ...
command.Connection.Close();
```

- SqlCommand 개체를 생성하는 부분도 메서드로 통일한다

```csharp
private SqlCommand CreateCommand()
{
	SqlCommand command = new SqlCommand();
	command.Connection = CreateConnection();
	return command;
}
// ...
SqlCommand command = CreateCommand();
```

- ExecuteReader 메서드를 통해 받은 데이터를 읽는 부분도 정리가 가능하다

```csharp
private Album ReadEntity(SqlDataReader reader)
{
	Album album = new Album();
	album.AlbumId = reader.GetInt32(0);
	album.Name = reader.GetString(1);
	album.ArtistId = reader.GetInt32(2);
	return album;
}
// ...
while(reader.Read())
	list.Add(ReadEntity(reader));
```

## 3. DAO 부모 클래스 생성

- 여러 테이블의 Dao클래스를 만들다보면, 중복된 내용의 메서드가 생기게 된다. 그렇다면 중복된 메서드를 부모 클래스로 합치면 어떨까?
- AlbumDao 클래스의 부모 클래스가 될 BaseDao 추상 클래스를 만들고 GetCount를 상속 메서드로 바꿔보자

```csharp
public abstract class BaseDao{
	protected SqlCommand CreateCommand(){}
	protected SqlConnection CreateConnection(){}
	public int GetCount(){
		// ...
		command.CommandText = QueryForGetCount;
	}
	protected abstract string QueryForGetCount {get;}
}

public class AlbumDao : BaseDao{
	protected override string QueryForGetCount => "select count(*) from Album";
}
```

- GetAll 메서드도 상속 메서드로 바꿔보자
- GetAll 메서드는 DTO 클래스를 받아서 사용하기 때문에, 어떤 DTO 클래스든 받아서 사용할 수 있도록 일반화(generic)가 필요하다

```csharp
// BaseDao 클래스를 제네릭 클래스로 바꿔준다
public abstract class BaseDao<T>{
public List<T> GetAll(){
	// ...
	command.CommandText = QueryForGetAll;
	// ...
	List<T> list = new List<T>();
	// ...
	T album = ReadEntity(reader);
	// ...
}
protected abstract string QueryForGetAll { get; }
protected abstract T ReadEntity(SqlDataReader reader);

public class AlbumDao : BaseDao<T>{
	protected override string QueryForGetAll =>
		"select AlbumId, Name, ArtistId, from Album";
	protected override Album ReadEntity(SqlDataReader reader){}
}
```

- Insert나 Update는 기본적인 행동이기 때문에 올릴 수 있을 것 같지만, 테이블에 따라 설정해야 하는 내용이 달라서 올리는 것이 효율이 떨어질 것 같다. 그런 경우에는 추상함수로만 묶어둔다.

```csharp
public abstract void Insert(T entity);
public abstract void Update(T entity);
```

## 4. DAO의 부모 클래스 생성2

- Dao클래스에서 만들었던 메서드 중에 기본 키를 이용해 작동하는 GetByKey, DeleteByKey등의 메서드가 있다. 기본키라는 요소가 어떤 타입으로 올지 모르기도 하고, 개수가 1개라는 보장도 없기 때문에 BaseDao 클래스에 올리기 어렵다.
- 그래서, 중간에서 이 값을 치환해주기 위해 다른 클래스를 만들어 BaseDao와 개별 Dao클래스 사이에 상속해준다

```csharp
// 기본 키가 1개인 테이블에 대한 클래스. T를 클래스로 한정한다.
// 기본 키가 2개인 테이블에 대한 클래스는 DuelKeyDao<T, K1, K2> 처럼 생성해준다
public abstract class SingleKeyDao<T, K> : BaseDao<T> where T:class
{
	public abstract string SqlForGetByPK { get; }
	public T GetByPK(K key)
	{
	//...
	// 통일성을 위해 파라미터를 Key로 바꿔주자
	command.Parameters.AddWithValue("@Key", key);
	T entity = null;
	//...
	}
}
```

- Dao클래스가 상속받는 부모 클래스를 바꿔주자.

```csharp
public class AlbumDao : SingleKeyDao<Album, int>{
	protected override string SqlForGetByPK => "select AlbumId, Name, ArtistId from Album where AlbumId = @Key";
```