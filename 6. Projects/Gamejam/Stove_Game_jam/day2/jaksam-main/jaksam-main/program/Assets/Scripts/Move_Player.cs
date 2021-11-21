using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move_Player: MonoBehaviour // 플레이어 컨트롤 
{
    public GameObject dashEffect;
    FoodObject foodobject;
    // 캐릭터 이동 및 대쉬 관련 변수
    public float c_speed = 5f; //캐릭터 속도
    public float d_speed = 1.4f; //대쉬 속도
    private Vector3 moveDir; // 캐릭터 방향 벡터
    Rigidbody2D rigid;
    bool isDashButtonDown; //대쉬 판별 bool
    float moveX = 0f;
    float moveY = 0f;

    // 캐릭터 collider 처리 관련 함수 
    private SpriteRenderer spriteRenderer;
    Vector3 oldDir = Vector3.zero;

    Animator animator;

    public float dashCoolTime = 0.0f;
    public float dashMax = 3.0f;


    float healTime = 0.0f;
    public GameObject healobject;
    public void SetHeal()
    {
        healTime = 0.5f;
        healobject.SetActive(true);
        healobject.transform.localScale = Vector3.one;
        healobject.transform.localPosition = new Vector3(0, 0.5f);
    }

    private void Awake()
    {
        rigid = GetComponent<Rigidbody2D>();
        spriteRenderer = GetComponent<SpriteRenderer>();
        dashEffect.SetActive(false);
        TryGetComponent<Animator>(out animator);
        Fat(125);
    }

    public void Fat(int f)
    {
        animator.SetInteger("Fat", f);
    }

    private void Update()
    {
        if(healTime > 0)
        {
            healTime -= Time.deltaTime;
            healobject.transform.localScale = Vector3.Lerp(healobject.transform.localScale,Vector3.zero, Time.deltaTime);
            healobject.transform.localPosition += Vector3.up * Time.deltaTime;

            if (healTime < 0)
            {
                healobject.SetActive(false);
            }
        }


        moveX = Input.GetAxisRaw("Horizontal");
        moveY = Input.GetAxisRaw("Vertical");

        // 이동 방향
        moveDir = new Vector3(moveX, moveY).normalized;

        if (oldDir != Vector3.zero && moveDir == Vector3.zero)
        {
            animator.SetFloat("OldX", oldDir.x);
            animator.SetFloat("OldY", oldDir.y);
            oldDir = Vector3.zero;
        }
        else
            oldDir = moveDir;

        animator.SetFloat("PositionX", moveDir.x);
        animator.SetFloat("PositionY", moveDir.y);

        if (dashCoolTime >= 0)
            dashCoolTime -= Time.deltaTime;


        // 대쉬 판정시 ->Fixed로
        if (dashCoolTime <= 0 && Input.GetKeyDown(KeyCode.LeftShift))                     // 향후 대쉬 조건식 넣어준다.
        {
            //isDashButtonDown = true;
            dashCoolTime = dashMax;

            StartCoroutine("Dash");
        }

    }

    IEnumerator Dash()
    {


        for (int i = 0; i < 10; i++)
        {
            rigid.MovePosition(transform.position + moveDir * (d_speed /3 ));

            if(i % 3 == 0)
            {
                GameObject DashEffectIns = Instantiate(dashEffect, transform.position, Quaternion.identity);
                // DashEffectIns.transform.LookAt(this.transform);

                var rot = moveDir;
                var angle = Mathf.Atan2(rot.y, rot.x) * Mathf.Rad2Deg;

                DashEffectIns.transform.rotation = Quaternion.Euler(0, 0, angle+180);
                


                DashEffectIns.SetActive(true);
            }


            yield return new WaitForSeconds(0.05f);
        }
    }


    private void FixedUpdate()
    {
        rigid.velocity = moveDir * c_speed;                            // 캐릭터 벡터
        moveX = 0;                                                      // 벡터값 초기화
        moveY = 0;                                                      // 벡터값 초기화

        if (isDashButtonDown)                                           // 대쉬 작동
        {
            //dashEffect.SetActive(true);
            rigid.MovePosition(transform.position + moveDir * d_speed); // 대쉬 스피드 만큼 기존 position에 *

            GameObject DashEffectIns = Instantiate(dashEffect, transform.position, Quaternion.identity);
            DashEffectIns.transform.LookAt(this.transform);
            // Destroy(DashEffectIns, 0.08f);

            isDashButtonDown = false;                                   // 대쉬 판정 초기화
        }

    }

    // 캐릭터 적 충돌 이벤트
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "EnemyTag") // 정크푸드와 충돌
        {
            //데미지 처리
            spriteRenderer.color = new Color(1, 0, 0, 0.5f);
            gameObject.layer = 8;                                       // 무적상태 // playerDamaged layer로 
            Invoke("OnDamaged", 0.5f);                                  // OnDamaged 로 넘아간다 // 무적시간 0.5초

            //정크푸드 먹었을때 비만 게이지  증가하게
            c_speed = 2f;
            Invoke("SpeedReturn", 0.5f);
            GameManager.gm.SetGuage(10); // 변수값 따로 아이템에서 불러오기
        }
        
        if(collision.gameObject.tag =="Ally")                            // 헬스 푸드 충돌
        {
            c_speed = 7f;
            Invoke("SpeedReturn", 0.5f);
            GameManager.gm.SetGuage(-10); // 변수값 따로 아이템에서 불러오기
        }
    }



    void OnDamaged() // 데미지 처리 받고 다시 돌어감
    {
        spriteRenderer.color = new Color(1, 1, 1, 1);
        gameObject.layer = 7; // 무적상태해제 => 다시 player layer로 
    }

    void SpeedReturn() //음식 먹고 원래 속도로 다시 돌아옴
    {
        c_speed = 5f;
    }

    


}
