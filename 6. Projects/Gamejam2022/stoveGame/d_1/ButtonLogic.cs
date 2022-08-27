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

    //레이캐스트용
    RaycastHit2D hit;
    [SerializeField] float distance = 10f;


    public 
    void Start()
    {
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
        hit = Physics2D.Raycast(transform.position, transform.up, distance);

        if(mustPatrol)
        {
            Patrol();
        }


        if (IsLeftBtn)  //왼쪽 버튼 누를때
        {
            if (Input.GetKeyDown(KeyCode.A))
            {
                Debug.Log("A Pressed");
                if(hit.collider != null)
                {
                    Debug.DrawRay(transform.position, hit.point, Color.white);
                    Debug.Log("Food Hit");
                }
            }
        }


        else
        {
            if (Input.GetKeyDown(KeyCode.S))
            {
                Debug.Log("S Pressed");
            }
        }
    }

    void Patrol()
    {

    }

    void Flip()
    {
        mustPatrol = false;
        MoveSpeed = -1;
        mustPatrol = true;

    }
}
