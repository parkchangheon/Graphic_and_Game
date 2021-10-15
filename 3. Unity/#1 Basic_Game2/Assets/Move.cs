using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move : MonoBehaviour

    //prefab은 계속적으로 찍어낼 수 있는 (generator 가)  ==> 마린 / 배럭 개념
{
    // Start is called before the first frame update

    public float speed;

    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        transform.position += Vector3.left * speed * Time.deltaTime;    //vector3.left=(-1,0,0) 을 뜻한다    // Time.deltatime은 역시 DeltaTime과 같음

    }
}
