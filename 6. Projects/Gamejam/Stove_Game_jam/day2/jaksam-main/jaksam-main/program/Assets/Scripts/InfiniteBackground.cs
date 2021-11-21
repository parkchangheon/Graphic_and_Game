using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InfiniteBackground : MonoBehaviour
{
    private Material mat;

    [SerializeField]
    GameObject player_obj;

    Rigidbody2D rigid;

    private void Start()
    {
        if(player_obj != null)
            rigid = player_obj.GetComponent<Rigidbody2D>();
        mat = GetComponent<Renderer>().material;
    }

    private void Update()
    {
        Vector2 newoffset = mat.mainTextureOffset;
        if(rigid != null)
        {
            newoffset.Set(newoffset.x + rigid.velocity.x * Time.deltaTime, newoffset.y + rigid.velocity.y * Time.deltaTime);
        }
        else
        {
            newoffset.Set(0, newoffset.y + 0.5f * Time.deltaTime);
        }
        mat.mainTextureOffset = newoffset;
    }

}
