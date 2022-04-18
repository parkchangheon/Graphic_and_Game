using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LifeCycle : MonoBehaviour
{

    /*    //1. 초기화 영역 -> 물리 연산 -> 게임 로직 -> 해제
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
        }*/



    //=============================B6 강의 ===============================

    //입력은 3가지로 구성되어있는데, down, stay, up 으로 구성되어 있다.

    /*    private void Update()
        {
            //input은 게임 내 입력을 모두 관장한다.
            if (Input.anyKeyDown)  //프러퍼티
                Debug.Log("플레이어가 아무키를 눌렀습니다.");

            *//*if (Input.anyKey)  //누를때마다 계속.
                Debug.Log("키를 누르고 있습니다.");*//*

            if (Input.GetKeyDown(KeyCode.Return))  //Enter가 Return이다.
                Debug.Log("아이템을 구매하였습니다.");

            if (Input.GetKeyDown(KeyCode.LeftArrow))
                Debug.Log("왼쪽방향키를 눌렀습니다.");

            if (Input.GetKeyDown(KeyCode.RightArrow))
                Debug.Log("오른쪽 방향키를 눌렀습니다.");

            if (Input.GetKeyUp(KeyCode.RightArrow))
                Debug.Log("오른쪽 방향키를 뗏습니다.");


            // 0은 마우스 왼쪽 버튼, 1은 오른쪽 버튼
            if (Input.GetMouseButtonDown(0))
                Debug.Log("미사일 발사");

            if (Input.GetMouseButton(0))
                Debug.Log("미사일 모으는 중!!");

            if (Input.GetMouseButtonUp(0))
                Debug.Log("슈퍼미사일 발사!!");
        }*/




    //==========axis 활용============
    /*    private void Update()
        {
            if (Input.GetButtonDown("Jump"))
                Debug.Log("점프");

            if(Input.GetButton("Horizontal"))
            {
                Debug.Log("횡 이동 중" + Input.GetAxis("Horizontal"));

                //Debug.Log("횡 이동 중" + Input.GetAxisRaw("Horizontal")); => -1, 1, 0 세개만 표시
            }

            if(Input.GetButton("Vertical"))
            {
                Debug.Log("종 이동 중" + Input.GetAxisRaw("Vertical"));
            }


        }*/





    //========실제 이동================

    private void Start()
    {
        int number = 4; //스칼라 (값)
        //Vector3 vec = new Vector3(5, 0, 0); //벡터값(방향까지)
        //transform.Translate(vec);  //위치에 더해준다.
    }

    private void Update()
    {
        Vector3 vec = new Vector3(
            Input.GetAxisRaw("Horizontal"),
            Input.GetAxisRaw("Vertical"),
            0);
        transform.Translate(vec);
    }

}
