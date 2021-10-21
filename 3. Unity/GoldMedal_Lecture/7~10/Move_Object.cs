using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move_Object : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        //게임 오브젝트 트랜스폼은 이미 1:1 관계로 적용되어서, 선언이 필요없다.
        Vector3 vec = new Vector3(0, 0, 0);  // 벡터 값
        transform.Translate(vec);  // 단순 이동(벡터의 크기 만큼)


    }


    Vector3 target = new Vector3(8, 1.5f, 0);
    // Update is called once per frame
    void Update()
    {
        Vector3 vec = new Vector3(
            Input.GetAxisRaw("Horizontal") * Time.deltaTime,
            Input.GetAxisRaw("Vertical") * Time.deltaTime,
            0);  // 벡터 값

        transform.Translate(vec);
        //translate : 벡터에 곱하기 
        // vector 함수 : 시간 매개변수에 곱하기


        //1. MoveToward를 사용하여 이동하는 방법
        //transform.position = Vector3.MoveTowards(transform.position, target, 1f);// 현재 위치, 목표 위치, 속도 로 구성되어 있습니다.


        //2. SmoothDamp를 사용하여 이동하는 방법
        //Vector3 velo = Vector3.zero;
        //transform.position = Vector3.SmoothDamp(transform.position, target, ref velo, 0.1f);//부드러운 감속 이동

        //3. Lerp (선형 보간)
        /*transform.position =
            Vector3.Lerp(transform.position, target, 0.05f); //마지막 매개변수에 비례하게 속도 증가(최댓값 1)*/

        //4. SLerp (구형 선형 보간) - 포물선 이동
        /*transform.position =
            Vector3.Slerp(transform.position, target, 0.05f);*/
    


    }
}
