using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BirdJump : MonoBehaviour  //버드점프가 모노비헤이비얼을 상속받는다
{

    // RigidBody를 불러오는 변수를 만들어준다 (피직스를 이용하여, 점프를 구현)
    Rigidbody2D rb;
    public float JumpPower; //public 을 사용하면, UPROPERTY 처럼 에디터에서 수정이 가능함.


    // Start is called before the first frame update
    void Start()  // 최초한번 (언리얼의 begin)
    {
        //Debug.Log("Start 입니다");
        rb = GetComponent<Rigidbody2D>(); //Rigidbody2d라는 컴포넌트를 가져와서 rb에 담겠다.
    }

    // Update is called once per frame
    void Update() // 매 프레임마다 (언리얼의 Tick)
    {
        //Debug.Log("Update 입니다");
        if (Input.GetMouseButtonDown(0)) //마우스 버튼이 눌렸을때를 감지해서 ==>0은 마우스 왼쪽 버튼
        {
            rb.velocity = Vector2.up * JumpPower; //2차원 좌표 vector2.up은 (0,1)을 나타내고  
        }
    }


}
