using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAction : MonoBehaviour
{
    float h;
    float v;
    [SerializeField] public float Speed;
    bool isHorizonMove;
    Rigidbody2D rigid;
    Animator anim;

    void Awake()
    {
        rigid = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
    }

    void Update()
    {
        h = Input.GetAxisRaw("Horizontal");
        v = Input.GetAxisRaw("Vertical");

        bool hDown = Input.GetButtonDown("Horizontal"); //수평방향 눌렀을 때 
        bool vDown = Input.GetButtonDown("Vertical");   //수직방향 눌렀을 때
        bool hUp = Input.GetButtonUp("Horizontal");     //수평방향 떼었을 때 이제는 수평 방향 
        bool vUp = Input.GetButtonUp("Vertical");       //수직방향 떼었을 때

        //눌렀다 뗏다 할때 위 좌 키 누르고 렉걸리는 것 방지
        if (hDown)
            isHorizonMove = true;
        else if (vDown)
            isHorizonMove = false;

        else if (hUp || vUp)
            isHorizonMove = h != 0;

        // 애니메이션 진입 후 계속 콜하는 것 방지. 한번만 애니메이션 쏴줘서 이동 smooth 하게 처리
        if (anim.GetInteger("hAxisRaw") != h)
        {
            anim.SetBool("isChange", true);
            anim.SetInteger("hAxisRaw", (int)h);
        }

        else if (anim.GetInteger("vAxisRaw") != v)
        {
            anim.SetBool("isChange", true);
            anim.SetInteger("vAxisRaw", (int)v);
        }

        else
            anim.SetBool("isChange", false);

    }

    void FixedUpdate()
    {
        Vector2 moveVec = isHorizonMove ? new Vector2(h, 0) : new Vector2(0, v);
        rigid.velocity = moveVec * Speed;
    }
}
