using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WayPoint : MonoBehaviour
{
    [SerializeField] GameObject towerPrefab;
    [SerializeField] bool isPlaceable;

    void OnMouseDown()
    {
        if(isPlaceable)
        {
            Instantiate(towerPrefab, transform.position, Quaternion.identity); //게임 실행 도중에 오브젝트를 생성할 수 있다. (생성하고자 하는 오브젝트, 위치, 회전값 지정 default identity)
            isPlaceable = false;
        }
            
    }

    
    
}
