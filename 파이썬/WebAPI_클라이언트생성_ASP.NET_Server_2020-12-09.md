# Python Web Client _hellopython

1. NSwagStudio를 다운받는다 : [링크](https://github.com/RicoSuter/NSwag/wiki/NSwagStudio)
2. Rutime - Default로 설정
3. Web API via reflection - .NET Assembly Paths (...) 항목에 서버 "프로젝트명.dll"파일을 불러온다
4. Load Assemblies 버튼을 눌러 적용해준다
5. Generate Outputs 버튼을 눌러 서버 사양 정보를 출력한다
6. 출력한 사양 정보를 복사해, Swagger Editor에 접속해 붙여넣는다
7. Generate Client - Python을 선택해 다운받는다
8. 다운받은 파일 중 'docs'폴더와 'swagger_client'폴더를 복사해 원하는 파이썬 클라이언트 프로젝트에 넣는다
9. swagger_client폴더의 [configration.py](http://configration.py) 파일에 기본 경로를 지정해준다

```python
# Default Base url
self.host = "http://10.10.31.231/HelloWebApi"
```

```python
from __future__ import print_function
import time
import swagger_client
from swagger_client import Configuration
from swagger_client.rest import ApiException
from pprint import pprint

# create an instance of the API class
configuration = Configuration()
# configuration.
api_instance = swagger_client.AlbumsApi(swagger_client.ApiClient(configuration))
id = 1 # int |

try:
   api_response = api_instance.albums_get_album(1)
   pprint(api_response)
except ApiException as e:
   print("Exception when calling AlbumsApi->albums_delete_album: %s\n" % e)
```