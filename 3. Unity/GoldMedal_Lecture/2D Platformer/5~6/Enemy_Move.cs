using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy_Move : MonoBehaviour
{
    Rigidbody2D rigid;
    public int nextMove;
    Animator anim;
    SpriteRenderer spriterenderer;

    void Awake()
    {
        rigid = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
        spriterenderer = GetComponent<SpriteRenderer>();
        //함수호출할때 delay를 주고 싶으면, =>Invoke함수를 쓴다.
        Invoke("Think", 5);
    }

    private void FixedUpdate()
    {
        //Move
        rigid.velocity = new Vector2( nextMove, rigid.velocity.y);  // 왼쪽 방향으로 쭉 가게끔 짠 코드

        //Platform 낭떠러지 빠지지 않게끔 하는 코드
        Vector2 frontVec = new Vector2(rigid.position.x + nextMove, rigid.position.y);
        Debug.DrawRay(frontVec, Vector3.down, new Color(0, 1, 0));
        RaycastHit2D rayHit = Physics2D.Raycast(frontVec, Vector3.down, 1, LayerMask.GetMask("Platform"));

        if(rayHit.collider ==null){
            Turn();
        }


    }

    void Think()
    {
        nextMove = Random.Range(-1, 2); // -1 <= 랜덤값 < 2

        anim.SetInteger("WalkSpeed", nextMove);

        if(nextMove!=0)
            spriterenderer.flipX = nextMove == 1;

        //함수호출할때 delay를 주고 싶으면, =>Invoke함수를 쓴다.
        float nextThinkTime = Random.Range(2f, 5f);
        Invoke("Think", nextThinkTime);
    }

    void Turn()
    {
        nextMove *= -1; // 반대로가게끔 처리해주는 코드
        spriterenderer.flipX = nextMove == 1;

        CancelInvoke();
        Invoke("Think", 2);

    }
}
