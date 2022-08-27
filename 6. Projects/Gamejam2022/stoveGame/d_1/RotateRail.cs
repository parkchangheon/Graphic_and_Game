using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateRail : MonoBehaviour
{
    private float rotZ;
    public float RotationSpeed = 250;
    public bool RotationDir;

    private void Start()
    {
        Update();
    }

    private void Update()
    {
        if(RotationDir == false)
        {
            rotZ += Time.deltaTime * RotationSpeed;
        }
        else
        {
            rotZ += -Time.deltaTime * RotationSpeed;
        }

        transform.rotation = Quaternion.Euler(0, 0, rotZ);
    }
}
