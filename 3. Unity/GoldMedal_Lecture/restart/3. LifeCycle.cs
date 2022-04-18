using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LifeCycle : MonoBehaviour
{

    //1. 초기화 영역 -> 물리 연산 -> 게임 로직 -> 해제
    //             활성화                    비활성화

    // 1. 초기화 영역

    // 게임 오브젝트가 장면안에 들어갔을때 최초한번만 제일 먼저 실행된다. 마치 생성자와 같은 역할?
    private void Awake()
    {
        Debug.Log("플레이어 데이터가 준비되었습니다.");
    }

    // Awake 보다는 느리게, Start 보다는 빠르게 실행되는 부분 ==> 활성화 영역
    private void OnEnable()
    {
        Debug.Log("플레이어 로그인");
    }

    // 업데이트 시작 직전 최초 실행
    private void Start()
    {
        Debug.Log("사냥 장비를 챙겼습니다.");
    }


    // 2. 물리 연산 영역

    // 물리 연산을 하기 전에 실행되는 함수
    private void FixedUpdate() // 고전된 주기로 실행 -> CPU 부하가 많다.
    {
        Debug.Log("이동");
    }


    // 3. 게임 로직 영역

    // 실행 주기가 떨어질 수 있다.
    private void Update()
    {
        Debug.Log("몬스터 사냥");
    }

    // 모든 업데이트 종료후 후처리
    private void LateUpdate()
    {
        Debug.Log("경험치 획득");
    }

    //비활성화 부분
    private void OnDisable()
    {
        Debug.Log("플레이어 로그아웃");
    }

    // 4. 해제 영역
    private void OnDestroy() //삭제될때
    {
        Debug.Log("플레이어 데이터를 해제하였습니다.");
    }



}
