----히어독 수정 내용----
1. 임시파일에 내용 안담기는 문제 수정 
	- O_WRONLY 플래그 추가

2. $USER 입력 시 세그폴트 수정
	- expanded_str -> str

3. 히어독 내에서 readline 2번 이상 호출 시 배열에 데이터 안담기는 문제 수정
	- i 값 초기화

4. 히어독 메모리 릭 수정
	- strjoin 함수 수정
		- src1, src2 둘중에 널이 들어 올 경우 메모리 해제 코드 추가



----수정 내용 라인------
1. free_parser.c : 24 (라인)
2. free_parser.c : 47
3. free_parser.c : 43
4. main.c : 109 ~ 119


----할말-----------------
strjoin을 free_strjoin/source_free_strjoin 으로 바꾸는 것이 좋아보임.

현재 strjoin은 malloc 할당한 스트링만 넣어야 하는 구조라서,
스택/데이터 공간에 할당된 스트링을 넣을 경우, 에러 발생함.

함수 외부에서는 "strjoin이 소스 스트링을 해제 한다는 것" 을 전혀 알 수 없음.
따라서 함수 외부에 해당 내용을 알 릴 필요가 있음.

