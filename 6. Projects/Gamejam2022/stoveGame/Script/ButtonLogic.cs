using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButtonLogic : MonoBehaviour
{
    [HideInInspector]
    public float MoveSpeed;
    public bool mustPatrol;
    public Rigidbody2D rb;
    public Transform tb;
    public bool IsLeftBtn;
    public bool MoveLeftRight = true;
    public bool MoveRightRight = true;
    public bool CollideWith = false;
    public bool CanJump = true;


    //펀치
    [SerializeField] float moveSpeed = 1f;
    Rigidbody2D PunchRB;
    [SerializeField] int power;
    public Transform groundCheck;
    public LayerMask groundLayer;


    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.collider.CompareTag("Item"))
        {
            
            Destroy(collision.gameObject);
            CollideWith = true;
        }

        if(collision.collider.CompareTag("Ground"))
        {
             CanJump = true;
        }
    }



    void Start()
    {
        PunchRB = GetComponent<Rigidbody2D>();
        mustPatrol = true;
        this.gameObject.ToString();
        Debug.Log(this.gameObject.ToString());

        //왼버튼, 오른버튼
        if (this.gameObject.CompareTag("BtnLeft"))
            IsLeftBtn = true;
        else
            IsLeftBtn = false;

    }

    // Update is called once per frame
    void Update()
    {
        if(mustPatrol)
        {
            Patrol();
        }


        if (IsLeftBtn)  //왼쪽 버튼 누를때
        {
            if (Input.GetKeyDown(KeyCode.A) && CanJump)
            {
                CanJump = false;
                Debug.Log("A Pressed");
                mustPatrol = false;
                PunchRB.velocity = new Vector2(PunchRB.velocity.x, power);
                Punch();
            }
        }


        else
        {
            if (Input.GetKeyDown(KeyCode.S) && CanJump)
            {
                CanJump = false;
                Debug.Log("S Pressed");
                mustPatrol = false;
                PunchRB.velocity = new Vector2(PunchRB.velocity.x, power);
                Punch();
            }
        }
    }

    void Patrol()
    {
        if (this.gameObject.CompareTag("BtnLeft"))
        {
            if (transform.position.x < -8)
                MoveLeftRight = true;
            if(transform.position.x >-2)
                MoveLeftRight = false;

            if (MoveLeftRight)
                transform.position += new Vector3(4f * Time.deltaTime, 0);

            else
                transform.position += new Vector3(-4f * Time.deltaTime, 0);
        }


        else if (this.gameObject.CompareTag("BtnRight"))
        {
            if (transform.position.x < 4)
                MoveRightRight = true;
            if (transform.position.x > 10)
                MoveRightRight = false;

            if (MoveRightRight)
                transform.position += new Vector3(4f * Time.deltaTime, 0);

            else
                transform.position += new Vector3(-4f * Time.deltaTime, 0);
        }
    }

    void Punch()
    {
        Invoke("PunchOver", 0.3f);
    }

    void PunchOver()
    {
        mustPatrol = true;
        CollideWith = false;
    }
}
