using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lifecycle : MonoBehaviour
{
    void Awake() // Awake 함수는 시작할때 한번만 실행되는 것이 특징이다.
    {
        Debug.Log("풀레이어 데이터가 준비되었습니다.");
    }

    private void OnEnable() // 게임 오브젝트가 활성화 되었을때
    {
        Debug.Log("플레이어 로그인");

    }

    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("사냥장비를 챙겼습니다");
    }

    private void FixedUpdate() // 물리연산을 하기전에 하는 Update하는 함수
    {
        //고정된 주기로 CPU를 사용함.
        Debug.Log("이동한다."); // 계속 실행하고 있다. 
    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log("몬스터사냥");
    }


    void LateUpdate() // 모든 업데이트가 끝난 뒤에 실행이 된다.
    {
        Debug.Log("경험치 획득 ");
    }

    private void OnDisable()
    {
        Debug.Log("풀레이어 로그아웃.");

    }

    private void OnDestroy() // 오브젝트가 삭제될때 사용된다
    {
        Debug.Log("풀레이어 데이터가 해제되었습니다.");

    }
}
