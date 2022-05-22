using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    public float maxSpeed;
    public float jumpPower;
    Rigidbody2D rigid;
    SpriteRenderer spriteRender;
    Animator anim;

    void Awake()
    {
        rigid = GetComponent<Rigidbody2D>();
        spriteRender = GetComponent<SpriteRenderer>();
        anim = GetComponent<Animator>();
        
    }

    void Update()
    {
        //Jump
        if (Input.GetButtonDown("Jump")&& !anim.GetBool("IsJumping"))
        {
            rigid.AddForce(Vector2.up * jumpPower, ForceMode2D.Impulse);
            anim.SetBool("IsJumping", true);
        }

        //stop speed
        if (Input.GetButtonUp("Horizontal"))
        {
            //rigid.velocity.normalized    //벡터 크기를 1로 만든 상태 ( 단위 벡터 ) 
            rigid.velocity = new Vector2(rigid.velocity.normalized.x * 0.5f, rigid.velocity.y);
        }

        //Direction Sprite
        if (Input.GetButtonDown("Horizontal"))
            spriteRender.flipX = Input.GetAxisRaw("Horizontal") == -1;

        if (Mathf.Abs(rigid.velocity.x) <0.3 )
            anim.SetBool("IsWalking", false);
        else
            anim.SetBool("IsWalking", true);
    }

    private void FixedUpdate()
    {

        //move by control
        float h = Input.GetAxisRaw("Horizontal");
        rigid.AddForce(Vector2.right * h, ForceMode2D.Impulse); //등가속도라 가속이 무한이 된다.

        //Max Speed 
        if (rigid.velocity.x > maxSpeed)  //right
            rigid.velocity = new Vector2(maxSpeed, rigid.velocity.y); //y축을 0 으로 두면 안된다.

        else if (rigid.velocity.x < maxSpeed*(-1)) //left
            rigid.velocity = new Vector2(maxSpeed*(-1), rigid.velocity.y);


        //Landing Platform
        if (rigid.velocity.y<0)
        {
            Debug.DrawRay(rigid.position, Vector3.down, new Color(0, 1, 0));
            RaycastHit2D rayHit = Physics2D.Raycast(rigid.position, Vector3.down, 4, LayerMask.GetMask("Platform"));
            if (rayHit.collider != null)
            {
                if (rayHit.distance < 0.5f)
                {
                    Debug.Log(rayHit.collider.name);
                    anim.SetBool("IsJumping", false);
                }

            }
        }




    }
}
