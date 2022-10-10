using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class dropper : MonoBehaviour
{
    [SerializeField] float timeTowait = 3.0f;
    private void Start()
    {
        GetComponent<Rigidbody>().useGravity = false;
    }

    private void Update()
    {
        if (Time.time < timeTowait)
        {
            Debug.Log("the time.time is " + Time.time);
        }
            

        else
        {
            GetComponent<Rigidbody>().useGravity = true;
        }
    }
}
