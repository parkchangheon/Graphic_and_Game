using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class S_Ball : MonoBehaviour
{

    Rigidbody rigid;

    void Start()
    {
        /*rigid = GetComponent<Rigidbody>(); */  //rigid 바디 초기화 
                                             //rigid.velocity = Vector3.right;
                                             //rigid.velocity = new Vector3(2, 4, 3); // 통통 튀기듯이 간다. => 단 피직스 머터리얼 입혔을때

        //힘으로 밀듯이 효과를 주는 것
    }

    void Update()
    {
        // 업데이트에 rigid 위에 통통 을 쓰면, 계속 쭉 날아간다.
        // rigidbody 관련 코드는 Fixed Update에 넣어서 작동시켜라

        /*if (Input.GetButtonDown("Jump"))
        {
            rigid.AddForce(Vector3.up * 50, ForceMode.Impulse);
            Debug.Log(rigid.velocity);
        }

        Vector3 vec = new Vector3(Input.GetAxisRaw("Horizontal"), 
            0,Input.GetAxisRaw("Vertical"));

        rigid.AddForce(vec, ForceMode.Impulse);*/

        //3. 회전력
        //rigid.AddTorque(Vector3.back); // vec를 축으로 삼는다.
    }

}
