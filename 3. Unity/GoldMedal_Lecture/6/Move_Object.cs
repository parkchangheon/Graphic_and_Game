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

    // Update is called once per frame
    void Update()
    {
        Vector3 vec = new Vector3(
            Input.GetAxisRaw("Horizontal"),
            Input.GetAxisRaw("Vertical"), 
            0);  // 벡터 값

        transform.Translate(vec);
        
    }
}
