using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move_Player: MonoBehaviour
{
    // 캐릭터 이동 및 대쉬 관련 변수
    public float c_speed = 5f; //캐릭터 속도
    public float d_speed = 1.4f; //대쉬 속도
    private Vector3 moveDir; // 캐릭터 방향 벡터
    Rigidbody2D rigid;
    bool isDashButtonDown; //대쉬 판별 bool
    bool isHorizonMove;
    float moveX = 0f;
    float moveY = 0f;

    // 캐릭터 collider 처리 관련 함수 
    private SpriteRenderer spriteRenderer;


    private void Awake()
    {
        rigid = GetComponent<Rigidbody2D>();
        spriteRenderer = GetComponent<SpriteRenderer>();
    }

    private void Update()
    {
        // 단순 방향키 (360도 가능하게)

        bool hDown = Input.GetButtonDown("Horizontal"); //횡 버튼 누를때
        bool vDown = Input.GetButtonDown("Vertical");   //종 버튼 누를떄
        bool hUp = Input.GetButtonUp("Horizontal");     //횡 버튼 땔때
        bool vUp = Input.GetButtonUp("Vertical");       //종 버튼 땔때 

        if (Input.GetKey(KeyCode.W))
        {
            moveY = + 1f;
        }
        if (Input.GetKey(KeyCode.S))
        {
            moveY = -1f;
        }
        if (Input.GetKey(KeyCode.A))
        {
            moveX = -1f;
        }
        if (Input.GetKey(KeyCode.D))
        {
            moveX = +1f;
        }
        if (hDown || vUp)
            isHorizonMove = true; // 수평 이동 
        else if (vDown || hUp)
            isHorizonMove = false; // 수직 이동

        // 이동 방향


        // 대쉬 판정시 ->Fixed로
        if (Input.GetKeyDown(KeyCode.LeftShift)) // 향후 대쉬 조건식 넣어준다.
        {
            isDashButtonDown = true;
        }
    }


    private void FixedUpdate()
    {
        moveDir = isHorizonMove ? new Vector3(moveX, 0) : new Vector3(0, moveY);
        rigid.velocity = moveDir * c_speed; // 캐릭터 벡터
        moveX = 0; // 벡터값 초기화
        moveY = 0; // 벡터값 초기화

        if (isDashButtonDown) // 대쉬 작동
        {
            rigid.MovePosition(transform.position + moveDir * d_speed); // 대쉬 스피드 만큼 기존 position에 *
            isDashButtonDown = false; // 대쉬 판정 초기화
        }

    }

    // 캐릭터 적 충돌 이벤트
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("EnemyTag"))
        {
            Debug.Log("적 캐릭터와 부딫혔어요!!");
            StopCoroutine("OnHit");
            StartCoroutine("OnHit");
            Destroy(collision.gameObject);
        }
    }

    private IEnumerator OnHit()
    {
        spriteRenderer.color = Color.red;
        yield return new WaitForSeconds(1f);
        spriteRenderer.color = Color.white;
    }

    // 캐릭터가 단계별로 슬로우 가는것?

    private void Character_Slow()
    {

    }

}
