using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bigScroller : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        Update();
    }

    // Update is called once per frame
    void Update()
    {
        transform.position += new Vector3(-0.5f * Time.deltaTime, 0);

        if(transform.position.x < -17.2)
        {
            transform.position = new Vector3(17.2f, transform.position.y);
        }
    }
}
