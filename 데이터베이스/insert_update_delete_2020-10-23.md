# INSERT 구문

```sql
-- INSERT INTO [테이블] ([입력할 열]) VALUES([들어갈 값])
insert into PlaylistTrack values(18, 3290)
insert into PlaylistTrack (PlaylistId, TrackId) values(18, 3290)
```

- 기본적인 INSERT문, 테이블에 값을 추가하는 구문이다
- 값을 추가할 열을 지정하지 않으면, 순차적으로 값을 추가한다
- 입력할 열로 선택되지 않은 열이 null허용이 아니라면 에러가 난다

```sql
insert into Artist values(276, 'BTS') -- (ArtistId, Name), 에러
insert into Artist values('BTS') -- ArtistId는 자동 입력, Name만 입력됨
insert into Album values('BTS 1집', 276) -- AlbumId는 자동 입력, Name, ArtistId만 입력
```

- 테이블의 Key값에 AUTOINCREMENT 또는 IDENTITY(자동 증가값 부여)가 있을 경우, insert로 값을 입력하면 에러가 난다

# DELETE 구문

```sql
-- DELETE [테이블] WHERE [조건]
delete Album
delete Album where AlbumId = 348
```

- 기본적인 DELETE문, 테이블의 값을 제거하는 구문이다
- 첫번째처럼 아무 조건 없이 입력하면 테이블의 모든 값이 삭제되고, 복구가 되지 않으니 주의해야 한다
- 특정 내용의 값을 삭제하고 싶을때는 WHERE로 조건을 주면 된다

```sql
delete Album where Title like '%1집%'
```

- ```like '%1집%'```은 앞에 값이 0개이상 있고 뒤에도 값이 0개 이상 있는, '1집'이라는 값이 포함된 값을 의미한다.
- 앞에 %를 지우면 "1집으로 시작하는 값"이 되고 뒤에 %를 지우면 '1집으로 끝나는 값'이 된다

```sql
drop table Album
```

- 테이블 자체를 삭제하거나 데이터베이스 자체를 삭제하려고 할 떄는, DROP 구문을 사용한다. 이 역시 복구가 되지 않으니 주의하자.

# UPDATE 구문

```sql
-- UPDATE [테이블] SET [바꿀 값] WHERE [조건]
update Album set Title = '2집', ArtistId = 1
update Album set Title = '2집', ArtistId = 1 where AlbumId = 350
```

- 기본적인 UPDATE문, 테이블의 값을 변경하는 구문이다
- 첫번째처럼 아무 조건 없이 입력하면 테이블의 모든 값이 변경되고, 복구가 되지 않으니 주의해야 한다.
- 특정 내용의 값을 변경할 때는, WHERE로 조건을 주면 된다

# 동적 SQL

- 동적 SQL이란, 문자열을 저장해 조합하여 문자열 형태의 SQL문장을 실행시키는 것을 의미한다
- 프로그램이 실행중일 떄 쿼리를 조합하여 사용해야 하는 경우가 생길 떄 사용한다
- 사용법은, 다른 프로그래밍 언어처럼 변수를 선언해 여러 방법으로 문자열을 조합하고, 이를 EXEC로 실행한다

```sql
select * from Album where ArtistId < 5 and AlbumId > 8
-- 위와 아래는 같다 --
declare @sql nvarchar(1000) -- char sql[1000]

set @sql = 'select * from Album ' -- sql = "select * from Album "

if 1 = 1 -- if(True)
begin -- {
	set @sql = @sql + 'where ArtistId < '
	set @sql = @sql + '5'
end -- }

if 1 = 1
begin
	set @sql = @sql + 'and AlbumId > '
	set @sql = @sql + '8'
end

exec(@sql)
```