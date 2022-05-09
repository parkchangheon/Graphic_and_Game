using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyBall : MonoBehaviour
{

    Rigidbody rigid;

    void Start()
    {
        rigid = GetComponent<Rigidbody>();
        //rigid.velocity = Vector3.right; //속력을 주었다.오른쪽으로
        //rigid.velocity = new Vector3(2, 4, 3);

        //힘으로 밀기
        //rigid.AddForce(Vector3.up * 5, ForceMode.Impulse); // 점프


    }

    //unity에서는 rigid velocity를 FixedUpdate에 써주는 것을 권장한다.
    private void FixedUpdate()
    {
        //rigid.velocity = new Vector3(2, 4, 3);
/*        if (Input.GetButtonDown("Jump"))
            rigid.AddForce(Vector3.up * 50, ForceMode.Impulse);*/

        //Vector3 vec = new Vector3(Input.GetAxisRaw("Horizontal"), 0, Input.GetAxisRaw("Vertical")); //벡터는 클릭한 값 단 위로는 x
        //rigid.AddForce(vec*(0.2f), ForceMode.Impulse);  // impulse -> forcemode

        //회전력
        //rigid.AddTorque(Vector3.back);
        float h = Input.GetAxisRaw("Horizontal");
        float v = Input.GetAxisRaw("Vertical");
        Vector3 vec = new Vector3(h, 0, v);

        rigid.AddForce(vec, ForceMode.Impulse);
    }


    private void OnTriggerStay(Collider other)
    {
        if (other.gameObject.name == "Cube")
        {
            rigid.AddForce(Vector3.up * 2, ForceMode.Impulse);
        }
    }

    void Update()
    {
        //여기에 rigid.velocity를 주면 계속 날아가겠지?
        //rigid.velocity = new Vector3(2, 4, 3); // 우주선 마냥 날아간다.


    }
}
