using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveTarget : MonoBehaviour
{
    Vector3 target = new Vector3(8, 1.5f, 0);
    void Update()
    {
        // 1. movetowards
        //transform.position = Vector3.MoveTowards(transform.position, target, 1f);  //현재위치, 타겟위치, 속도 

        // 2. SmoothDamp
        /*Vector3 velo = Vector3.zero;
        //Vector3 velo = Vector3.up*50; //잘안씀

        transform.position = Vector3.SmoothDamp(transform.position, target, ref velo, 0.1f);   //참조 -> 실시간으로 바뀌는 값 적용 가능 ref*/

        // 3. Lerp (보간) - Smooth Damp보다 감속시간이 길다.
        //transform.position = Vector3.Lerp(transform.position, target, 0.05f); // 값을 적게 줄수록 느리게 이동

        // 4. SLerp (구면 선형 보간) - 호를 그리며 이동
        //transform.position = Vector3.Slerp(transform.position, target, 0.05f); // 포물선 이동 -> 점프하는 듯한 움직임
    }
}
