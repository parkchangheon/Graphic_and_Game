using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OtherBall : MonoBehaviour
{
    Rigidbody rigid;
    MeshRenderer mesh;
    Material mat;
    
    void Start()
    {
        mesh = GetComponent<MeshRenderer>();
        mat = mesh.material;
    }

    private void OnCollisionEnter(Collision collision)  //Collision 이 충돌한 오브젝트의 정보를 가지고 있다.
    {
        if(collision.gameObject.name == "Test") // 오브젝트의 이름을 설정해준다.
            mat.color = new Color(0, 0, 0);
    }


    private void OnCollisionExit(Collision collision)
    {
        mat.color = new Color(1, 1, 1);
    }

}
