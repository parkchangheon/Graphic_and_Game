using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    // Start is called before the first frame update

    public float maxSpeed;
    public float jumpPower;
    Rigidbody2D rigid;
    SpriteRenderer spriteRenderer;
    Animator anim;

    private void Awake()
    {
        rigid = GetComponent<Rigidbody2D>();
        spriteRenderer = GetComponent<SpriteRenderer>();
        anim = GetComponent<Animator>();
    }

    private void Update()  // 단발적인 update
    {

        //Jump
        if(Input.GetButtonDown("Jump")&& !anim.GetBool("IsJumping"))
        {
            rigid.AddForce(Vector2.up * jumpPower, ForceMode2D.Impulse);
            anim.SetBool("IsJumping", true);
        }


        //stop speed
        if (Input.GetButtonUp("Horizontal"))
        {
            rigid.velocity = new Vector2(rigid.velocity.normalized.x * 0.5f, rigid.velocity.y);
        }

        if (Input.GetButtonDown("Horizontal"))  // 방향 전환시 Flip하는 것.
            spriteRenderer.flipX = Input.GetAxisRaw("Horizontal") == -1;



        //Animation
        if (Mathf.Abs(rigid.velocity.x) <= 0.3f)
            anim.SetBool("IsWalking", false);

        else
            anim.SetBool("IsWalking", true);
    }


    private void FixedUpdate() //지속적인 update
    {
        // 속도 구하기
        float h = Input.GetAxis("Horizontal");
        rigid.AddForce(Vector2.right * h, ForceMode2D.Impulse); // 이건 가속을 준것.


        //Move By Key Control
        if (rigid.velocity.x > maxSpeed) // 오른쪽으로 가는 경우
            rigid.velocity = new Vector2(maxSpeed, rigid.velocity.y);

        else if (rigid.velocity.x < -maxSpeed) // 왼쪽으로 가는 경우
            rigid.velocity = new Vector2(-maxSpeed, rigid.velocity.y);


        // Landing Platform
        if (rigid.velocity.y < 0)
        {
            Debug.DrawRay(rigid.position, Vector3.down, new Color(0, 1, 0));
            RaycastHit2D rayHit = Physics2D.Raycast(rigid.position, Vector3.down, 1, LayerMask.GetMask("Platform"));

            if (rayHit.collider != null) // 비어 있지 않다면
            {
                if (rayHit.distance < 0.5f)
                {
                    anim.SetBool("IsJumping", false);
                }
            }
        }


    }

    void Start()
    {
        
    }


}
