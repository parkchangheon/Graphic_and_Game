using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class dropper : MonoBehaviour
{
    MeshRenderer renderer;
    Rigidbody rigidbody;

    [SerializeField] float timeTowait = 3.0f;
    private void Start()
    {
        renderer = GetComponent<MeshRenderer>();
        rigidbody = GetComponent<Rigidbody>();
        renderer.enabled = false;
        rigidbody.useGravity = false;
    }

    private void Update()
    {
        if (Time.time > timeTowait)
        {
            renderer.enabled = true;
            rigidbody.useGravity = true;
        }

    }
}
